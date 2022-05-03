#include "user_manager.hpp"
#include "src/log.hpp"
#include "src/util.hpp"
#include "src/util/hash_util.hpp"
#include "blog/util.hpp"

namespace blog {

static stone::Logger::ptr g_logger = STONE_LOG_ROOT();

bool UserManager::loadAll() {
    auto db = GetDB();
    if(!db) {
        STONE_LOG_ERROR(g_logger) << "Get SQLite3 connection fail";
        return false;
    }
    std::vector<data::UserInfo::ptr> results;
    if(blog::data::UserInfoDao::QueryAll(results, db)) {
        STONE_LOG_ERROR(g_logger) << "UserManager loadAll fail";
        return false;
    }

    std::unordered_map<int64_t, blog::data::UserInfo::ptr> datas;
    std::unordered_map<std::string, blog::data::UserInfo::ptr> emails;
    std::unordered_map<std::string, blog::data::UserInfo::ptr> names;

    for(auto& i : results) {
        datas[i->getUId()] = i;
        emails[i->getEmail()] = i;
        names[i->getNickName()] = i;
    }

    stone::RWMutex::WriteLock lock(m_mutex);
    m_datas.swap(datas);
    m_emails.swap(emails);
    m_names.swap(names);
    return true;
}

void UserManager::add(blog::data::UserInfo::ptr info) {
    stone::RWMutex::WriteLock lock(m_mutex);
    m_datas[info->getUId()] = info;
    m_emails[info->getEmail()] = info;
    m_names[info->getNickName()] = info;
}

#define XX(map, key) \
    stone::RWMutex::ReadLock lock(m_mutex); \
    auto it = map.find(key); \
    return it == map.end() ? nullptr : it->second;

blog::data::UserInfo::ptr UserManager::get(int64_t id) {
    XX(m_datas, id);
}

blog::data::UserInfo::ptr UserManager::getByEmail(const std::string& v) {
    XX(m_emails, v);
}

blog::data::UserInfo::ptr UserManager::getByNickName(const std::string& v) {
    XX(m_names, v);
}

#undef XX

std::string UserManager::GetToken(data::UserInfo::ptr info, int64_t ts) {
    std::stringstream ss;
    ss << info->getUId()
       << "|" << info->getNickName()
       << "|" << info->getEmail()
       << "|" << info->getPassword()
       << "|" << ts;
    return stone::md5(ss.str());
}

std::string UserManager::statusString() {
    std::stringstream ss;
    stone::RWMutex::ReadLock lock(m_mutex);
    ss << "UserManager total=" << m_datas.size()
       << std::endl;
    lock.unlock();
    return ss.str();
}

}
