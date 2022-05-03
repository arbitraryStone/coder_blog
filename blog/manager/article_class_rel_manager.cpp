#include "article_class_rel_manager.hpp"
#include "src/log.hpp"
#include "src/util.hpp"
#include "blog/util.hpp"

namespace blog {

static stone::Logger::ptr g_logger = STONE_LOG_ROOT();

bool ArticleClassRelManager::loadAll() {
    auto db = GetDB();
    if(!db) {
        STONE_LOG_ERROR(g_logger) << "Get SQLite3 connection fail";
    }
    std::vector<blog::data::ArticleClassRelInfo::ptr> results;
    if(blog::data::ArticleClassRelInfoDao::QueryAll(results, db)) {
        STONE_LOG_ERROR(g_logger) << "ArticleClassRelManager loadAll fail";
        return false;
    }

    std::unordered_map<int64_t, blog::data::ArticleClassRelInfo::ptr> datas;
    std::unordered_map<int64_t, std::map<int64_t, blog::data::ArticleClassRelInfo::ptr> > articles;
    std::unordered_map<int64_t, std::map<int64_t, blog::data::ArticleClassRelInfo::ptr> > classes;

    for(auto& i : results) {
        datas[i->getId()] = i;
        articles[i->getArticleId()][i->getClassId()] = i;
        articles[i->getClassId()][i->getArticleId()] = i;
    }

    stone::RWMutex::WriteLock lock(m_mutex);
    m_datas.swap(datas);
    m_articles.swap(articles);
    m_classes.swap(classes);
    return true;
}

void ArticleClassRelManager::add(blog::data::ArticleClassRelInfo::ptr info) {
    stone::RWMutex::WriteLock lock(m_mutex);
    m_datas[info->getId()] = info;
    m_articles[info->getArticleId()][info->getClassId()] = info;
    m_classes[info->getClassId()][info->getArticleId()] = info;
}

#define XX(map, key) \
    stone::RWMutex::ReadLock lock(m_mutex); \
    auto it = map.find(key); \
    return it == map.end() ? nullptr : it->second;

blog::data::ArticleClassRelInfo::ptr ArticleClassRelManager::get(int64_t id) {
    XX(m_datas, id);
}

bool ArticleClassRelManager::listByArticleId(std::vector<data::ArticleClassRelInfo::ptr>& infos
                                                ,int64_t id, bool valid) {
    stone::RWMutex::ReadLock lock(m_mutex);
    auto it = m_articles.find(id);
    if(it == m_articles.end()) {
        return false;
    }
    for(auto& i : it->second) {
        if(!valid || !i.second->getIsDeleted()) {
            infos.push_back(i.second);
        }
    }
    return true;
}

bool ArticleClassRelManager::listByClassId(std::vector<data::ArticleClassRelInfo::ptr>& infos
                                                ,int64_t id, bool valid) {
    stone::RWMutex::ReadLock lock(m_mutex);
    auto it = m_classes.find(id);
    if(it == m_classes.end()) {
        return false;
    }
    for(auto& i : it->second) {
        if(!valid || !i.second->getIsDeleted()) {
            infos.push_back(i.second);
        }
    }
    return true;
}

blog::data::ArticleClassRelInfo::ptr ArticleClassRelManager::getByArticleIdClassId(int64_t article_id
                    ,int64_t class_id) {
    stone::RWMutex::ReadLock lock(m_mutex);
    auto it = m_articles.find(article_id);
    if(it == m_articles.end()) {
        return nullptr;
    }
    auto iit = it->second.find(class_id);
    if(iit == it->second.end()) {
        return nullptr;
    }
    return iit->second;
}

std::string ArticleClassRelManager::statusString() {
    std::stringstream ss;
    stone::RWMutex::ReadLock lock(m_mutex);
    ss << "ArticleClassRelManager total=" << m_datas.size()
       << " articles=" << m_articles.size()
       << std::endl;
    lock.unlock();
    return ss.str();
}

#undef XX

}
