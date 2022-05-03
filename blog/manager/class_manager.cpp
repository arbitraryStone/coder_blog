#include "class_manager.hpp"
#include "src/log.hpp"
#include "src/util.hpp"
#include "blog/util.hpp"

namespace blog {

static stone::Logger::ptr g_logger = STONE_LOG_ROOT();

bool ClassManager::loadAll() {
    auto db = GetDB();
    if(!db) {
        STONE_LOG_ERROR(g_logger) << "Get SQLite3 connection fail";
        return false;
    }
    std::vector<data::ClassificationInfo::ptr> results;
    if(blog::data::ClassificationInfoDao::QueryAll(results, db)) {
        STONE_LOG_ERROR(g_logger) << "ClassManager loadAll fail";
        return false;
    }

    std::unordered_map<int64_t, blog::data::ClassificationInfo::ptr> datas;

    for(auto& i : results) {
        datas[i->getClassId()] = i;
    }

    stone::RWMutex::WriteLock lock(m_mutex);
    m_datas.swap(datas);
    return true;
}

void ClassManager::add(blog::data::ClassificationInfo::ptr info) {
    stone::RWMutex::WriteLock lock(m_mutex);
    m_datas[info->getClassId()] = info;
}

#define XX(map, key) \
    stone::RWMutex::ReadLock lock(m_mutex); \
    auto it = map.find(key); \
    return it == map.end() ? nullptr : it->second;

blog::data::ClassificationInfo::ptr ClassManager::get(int64_t id) {
    XX(m_datas, id);
}

bool ClassManager::exists(int64_t id, const std::string& name) {
    stone::RWMutex::ReadLock lock(m_mutex);
    auto it = m_datas.find(id);
    if(it == m_datas.end()) {
        return false;
    }
    if(it->second->getName()==name){
        return true;
    }
    return false;
}


std::string ClassManager::statusString() {
    std::stringstream ss;
    stone::RWMutex::ReadLock lock(m_mutex);
    ss << "ClassManager total=" << m_datas.size();
    lock.unlock();
    return ss.str();
}

#undef XX

}
