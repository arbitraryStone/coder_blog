#include "user_info.hpp"
#include "src/log.hpp"

namespace blog {
namespace data {

static stone::Logger::ptr g_logger = STONE_LOG_NAME("orm");

UserInfo::UserInfo()
    :m_role()
    ,m_state()
    ,m_isDeleted()
    ,m_uId()
    ,m_nickName()
    ,m_email()
    ,m_password()
    ,m_code()
    ,m_avatar()
    ,m_loginTime()
    ,m_createTime() {
}

std::string UserInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["u_id"] = std::to_string(m_uId);
    jvalue["nick_name"] = m_nickName;
    jvalue["avatar"] = m_avatar;
    jvalue["email"] = m_email;
    jvalue["password"] = m_password;
    jvalue["code"] = m_code;
    jvalue["role"] = m_role;
    jvalue["state"] = m_state;
    jvalue["login_time"] = stone::Time2Str(m_loginTime);
    jvalue["is_deleted"] = m_isDeleted;
    jvalue["create_time"] = stone::Time2Str(m_createTime);
    return stone::JsonUtil::ToString(jvalue);
}

void UserInfo::setUId(const int64_t& v) {
    m_uId = v;
}

void UserInfo::setNickName(const std::string& v) {
    m_nickName = v;
}

void UserInfo::setAvatar(const std::string& v) {
    m_avatar = v;
}

void UserInfo::setEmail(const std::string& v) {
    m_email = v;
}

void UserInfo::setPassword(const std::string& v) {
    m_password = v;
}

void UserInfo::setCode(const std::string& v) {
    m_code = v;
}

void UserInfo::setRole(const int32_t& v) {
    m_role = v;
}

void UserInfo::setState(const int32_t& v) {
    m_state = v;
}

void UserInfo::setLoginTime(const int64_t& v) {
    m_loginTime = v;
}

void UserInfo::setIsDeleted(const int32_t& v) {
    m_isDeleted = v;
}

void UserInfo::setCreateTime(const int64_t& v) {
    m_createTime = v;
}


int UserInfoDao::Update(UserInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "update user set nick_name = ?, avatar = ?, email = ?, password = ?, code = ?, role = ?, state = ?, login_time = ?, is_deleted = ?, create_time = ? where u_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, info->m_nickName);
    stmt->bindString(2, info->m_avatar);
    stmt->bindString(3, info->m_email);
    stmt->bindString(4, info->m_password);
    stmt->bindString(5, info->m_code);
    stmt->bindInt32(6, info->m_role);
    stmt->bindInt32(7, info->m_state);
    stmt->bindTime(8, info->m_loginTime);
    stmt->bindInt32(9, info->m_isDeleted);
    stmt->bindTime(10, info->m_createTime);
    stmt->bindInt64(11, info->m_uId);
    return stmt->execute();
}

int UserInfoDao::Insert(UserInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "insert into user (nick_name, avatar, email, password, code, role, state, login_time, is_deleted, create_time) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, info->m_nickName);
    stmt->bindString(2, info->m_avatar);
    stmt->bindString(3, info->m_email);
    stmt->bindString(4, info->m_password);
    stmt->bindString(5, info->m_code);
    stmt->bindInt32(6, info->m_role);
    stmt->bindInt32(7, info->m_state);
    stmt->bindTime(8, info->m_loginTime);
    stmt->bindInt32(9, info->m_isDeleted);
    stmt->bindTime(10, info->m_createTime);
    int rt = stmt->execute();
    if(rt == 0) {
        info->m_uId = conn->getLastInsertId();
    }
    return rt;
}

int UserInfoDao::InsertOrUpdate(UserInfo::ptr info, stone::IDB::ptr conn) {
    if(info->m_uId == 0) {
        return Insert(info, conn);
    }
    std::string sql = "replace into user (u_id, nick_name, avatar, email, password, code, role, state, login_time, is_deleted, create_time) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_uId);
    stmt->bindString(2, info->m_nickName);
    stmt->bindString(3, info->m_avatar);
    stmt->bindString(4, info->m_email);
    stmt->bindString(5, info->m_password);
    stmt->bindString(6, info->m_code);
    stmt->bindInt32(7, info->m_role);
    stmt->bindInt32(8, info->m_state);
    stmt->bindTime(9, info->m_loginTime);
    stmt->bindInt32(10, info->m_isDeleted);
    stmt->bindTime(11, info->m_createTime);
    return stmt->execute();
}

int UserInfoDao::Delete(UserInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "delete from user where u_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_uId);
    return stmt->execute();
}

int UserInfoDao::DeleteByUId( const int64_t& u_id, stone::IDB::ptr conn) {
    std::string sql = "delete from user where u_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, u_id);
    return stmt->execute();
}

int UserInfoDao::DeleteByEmail( const std::string& email, stone::IDB::ptr conn) {
    std::string sql = "delete from user where email = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, email);
    return stmt->execute();
}

int UserInfoDao::DeleteByNickName( const std::string& nick_name, stone::IDB::ptr conn) {
    std::string sql = "delete from user where nick_name = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, nick_name);
    return stmt->execute();
}

int UserInfoDao::QueryAll(std::vector<UserInfo::ptr>& results, stone::IDB::ptr conn) {
    std::string sql = "select u_id, nick_name, avatar, email, password, code, role, state, login_time, is_deleted, create_time from user";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    auto rt = stmt->query();
    if(!rt) {
        return stmt->getErrno();
    }
    while (rt->next()) {
        UserInfo::ptr v(new UserInfo);
        v->m_uId = rt->getInt64(0);
        v->m_nickName = rt->getString(1);
        v->m_avatar = rt->getString(2);
        v->m_email = rt->getString(3);
        v->m_password = rt->getString(4);
        v->m_code = rt->getString(5);
        v->m_role = rt->getInt32(6);
        v->m_state = rt->getInt32(7);
        v->m_loginTime = rt->getTime(8);
        v->m_isDeleted = rt->getInt32(9);
        v->m_createTime = rt->getTime(10);
        results.push_back(v);
    }
    return 0;
}

UserInfo::ptr UserInfoDao::Query( const int64_t& u_id, stone::IDB::ptr conn) {
    std::string sql = "select u_id, nick_name, avatar, email, password, code, role, state, login_time, is_deleted, create_time from user where u_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindInt64(1, u_id);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    UserInfo::ptr v(new UserInfo);
    v->m_uId = rt->getInt64(0);
    v->m_nickName = rt->getString(1);
    v->m_avatar = rt->getString(2);
    v->m_email = rt->getString(3);
    v->m_password = rt->getString(4);
    v->m_code = rt->getString(5);
    v->m_role = rt->getInt32(6);
    v->m_state = rt->getInt32(7);
    v->m_loginTime = rt->getTime(8);
    v->m_isDeleted = rt->getInt32(9);
    v->m_createTime = rt->getTime(10);
    return v;
}

UserInfo::ptr UserInfoDao::QueryByEmail( const std::string& email, stone::IDB::ptr conn) {
    std::string sql = "select u_id, nick_name, avatar, email, password, code, role, state, login_time, is_deleted, create_time from user where email = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindString(1, email);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    UserInfo::ptr v(new UserInfo);
    v->m_uId = rt->getInt64(0);
    v->m_nickName = rt->getString(1);
    v->m_avatar = rt->getString(2);
    v->m_email = rt->getString(3);
    v->m_password = rt->getString(4);
    v->m_code = rt->getString(5);
    v->m_role = rt->getInt32(6);
    v->m_state = rt->getInt32(7);
    v->m_loginTime = rt->getTime(8);
    v->m_isDeleted = rt->getInt32(9);
    v->m_createTime = rt->getTime(10);
    return v;
}

UserInfo::ptr UserInfoDao::QueryByNickName( const std::string& nick_name, stone::IDB::ptr conn) {
    std::string sql = "select u_id, nick_name, avatar, email, password, code, role, state, login_time, is_deleted, create_time from user where nick_name = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindString(1, nick_name);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    UserInfo::ptr v(new UserInfo);
    v->m_uId = rt->getInt64(0);
    v->m_nickName = rt->getString(1);
    v->m_avatar = rt->getString(2);
    v->m_email = rt->getString(3);
    v->m_password = rt->getString(4);
    v->m_code = rt->getString(5);
    v->m_role = rt->getInt32(6);
    v->m_state = rt->getInt32(7);
    v->m_loginTime = rt->getTime(8);
    v->m_isDeleted = rt->getInt32(9);
    v->m_createTime = rt->getTime(10);
    return v;
}

int UserInfoDao::CreateTableSQLite3(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE user("
            "u_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "nick_name TEXT NOT NULL DEFAULT '',"
            "avatar TEXT NOT NULL DEFAULT '',"
            "email TEXT NOT NULL DEFAULT '',"
            "password TEXT NOT NULL DEFAULT '',"
            "code TEXT NOT NULL DEFAULT '',"
            "role INTEGER NOT NULL DEFAULT 0,"
            "state INTEGER NOT NULL DEFAULT 0,"
            "login_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "is_deleted INTEGER NOT NULL DEFAULT 0,"
            "create_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00');"
            "CREATE UNIQUE INDEX user_email ON user(email);"
            "CREATE UNIQUE INDEX user_nick_name ON user(nick_name);"
            );
}

int UserInfoDao::CreateTableMySQL(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE user("
            "`u_id` bigint AUTO_INCREMENT COMMENT '用户id',"
            "`nick_name` varchar(30) NOT NULL DEFAULT '' COMMENT '昵称',"
            "`avatar` text NOT NULL DEFAULT '' COMMENT '用户头像',"
            "`email` varchar(50) NOT NULL DEFAULT '' COMMENT '邮箱地址',"
            "`password` varchar(50) NOT NULL DEFAULT '' COMMENT '密码',"
            "`code` varchar(20) NOT NULL DEFAULT '' COMMENT '验证码',"
            "`role` int NOT NULL DEFAULT 0 COMMENT '角色',"
            "`state` int NOT NULL DEFAULT 0 COMMENT '状态1未激活2激活',"
            "`login_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '登录时间',"
            "`is_deleted` int NOT NULL DEFAULT 0 COMMENT '是否删除',"
            "`create_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '注册时间',"
            "PRIMARY KEY(`u_id`),"
            "UNIQUE KEY `user_email` (`email`),"
            "UNIQUE KEY `user_nick_name` (`nick_name`)) COMMENT='用户表'");
}
} //namespace data
} //namespace blog
