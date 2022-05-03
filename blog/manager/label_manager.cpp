#include "label_manager.hpp"
#include "src/log.hpp"
#include "src/util.hpp"
#include "blog/util.hpp"

namespace blog {

static stone::Logger::ptr g_logger = STONE_LOG_ROOT();

bool LabelManager::loadAll() {
    auto db = GetDB();
    if(!db) {
        STONE_LOG_ERROR(g_logger) << "Get SQLite3 connection fail";
        return false;
    }
    std::vector<data::LabelInfo::ptr> results;
    if(blog::data::LabelInfoDao::QueryAll(results, db)) {
        STONE_LOG_ERROR(g_logger) << "LabelManager loadAll fail";
        return false;
    }

    std::unordered_map<int64_t, blog::data::LabelInfo::ptr> datas;

    for(auto& i : results) {
        datas[i->getLId()] = i;
    }

    stone::RWMutex::WriteLock lock(m_mutex);
    m_datas.swap(datas);
    return true;
}

void LabelManager::add(blog::data::LabelInfo::ptr info) {
    stone::RWMutex::WriteLock lock(m_mutex);
    m_datas[info->getLId()] = info;
}

#define XX(map, key) \
    stone::RWMutex::ReadLock lock(m_mutex); \
    auto it = map.find(key); \
    return it == map.end() ? nullptr : it->second;

blog::data::LabelInfo::ptr LabelManager::get(int64_t id) {
    XX(m_datas, id);
}

std::string LabelManager::statusString() {
    std::stringstream ss;
    stone::RWMutex::ReadLock lock(m_mutex);
    ss << "LabelManager total=" << m_datas.size()
       << std::endl;
    lock.unlock();
    return ss.str();
}

#undef XX

}
