#ifndef __BLOG_MANAGER_USER_MANAGER_HPP__
#define __BLOG_MANAGER_USER_MANAGER_HPP__

#include "blog/data/user_info.hpp"
#include "src/singleton.hpp"
#include "src/mutex.hpp"
#include <unordered_map>

namespace blog {

class UserManager {
public:
    enum class RoleType {
        NORMAL = 1,
        ADMIN = 0xFF
    };
    bool loadAll();
    void add(blog::data::UserInfo::ptr info);
    blog::data::UserInfo::ptr get(int64_t id);
    blog::data::UserInfo::ptr getByEmail(const std::string& v);
    blog::data::UserInfo::ptr getByNickName(const std::string& v);

    static std::string GetToken(data::UserInfo::ptr info, int64_t ts);

    std::string statusString();
private:
    stone::RWMutex m_mutex;
    std::unordered_map<int64_t, blog::data::UserInfo::ptr> m_datas;
    std::unordered_map<std::string, blog::data::UserInfo::ptr> m_emails;
    std::unordered_map<std::string, blog::data::UserInfo::ptr> m_names;
};

typedef stone::Singleton<UserManager> UserMgr;

}

#endif
