#include "user_friend_rel_manager.hpp"
#include "src/log.hpp"
#include "src/util.hpp"
#include "blog/util.hpp"

namespace blog {

static stone::Logger::ptr g_logger = STONE_LOG_ROOT();

bool UserFriendRelManager::loadAll() {
    auto db = GetDB();
    if(!db) {
        STONE_LOG_ERROR(g_logger) << "Get SQLite3 connection fail";
        return false;
    }
    std::vector<data::UserFriendRelInfo::ptr> results;
    if(blog::data::UserFriendRelInfoDao::QueryAll(results, db)) {
        STONE_LOG_ERROR(g_logger) << "UserFriendRelManager loadAll fail";
        return false;
    }

    std::unordered_map<int64_t, blog::data::UserFriendRelInfo::ptr> datas;
    std::unordered_map<int64_t, std::map<int64_t, blog::data::UserFriendRelInfo::ptr> > users;

    for(auto& i : results) {
        datas[i->getId()] = i;
        users[i->getUserId()][i->getFriendId()] = i;
    }

    stone::RWMutex::WriteLock lock(m_mutex);
    m_datas.swap(datas);
    m_users.swap(users);
    return true;
}

void UserFriendRelManager::add(blog::data::UserFriendRelInfo::ptr info) {
    stone::RWMutex::WriteLock lock(m_mutex);
    m_datas[info->getId()] = info;
    m_users[info->getUserId()][info->getFriendId()] = info;
}

#define XX(map, key) \
    stone::RWMutex::ReadLock lock(m_mutex); \
    auto it = map.find(key); \
    return it == map.end() ? nullptr : it->second;

blog::data::UserFriendRelInfo::ptr UserFriendRelManager::get(int64_t id) {
    XX(m_datas, id);
}

blog::data::UserFriendRelInfo::ptr UserFriendRelManager::getByUserIdFriendId(int64_t user_id, int64_t friend_id) {
    stone::RWMutex::ReadLock lock(m_mutex);
    auto it = m_users.find(user_id);
    if(it == m_users.end()) {
        return nullptr;
    }
    auto iit = it->second.find(friend_id);
    return iit == it->second.end() ? nullptr : iit->second;
}

bool UserFriendRelManager::listByUserId(std::vector<data::UserFriendRelInfo::ptr>& infos
                ,int64_t user_id, bool valid) {
    stone::RWMutex::ReadLock lock(m_mutex);
    auto it = m_users.find(user_id);
    if(it == m_users.end()) {
        return false;
    }
    for(auto& i : it->second) {
        if(!valid || !i.second->getIsDeleted()) {
            infos.push_back(i.second);
        }
    }
    return true;
}

std::string UserFriendRelManager::statusString() {
    std::stringstream ss;
    stone::RWMutex::ReadLock lock(m_mutex);
    ss << "UserFriendRelManager total=" << m_datas.size()
       << " users=" << m_users.size() << std::endl;
    lock.unlock();
    return ss.str();
}

#undef XX

}
