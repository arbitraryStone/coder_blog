#include "user_friend_rel_info.hpp"
#include "src/log.hpp"

namespace blog {
namespace data {

static stone::Logger::ptr g_logger = STONE_LOG_NAME("orm");

UserFriendRelInfo::UserFriendRelInfo()
    :m_isDeleted()
    ,m_id()
    ,m_userId()
    ,m_friendId()
    ,m_createTime()
    ,m_updateTime() {
}

std::string UserFriendRelInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["id"] = std::to_string(m_id);
    jvalue["user_id"] = std::to_string(m_userId);
    jvalue["friend_id"] = std::to_string(m_friendId);
    jvalue["is_deleted"] = m_isDeleted;
    jvalue["create_time"] = stone::Time2Str(m_createTime);
    jvalue["update_time"] = stone::Time2Str(m_updateTime);
    return stone::JsonUtil::ToString(jvalue);
}

void UserFriendRelInfo::setId(const int64_t& v) {
    m_id = v;
}

void UserFriendRelInfo::setUserId(const int64_t& v) {
    m_userId = v;
}

void UserFriendRelInfo::setFriendId(const int64_t& v) {
    m_friendId = v;
}

void UserFriendRelInfo::setIsDeleted(const int32_t& v) {
    m_isDeleted = v;
}

void UserFriendRelInfo::setCreateTime(const int64_t& v) {
    m_createTime = v;
}

void UserFriendRelInfo::setUpdateTime(const int64_t& v) {
    m_updateTime = v;
}


int UserFriendRelInfoDao::Update(UserFriendRelInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "update user_friend_rel set user_id = ?, friend_id = ?, is_deleted = ?, create_time = ?, update_time = ? where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_userId);
    stmt->bindInt64(2, info->m_friendId);
    stmt->bindInt32(3, info->m_isDeleted);
    stmt->bindTime(4, info->m_createTime);
    stmt->bindTime(5, info->m_updateTime);
    stmt->bindInt64(6, info->m_id);
    return stmt->execute();
}

int UserFriendRelInfoDao::Insert(UserFriendRelInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "insert into user_friend_rel (user_id, friend_id, is_deleted, create_time, update_time) values (?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_userId);
    stmt->bindInt64(2, info->m_friendId);
    stmt->bindInt32(3, info->m_isDeleted);
    stmt->bindTime(4, info->m_createTime);
    stmt->bindTime(5, info->m_updateTime);
    int rt = stmt->execute();
    if(rt == 0) {
        info->m_id = conn->getLastInsertId();
    }
    return rt;
}

int UserFriendRelInfoDao::InsertOrUpdate(UserFriendRelInfo::ptr info, stone::IDB::ptr conn) {
    if(info->m_id == 0) {
        return Insert(info, conn);
    }
    std::string sql = "replace into user_friend_rel (id, user_id, friend_id, is_deleted, create_time, update_time) values (?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    stmt->bindInt64(2, info->m_userId);
    stmt->bindInt64(3, info->m_friendId);
    stmt->bindInt32(4, info->m_isDeleted);
    stmt->bindTime(5, info->m_createTime);
    stmt->bindTime(6, info->m_updateTime);
    return stmt->execute();
}

int UserFriendRelInfoDao::Delete(UserFriendRelInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "delete from user_friend_rel where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    return stmt->execute();
}

int UserFriendRelInfoDao::DeleteById( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "delete from user_friend_rel where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, id);
    return stmt->execute();
}

int UserFriendRelInfoDao::DeleteByUserId( const int64_t& user_id, stone::IDB::ptr conn) {
    std::string sql = "delete from user_friend_rel where user_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, user_id);
    return stmt->execute();
}

int UserFriendRelInfoDao::DeleteByUserIdFriendId( const int64_t& user_id,  const int64_t& friend_id, stone::IDB::ptr conn) {
    std::string sql = "delete from user_friend_rel where user_id = ? and friend_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, user_id);
    stmt->bindInt64(1, friend_id);
    return stmt->execute();
}

int UserFriendRelInfoDao::QueryAll(std::vector<UserFriendRelInfo::ptr>& results, stone::IDB::ptr conn) {
    std::string sql = "select id, user_id, friend_id, is_deleted, create_time, update_time from user_friend_rel";
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
        UserFriendRelInfo::ptr v(new UserFriendRelInfo);
        v->m_id = rt->getInt64(0);
        v->m_userId = rt->getInt64(1);
        v->m_friendId = rt->getInt64(2);
        v->m_isDeleted = rt->getInt32(3);
        v->m_createTime = rt->getTime(4);
        v->m_updateTime = rt->getTime(5);
        results.push_back(v);
    }
    return 0;
}

