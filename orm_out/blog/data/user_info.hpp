#ifndef __BLOG_DATAUSER_INFO_HPP__
#define __BLOG_DATAUSER_INFO_HPP__

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

    const int64_t& getUId() { return m_uId; }
    void setUId(const int64_t& v);

    const std::string& getNickName() { return m_nickName; }
    void setNickName(const std::string& v);

    const std::string& getAvatar() { return m_avatar; }
    void setAvatar(const std::string& v);

    const std::string& getEmail() { return m_email; }
    void setEmail(const std::string& v);

    const std::string& getPassword() { return m_password; }
    void setPassword(const std::string& v);

    const std::string& getCode() { return m_code; }
    void setCode(const std::string& v);

    const int32_t& getRole() { return m_role; }
    void setRole(const int32_t& v);

    const int32_t& getState() { return m_state; }
    void setState(const int32_t& v);

    const int64_t& getLoginTime() { return m_loginTime; }
    void setLoginTime(const int64_t& v);

    const int32_t& getIsDeleted() { return m_isDeleted; }
    void setIsDeleted(const int32_t& v);

    const int64_t& getCreateTime() { return m_createTime; }
    void setCreateTime(const int64_t& v);

    std::string toJsonString() const;

private:
    int32_t m_role;
    int32_t m_state;
    int32_t m_isDeleted;
    int64_t m_uId;
    std::string m_nickName;
    std::string m_email;
    std::string m_password;
    std::string m_code;
    std::string m_avatar;
    int64_t m_loginTime;
    int64_t m_createTime;
};


class UserInfoDao {
public:
    typedef std::shared_ptr<UserInfoDao> ptr;
    static int Update(UserInfo::ptr info, stone::IDB::ptr conn);
    static int Insert(UserInfo::ptr info, stone::IDB::ptr conn);
    static int InsertOrUpdate(UserInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(UserInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(const int64_t& u_id, stone::IDB::ptr conn);
    static int DeleteByUId( const int64_t& u_id, stone::IDB::ptr conn);
    static int DeleteByEmail( const std::string& email, stone::IDB::ptr conn);
    static int DeleteByNickName( const std::string& nick_name, stone::IDB::ptr conn);
    static int QueryAll(std::vector<UserInfo::ptr>& results, stone::IDB::ptr conn);
    static UserInfo::ptr Query( const int64_t& u_id, stone::IDB::ptr conn);
    static UserInfo::ptr QueryByEmail( const std::string& email, stone::IDB::ptr conn);
    static UserInfo::ptr QueryByNickName( const std::string& nick_name, stone::IDB::ptr conn);
    static int CreateTableSQLite3(stone::IDB::ptr info);
    static int CreateTableMySQL(stone::IDB::ptr info);
};

} //namespace data
} //namespace blog
#endif //__BLOG_DATAUSER_INFO_HPP__
