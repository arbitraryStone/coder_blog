#include "tag_info.h"
#include "src/log.hpp"

namespace blog {
namespace data {

static stone::Logger::ptr g_logger = STONE_LOG_NAME("orm");

TagInfo::TagInfo()
    :m_id()
    ,m_tagName()
    ,m_createTime()
    ,m_updateTime() {
}

std::string TagInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["id"] = std::to_string(m_id);
    jvalue["tag_name"] = m_tagName;
    jvalue["create_time"] = stone::Time2Str(m_createTime);
    jvalue["update_time"] = stone::Time2Str(m_updateTime);
    return stone::JsonUtil::ToString(jvalue);
}

void TagInfo::setId(const int64_t& v) {
    m_id = v;
}

void TagInfo::setTagName(const std::string& v) {
    m_tagName = v;
}

void TagInfo::setCreateTime(const int64_t& v) {
    m_createTime = v;
}

void TagInfo::setUpdateTime(const int64_t& v) {
    m_updateTime = v;
}


int TagInfoDao::Update(TagInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "update tag set tag_name = ?, create_time = ?, update_time = ? where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, info->m_tagName);
    stmt->bindTime(2, info->m_createTime);
    stmt->bindTime(3, info->m_updateTime);
    stmt->bindInt64(4, info->m_id);
    return stmt->execute();
}

int TagInfoDao::Insert(TagInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "insert into tag (tag_name, create_time, update_time) values (?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, info->m_tagName);
    stmt->bindTime(2, info->m_createTime);
    stmt->bindTime(3, info->m_updateTime);
    int rt = stmt->execute();
    if(rt == 0) {
        info->m_id = conn->getLastInsertId();
    }
    return rt;
}

int TagInfoDao::InsertOrUpdate(TagInfo::ptr info, stone::IDB::ptr conn) {
    if(info->m_id == 0) {
        return Insert(info, conn);
    }
    std::string sql = "replace into tag (id, tag_name, create_time, update_time) values (?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    stmt->bindString(2, info->m_tagName);
    stmt->bindTime(3, info->m_createTime);
    stmt->bindTime(4, info->m_updateTime);
    return stmt->execute();
}

int TagInfoDao::Delete(TagInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "delete from tag where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    return stmt->execute();
}

int TagInfoDao::DeleteById( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "delete from tag where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, id);
    return stmt->execute();
}

int TagInfoDao::DeleteByTagName( const std::string& tag_name, stone::IDB::ptr conn) {
    std::string sql = "delete from tag where tag_name = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, tag_name);
    return stmt->execute();
}

int TagInfoDao::QueryAll(std::vector<TagInfo::ptr>& results, stone::IDB::ptr conn) {
    std::string sql = "select id, tag_name, create_time, update_time from tag";
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
        TagInfo::ptr v(new TagInfo);
        v->m_id = rt->getInt64(0);
        v->m_tagName = rt->getString(1);
        v->m_createTime = rt->getTime(2);
        v->m_updateTime = rt->getTime(3);
        results.push_back(v);
    }
    return 0;
}

TagInfo::ptr TagInfoDao::Query( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "select id, tag_name, create_time, update_time from tag where id = ?";
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
    TagInfo::ptr v(new TagInfo);
    v->m_id = rt->getInt64(0);
    v->m_tagName = rt->getString(1);
    v->m_createTime = rt->getTime(2);
    v->m_updateTime = rt->getTime(3);
    return v;
}

TagInfo::ptr TagInfoDao::QueryByTagName( const std::string& tag_name, stone::IDB::ptr conn) {
    std::string sql = "select id, tag_name, create_time, update_time from tag where tag_name = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindString(1, tag_name);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    TagInfo::ptr v(new TagInfo);
    v->m_id = rt->getInt64(0);
    v->m_tagName = rt->getString(1);
    v->m_createTime = rt->getTime(2);
    v->m_updateTime = rt->getTime(3);
    return v;
}

int TagInfoDao::CreateTableSQLite3(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE tag("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "tag_name TEXT NOT NULL DEFAULT '',"
            "create_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "update_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00');"
            "CREATE UNIQUE INDEX tag_tag_name ON tag(tag_name);"
            );
}

int TagInfoDao::CreateTableMySQL(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE tag("
            "`id` bigint AUTO_INCREMENT COMMENT '标签id',"
            "`tag_name` varchar(50) NOT NULL DEFAULT '' COMMENT '标签名称',"
            "`create_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '创建时间',"
            "`update_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '更新时间',"
            "PRIMARY KEY(`id`),"
            "UNIQUE KEY `tag_tag_name` (`tag_name`)) COMMENT='文章标签'");
}
} //namespace data
} //namespace blog
