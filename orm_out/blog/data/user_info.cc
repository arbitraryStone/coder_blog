#include "user_info.h"
#include "src/log.hpp"

namespace blog {
namespace data {

static stone::Logger::ptr g_logger = STONE_LOG_NAME("orm");

UserInfo::UserInfo()
    :m_id()
    ,m_nickname()
    ,m_email()
    ,m_password()
    ,m_picture()
    ,m_username()
    ,m_createTime()
    ,m_updateTime() {
}

std::string UserInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["id"] = std::to_string(m_id);
    jvalue["nickname"] = m_nickname;
    jvalue["email"] = m_email;
    jvalue["password"] = m_password;
    jvalue["picture"] = m_picture;
    jvalue["username"] = m_username;
    jvalue["create_time"] = stone::Time2Str(m_createTime);
    jvalue["update_time"] = stone::Time2Str(m_updateTime);
    return stone::JsonUtil::ToString(jvalue);
}

void UserInfo::setId(const int64_t& v) {
    m_id = v;
}

void UserInfo::setNickname(const std::string& v) {
    m_nickname = v;
}

void UserInfo::setEmail(const std::string& v) {
    m_email = v;
}

void UserInfo::setPassword(const std::string& v) {
    m_password = v;
}

void UserInfo::setPicture(const std::string& v) {
    m_picture = v;
}

void UserInfo::setUsername(const std::string& v) {
    m_username = v;
}

void UserInfo::setCreateTime(const int64_t& v) {
    m_createTime = v;
}

void UserInfo::setUpdateTime(const int64_t& v) {
    m_updateTime = v;
}


int UserInfoDao::Update(UserInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "update user set nickname = ?, email = ?, password = ?, picture = ?, username = ?, create_time = ?, update_time = ? where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, info->m_nickname);
    stmt->bindString(2, info->m_email);
    stmt->bindString(3, info->m_password);
    stmt->bindString(4, info->m_picture);
    stmt->bindString(5, info->m_username);
    stmt->bindTime(6, info->m_createTime);
    stmt->bindTime(7, info->m_updateTime);
    stmt->bindInt64(8, info->m_id);
    return stmt->execute();
}

int UserInfoDao::Insert(UserInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "insert into user (nickname, email, password, picture, username, create_time, update_time) values (?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, info->m_nickname);
    stmt->bindString(2, info->m_email);
    stmt->bindString(3, info->m_password);
    stmt->bindString(4, info->m_picture);
    stmt->bindString(5, info->m_username);
    stmt->bindTime(6, info->m_createTime);
    stmt->bindTime(7, info->m_updateTime);
    int rt = stmt->execute();
    if(rt == 0) {
        info->m_id = conn->getLastInsertId();
    }
    return rt;
}

int UserInfoDao::InsertOrUpdate(UserInfo::ptr info, stone::IDB::ptr conn) {
    if(info->m_id == 0) {
        return Insert(info, conn);
    }
    std::string sql = "replace into user (id, nickname, email, password, picture, username, create_time, update_time) values (?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    stmt->bindString(2, info->m_nickname);
    stmt->bindString(3, info->m_email);
    stmt->bindString(4, info->m_password);
    stmt->bindString(5, info->m_picture);
    stmt->bindString(6, info->m_username);
    stmt->bindTime(7, info->m_createTime);
    stmt->bindTime(8, info->m_updateTime);
    return stmt->execute();
}

int UserInfoDao::Delete(UserInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "delete from user where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    return stmt->execute();
}

int UserInfoDao::DeleteById( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "delete from user where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, id);
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

int UserInfoDao::DeleteByUsername( const std::string& username, stone::IDB::ptr conn) {
    std::string sql = "delete from user where username = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, username);
    return stmt->execute();
}

int UserInfoDao::QueryAll(std::vector<UserInfo::ptr>& results, stone::IDB::ptr conn) {
    std::string sql = "select id, nickname, email, password, picture, username, create_time, update_time from user";
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
        v->m_id = rt->getInt64(0);
        v->m_nickname = rt->getString(1);
        v->m_email = rt->getString(2);
        v->m_password = rt->getString(3);
        v->m_picture = rt->getString(4);
        v->m_username = rt->getString(5);
        v->m_createTime = rt->getTime(6);
        v->m_updateTime = rt->getTime(7);
        results.push_back(v);
    }
    return 0;
}

UserInfo::ptr UserInfoDao::Query( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "select id, nickname, email, password, picture, username, create_time, update_time from user where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindInt64(1, id);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    UserInfo::ptr v(new UserInfo);
    v->m_id = rt->getInt64(0);
    v->m_nickname = rt->getString(1);
    v->m_email = rt->getString(2);
    v->m_password = rt->getString(3);
    v->m_picture = rt->getString(4);
    v->m_username = rt->getString(5);
    v->m_createTime = rt->getTime(6);
    v->m_updateTime = rt->getTime(7);
    return v;
}

UserInfo::ptr UserInfoDao::QueryByEmail( const std::string& email, stone::IDB::ptr conn) {
    std::string sql = "select id, nickname, email, password, picture, username, create_time, update_time from user where email = ?";
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
    v->m_id = rt->getInt64(0);
    v->m_nickname = rt->getString(1);
    v->m_email = rt->getString(2);
    v->m_password = rt->getString(3);
    v->m_picture = rt->getString(4);
    v->m_username = rt->getString(5);
    v->m_createTime = rt->getTime(6);
    v->m_updateTime = rt->getTime(7);
    return v;
}

UserInfo::ptr UserInfoDao::QueryByUsername( const std::string& username, stone::IDB::ptr conn) {
    std::string sql = "select id, nickname, email, password, picture, username, create_time, update_time from user where username = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindString(1, username);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    UserInfo::ptr v(new UserInfo);
    v->m_id = rt->getInt64(0);
    v->m_nickname = rt->getString(1);
    v->m_email = rt->getString(2);
    v->m_password = rt->getString(3);
    v->m_picture = rt->getString(4);
    v->m_username = rt->getString(5);
    v->m_createTime = rt->getTime(6);
    v->m_updateTime = rt->getTime(7);
    return v;
}

int UserInfoDao::CreateTableSQLite3(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE user("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "nickname TEXT NOT NULL DEFAULT '',"
            "email TEXT NOT NULL DEFAULT '',"
            "password TEXT NOT NULL DEFAULT '',"
            "picture TEXT NOT NULL DEFAULT '',"
            "username TEXT NOT NULL DEFAULT '',"
            "create_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "update_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00');"
            "CREATE UNIQUE INDEX user_email ON user(email);"
            "CREATE UNIQUE INDEX user_username ON user(username);"
            );
}

int UserInfoDao::CreateTableMySQL(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE user("
            "`id` bigint AUTO_INCREMENT COMMENT '用户id',"
            "`nickname` varchar(30) NOT NULL DEFAULT '' COMMENT '昵称',"
            "`email` varchar(50) NOT NULL DEFAULT '' COMMENT '邮件地址',"
            "`password` varchar(50) NOT NULL DEFAULT '' COMMENT '密码',"
            "`picture` varchar(100) NOT NULL DEFAULT '' COMMENT '头像',"
            "`username` varchar(30) NOT NULL DEFAULT '' COMMENT '用户名',"
            "`create_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '创建时间',"
            "`update_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' ON UPDATE current_timestamp  COMMENT '修改时间',"
            "PRIMARY KEY(`id`),"
            "UNIQUE KEY `user_email` (`email`),"
            "UNIQUE KEY `user_username` (`username`)) COMMENT='用户表'");
}
} //namespace data
} //namespace blog
