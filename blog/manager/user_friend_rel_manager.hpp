#ifndef __BLOG_MANAGER_USER_FRIEND_REL_MANAGER_HPP__
#define __BLOG_MANAGER_USER_FRIEND_REL_MANAGER_HPP__

#include "blog/data/user_friend_rel_info.hpp"
#include "src/singleton.hpp"
#include "src/mutex.hpp"
#include <map>
#include <unordered_map>

namespace blog {

class UserFriendRelManager {
public:
    bool loadAll();
    void add(blog::data::UserFriendRelInfo::ptr info);
    blog::data::UserFriendRelInfo::ptr get(int64_t id);
    blog::data::UserFriendRelInfo::ptr getByUserIdFriendId(int64_t user_id, int64_t friend_id);
    bool listByUserId(std::vector<data::UserFriendRelInfo::ptr>& infos, int64_t user_id, bool valid);

    std::string statusString();
private:
    stone::RWMutex m_mutex;
    std::unordered_map<int64_t, blog::data::UserFriendRelInfo::ptr> m_datas;
    std::unordered_map<int64_t, std::map<int64_t, blog::data::UserFriendRelInfo::ptr> > m_users;
};

typedef stone::Singleton<UserFriendRelManager> UserFriendRelMgr;

}

#endif
