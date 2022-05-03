#ifndef __BLOG_DATAUSER_INFO_H__
#define __BLOG_DATAUSER_INFO_H__

#include <json/json.h>
#include <vector>
#include "src/db/db.hpp"
#include "src/util.hpp"


namespace blog {
namespace data {

class UserInfoDao;
class UserInfo {
friend class UserInfoDao;
public:
    typedef std::shared_ptr<UserInfo> ptr;

    UserInfo();

    const int64_t& getId() { return m_id; }
    void setId(const int64_t& v);

    const std::string& getNickname() { return m_nickname; }
    void setNickname(const std::string& v);

    const std::string& getEmail() { return m_email; }
    void setEmail(const std::string& v);

    const std::string& getPassword() { return m_password; }
    void setPassword(const std::string& v);

    const std::string& getPicture() { return m_picture; }
    void setPicture(const std::string& v);

    const std::string& getUsername() { return m_username; }
    void setUsername(const std::string& v);

    const int64_t& getCreateTime() { return m_createTime; }
    void setCreateTime(const int64_t& v);

    const int64_t& getUpdateTime() { return m_updateTime; }
    void setUpdateTime(const int64_t& v);

    std::string toJsonString() const;

private:
    int64_t m_id;
    std::string m_nickname;
    std::string m_email;
    std::string m_password;
    std::string m_picture;
    std::string m_username;
    int64_t m_createTime;
    int64_t m_updateTime;
};


class UserInfoDao {
public:
    typedef std::shared_ptr<UserInfoDao> ptr;
    static int Update(UserInfo::ptr info, stone::IDB::ptr conn);
    static int Insert(UserInfo::ptr info, stone::IDB::ptr conn);
    static int InsertOrUpdate(UserInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(UserInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(const int64_t& id, stone::IDB::ptr conn);
    static int DeleteById( const int64_t& id, stone::IDB::ptr conn);
    static int DeleteByEmail( const std::string& email, stone::IDB::ptr conn);
    static int DeleteByUsername( const std::string& username, stone::IDB::ptr conn);
    static int QueryAll(std::vector<UserInfo::ptr>& results, stone::IDB::ptr conn);
    static UserInfo::ptr Query( const int64_t& id, stone::IDB::ptr conn);
    static UserInfo::ptr QueryByEmail( const std::string& email, stone::IDB::ptr conn);
    static UserInfo::ptr QueryByUsername( const std::string& username, stone::IDB::ptr conn);
    static int CreateTableSQLite3(stone::IDB::ptr info);
    static int CreateTableMySQL(stone::IDB::ptr info);
};

} //namespace data
} //namespace blog
#endif //__BLOG_DATAUSER_INFO_H__
