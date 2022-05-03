#ifndef __BLOG_DATAUSER_FRIEND_REL_INFO_HPP__
#define __BLOG_DATAUSER_FRIEND_REL_INFO_HPP__

#include <json/json.h>
#include <vector>
#include "src/db/db.hpp"
#include "src/util.hpp"


namespace blog {
namespace data {

class UserFriendRelInfoDao;
class UserFriendRelInfo {
friend class UserFriendRelInfoDao;
public:
    typedef std::shared_ptr<UserFriendRelInfo> ptr;

    UserFriendRelInfo();

    const int64_t& getId() { return m_id; }
    void setId(const int64_t& v);

    const int64_t& getUserId() { return m_userId; }
    void setUserId(const int64_t& v);

    const int64_t& getFriendId() { return m_friendId; }
    void setFriendId(const int64_t& v);

    const int32_t& getIsDeleted() { return m_isDeleted; }
    void setIsDeleted(const int32_t& v);

    const int64_t& getCreateTime() { return m_createTime; }
    void setCreateTime(const int64_t& v);

    const int64_t& getUpdateTime() { return m_updateTime; }
    void setUpdateTime(const int64_t& v);

    std::string toJsonString() const;

private:
    int32_t m_isDeleted;
    int64_t m_id;
    int64_t m_userId;
    int64_t m_friendId;
    int64_t m_createTime;
    int64_t m_updateTime;
};


class UserFriendRelInfoDao {
public:
    typedef std::shared_ptr<UserFriendRelInfoDao> ptr;
    static int Update(UserFriendRelInfo::ptr info, stone::IDB::ptr conn);
    static int Insert(UserFriendRelInfo::ptr info, stone::IDB::ptr conn);
    static int InsertOrUpdate(UserFriendRelInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(UserFriendRelInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(const int64_t& id, stone::IDB::ptr conn);
    static int DeleteById( const int64_t& id, stone::IDB::ptr conn);
    static int DeleteByUserId( const int64_t& user_id, stone::IDB::ptr conn);
    static int DeleteByUserIdFriendId( const int64_t& user_id,  const int64_t& friend_id, stone::IDB::ptr conn);
    static int QueryAll(std::vector<UserFriendRelInfo::ptr>& results, stone::IDB::ptr conn);
    static UserFriendRelInfo::ptr Query( const int64_t& id, stone::IDB::ptr conn);
    static int QueryByUserId(std::vector<UserFriendRelInfo::ptr>& results,  const int64_t& user_id, stone::IDB::ptr conn);
    static UserFriendRelInfo::ptr QueryByUserIdFriendId( const int64_t& user_id,  const int64_t& friend_id, stone::IDB::ptr conn);
    static int CreateTableSQLite3(stone::IDB::ptr info);
    static int CreateTableMySQL(stone::IDB::ptr info);
};

} //namespace data
} //namespace blog
#endif //__BLOG_DATAUSER_FRIEND_REL_INFO_HPP__