UserFriendRelInfo::ptr UserFriendRelInfoDao::Query( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "select id, user_id, friend_id, is_deleted, create_time, update_time from user_friend_rel where id = ?";
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
    UserFriendRelInfo::ptr v(new UserFriendRelInfo);
    v->m_id = rt->getInt64(0);
    v->m_userId = rt->getInt64(1);
    v->m_friendId = rt->getInt64(2);
    v->m_isDeleted = rt->getInt32(3);
    v->m_createTime = rt->getTime(4);
    v->m_updateTime = rt->getTime(5);
    return v;
}

int UserFriendRelInfoDao::QueryByUserId(std::vector<UserFriendRelInfo::ptr>& results,  const int64_t& user_id, stone::IDB::ptr conn) {
    std::string sql = "select id, user_id, friend_id, is_deleted, create_time, update_time from user_friend_rel where user_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, user_id);
    auto rt = stmt->query();
    if(!rt) {
        return 0;
    }
    while (rt->next()) {
        UserFriendRelInfo::ptr v(new UserFriendRelInfo);
        v->m_id = rt->getInt64(0);
        v->m_userId = rt->getInt64(1);
        v->m_friendId = rt->getInt64(2);
        v->m_isDeleted = rt->getInt32(3);
        v->m_createTime = rt->getTime(4);
        v->m_updateTime = rt->getTime(5);
        results.push_back(v);
    };
    return 0;
}

UserFriendRelInfo::ptr UserFriendRelInfoDao::QueryByUserIdFriendId( const int64_t& user_id,  const int64_t& friend_id, stone::IDB::ptr conn) {
    std::string sql = "select id, user_id, friend_id, is_deleted, create_time, update_time from user_friend_rel where user_id = ? and friend_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindInt64(1, user_id);
    stmt->bindInt64(2, friend_id);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    UserFriendRelInfo::ptr v(new UserFriendRelInfo);
    v->m_id = rt->getInt64(0);
    v->m_userId = rt->getInt64(1);
    v->m_friendId = rt->getInt64(2);
    v->m_isDeleted = rt->getInt32(3);
    v->m_createTime = rt->getTime(4);
    v->m_updateTime = rt->getTime(5);
    return v;
}

int UserFriendRelInfoDao::CreateTableSQLite3(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE user_friend_rel("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "user_id INTEGER NOT NULL DEFAULT 0,"
            "friend_id INTEGER NOT NULL DEFAULT 0,"
            "is_deleted INTEGER NOT NULL DEFAULT 0,"
            "create_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "update_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00');"
            "CREATE INDEX user_friend_rel_user_id ON user_friend_rel(user_id);"
            "CREATE UNIQUE INDEX user_friend_rel_user_id_friend_id ON user_friend_rel(user_id,friend_id);"
            );
}

int UserFriendRelInfoDao::CreateTableMySQL(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE user_friend_rel("
            "`id` bigint AUTO_INCREMENT COMMENT '自增长id',"
            "`user_id` bigint NOT NULL DEFAULT 0 COMMENT '用户id',"
            "`friend_id` bigint NOT NULL DEFAULT 0 COMMENT '好友id',"
            "`is_deleted` int NOT NULL DEFAULT 0 COMMENT '是否删除',"
            "`create_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '创建时间',"
            "`update_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' ON UPDATE current_timestamp  COMMENT '更新时间',"
            "PRIMARY KEY(`id`),"
            "KEY `user_friend_rel_user_id` (`user_id`),"
            "UNIQUE KEY `user_friend_rel_user_id_friend_id` (`user_id`,`friend_id`)) COMMENT='用户好友关系表'");
}
} //namespace data
} //namespace blog
