#include "article_label_rel_manager.hpp"
#include "src/log.hpp"
#include "src/util.hpp"
#include "blog/util.hpp"

namespace blog {

static stone::Logger::ptr g_logger = STONE_LOG_ROOT(); 

bool ArticleLabelRelManager::loadAll() {
    auto db = GetDB();
    if(!db) {
        STONE_LOG_ERROR(g_logger) << "Get SQLite3 connection fail";
        return false;
    }
    std::vector<data::ArticleLabelRelInfo::ptr> results;
    if(blog::data::ArticleLabelRelInfoDao::QueryAll(results, db)) {
        STONE_LOG_ERROR(g_logger) << "ArticleLabelRelManager loadAll fail";
        return false;
    }

    std::unordered_map<int64_t, blog::data::ArticleLabelRelInfo::ptr> datas;
    std::unordered_map<int64_t, std::map<int64_t, blog::data::ArticleLabelRelInfo::ptr> > articles;
    std::unordered_map<int64_t, std::map<int64_t, blog::data::ArticleLabelRelInfo::ptr> > labels;

    for(auto& i : results) {
        datas[i->getId()] = i;
        articles[i->getArticleId()][i->getLabelId()] = i;
        labels[i->getLabelId()][i->getArticleId()] = i;
    }

    stone::RWMutex::WriteLock lock(m_mutex);
    m_datas.swap(datas);
    m_articles.swap(articles);
    m_labels.swap(labels);
    return true;
}

void ArticleLabelRelManager::add(blog::data::ArticleLabelRelInfo::ptr info) {
    stone::RWMutex::WriteLock lock(m_mutex);
    m_datas[info->getId()] = info;
    m_articles[info->getArticleId()][info->getLabelId()] = info;
    m_labels[info->getLabelId()][info->getArticleId()] = info;
}

#define XX(map, key) \
    stone::RWMutex::ReadLock lock(m_mutex); \
    auto it = map.find(key); \
    return it == map.end() ? nullptr : it->second;

blog::data::ArticleLabelRelInfo::ptr ArticleLabelRelManager::get(int64_t id) {
    XX(m_datas, id);
}

blog::data::ArticleLabelRelInfo::ptr ArticleLabelRelManager::getByArticleIdLabelId(int64_t article_id, int64_t label_id) {
    stone::RWMutex::ReadLock lock(m_mutex);
    auto it = m_articles.find(article_id);
    if(it == m_articles.end()) {
        return nullptr;
    }
    auto iit = it->second.find(label_id);
    return iit == it->second.end() ? nullptr : iit->second;
}

bool ArticleLabelRelManager::listByArticleId(std::vector<data::ArticleLabelRelInfo::ptr>& infos
                ,int64_t article_id, bool valid) {
    stone::RWMutex::ReadLock lock(m_mutex);
    auto it = m_articles.find(article_id);
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

bool ArticleLabelRelManager::listByLabelId(std::vector<data::ArticleLabelRelInfo::ptr>& infos
                ,int64_t label_id, bool valid) {
    stone::RWMutex::ReadLock lock(m_mutex);
    auto it = m_labels.find(label_id);
    if(it == m_labels.end()) {
        return false;
    }
    for(auto& i : it->second) {
        if(!valid || !i.second->getIsDeleted()) {
            infos.push_back(i.second);
        }
    }
    return true;
}

std::string ArticleLabelRelManager::statusString() {
    std::stringstream ss;
    stone::RWMutex::ReadLock lock(m_mutex);
    ss << "ArticleLabelRelManager total=" << m_datas.size()
       << " articles=" << m_articles.size() << std::endl;
    lock.unlock();
    return ss.str();
}

#undef XX

}
