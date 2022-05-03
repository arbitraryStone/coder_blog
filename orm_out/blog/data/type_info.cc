#include "type_info.h"
#include "src/log.hpp"

namespace blog {
namespace data {

static stone::Logger::ptr g_logger = STONE_LOG_NAME("orm");

TypeInfo::TypeInfo()
    :m_id()
    ,m_typeName()
    ,m_createTime()
    ,m_updateTime() {
}

std::string TypeInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["id"] = std::to_string(m_id);
    jvalue["type_name"] = m_typeName;
    jvalue["create_time"] = stone::Time2Str(m_createTime);
    jvalue["update_time"] = stone::Time2Str(m_updateTime);
    return stone::JsonUtil::ToString(jvalue);
}

void TypeInfo::setId(const int64_t& v) {
    m_id = v;
}

void TypeInfo::setTypeName(const std::string& v) {
    m_typeName = v;
}

void TypeInfo::setCreateTime(const int64_t& v) {
    m_createTime = v;
}

void TypeInfo::setUpdateTime(const int64_t& v) {
    m_updateTime = v;
}


int TypeInfoDao::Update(TypeInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "update type set type_name = ?, create_time = ?, update_time = ? where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, info->m_typeName);
    stmt->bindTime(2, info->m_createTime);
    stmt->bindTime(3, info->m_updateTime);
    stmt->bindInt64(4, info->m_id);
    return stmt->execute();
}

int TypeInfoDao::Insert(TypeInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "insert into type (type_name, create_time, update_time) values (?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, info->m_typeName);
    stmt->bindTime(2, info->m_createTime);
    stmt->bindTime(3, info->m_updateTime);
    int rt = stmt->execute();
    if(rt == 0) {
        info->m_id = conn->getLastInsertId();
    }
    return rt;
}

int TypeInfoDao::InsertOrUpdate(TypeInfo::ptr info, stone::IDB::ptr conn) {
    if(info->m_id == 0) {
        return Insert(info, conn);
    }
    std::string sql = "replace into type (id, type_name, create_time, update_time) values (?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    stmt->bindString(2, info->m_typeName);
    stmt->bindTime(3, info->m_createTime);
    stmt->bindTime(4, info->m_updateTime);
    return stmt->execute();
}

int TypeInfoDao::Delete(TypeInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "delete from type where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    return stmt->execute();
}

int TypeInfoDao::DeleteById( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "delete from type where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, id);
    return stmt->execute();
}

int TypeInfoDao::DeleteByTypeName( const std::string& type_name, stone::IDB::ptr conn) {
    std::string sql = "delete from type where type_name = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, type_name);
    return stmt->execute();
}

int TypeInfoDao::QueryAll(std::vector<TypeInfo::ptr>& results, stone::IDB::ptr conn) {
    std::string sql = "select id, type_name, create_time, update_time from type";
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
        TypeInfo::ptr v(new TypeInfo);
        v->m_id = rt->getInt64(0);
        v->m_typeName = rt->getString(1);
        v->m_createTime = rt->getTime(2);
        v->m_updateTime = rt->getTime(3);
        results.push_back(v);
    }
    return 0;
}

TypeInfo::ptr TypeInfoDao::Query( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "select id, type_name, create_time, update_time from type where id = ?";
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
    TypeInfo::ptr v(new TypeInfo);
    v->m_id = rt->getInt64(0);
    v->m_typeName = rt->getString(1);
    v->m_createTime = rt->getTime(2);
    v->m_updateTime = rt->getTime(3);
    return v;
}

TypeInfo::ptr TypeInfoDao::QueryByTypeName( const std::string& type_name, stone::IDB::ptr conn) {
    std::string sql = "select id, type_name, create_time, update_time from type where type_name = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindString(1, type_name);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    TypeInfo::ptr v(new TypeInfo);
    v->m_id = rt->getInt64(0);
    v->m_typeName = rt->getString(1);
    v->m_createTime = rt->getTime(2);
    v->m_updateTime = rt->getTime(3);
    return v;
}

int TypeInfoDao::CreateTableSQLite3(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE type("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "type_name TEXT NOT NULL DEFAULT '',"
            "create_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "update_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00');"
            "CREATE UNIQUE INDEX type_type_name ON type(type_name);"
            );
}

int TypeInfoDao::CreateTableMySQL(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE type("
            "`id` bigint AUTO_INCREMENT COMMENT '自增id',"
            "`type_name` varchar(50) NOT NULL DEFAULT '' COMMENT '分类名称',"
            "`create_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '创建时间',"
            "`update_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' ON UPDATE current_timestamp  COMMENT '更新时间',"
            "PRIMARY KEY(`id`),"
            "UNIQUE KEY `type_type_name` (`type_name`)) COMMENT='博客分类表'");
}
} //namespace data
} //namespace blog
