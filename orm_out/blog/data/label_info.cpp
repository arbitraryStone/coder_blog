#include "label_info.hpp"
#include "src/log.hpp"

namespace blog {
namespace data {

static stone::Logger::ptr g_logger = STONE_LOG_NAME("orm");

LabelInfo::LabelInfo()
    :m_isDeleted()
    ,m_lId()
    ,m_name()
    ,m_createTime() {
}

std::string LabelInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["l_id"] = std::to_string(m_lId);
    jvalue["name"] = m_name;
    jvalue["is_deleted"] = m_isDeleted;
    jvalue["create_time"] = stone::Time2Str(m_createTime);
    return stone::JsonUtil::ToString(jvalue);
}

void LabelInfo::setLId(const int64_t& v) {
    m_lId = v;
}

void LabelInfo::setName(const std::string& v) {
    m_name = v;
}

void LabelInfo::setIsDeleted(const int32_t& v) {
    m_isDeleted = v;
}

void LabelInfo::setCreateTime(const int64_t& v) {
    m_createTime = v;
}


int LabelInfoDao::Update(LabelInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "update label set name = ?, is_deleted = ?, create_time = ? where l_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, info->m_name);
    stmt->bindInt32(2, info->m_isDeleted);
    stmt->bindTime(3, info->m_createTime);
    stmt->bindInt64(4, info->m_lId);
    return stmt->execute();
}

int LabelInfoDao::Insert(LabelInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "insert into label (name, is_deleted, create_time) values (?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, info->m_name);
    stmt->bindInt32(2, info->m_isDeleted);
    stmt->bindTime(3, info->m_createTime);
    int rt = stmt->execute();
    if(rt == 0) {
        info->m_lId = conn->getLastInsertId();
    }
    return rt;
}

int LabelInfoDao::InsertOrUpdate(LabelInfo::ptr info, stone::IDB::ptr conn) {
    if(info->m_lId == 0) {
        return Insert(info, conn);
    }
    std::string sql = "replace into label (l_id, name, is_deleted, create_time) values (?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_lId);
    stmt->bindString(2, info->m_name);
    stmt->bindInt32(3, info->m_isDeleted);
    stmt->bindTime(4, info->m_createTime);
    return stmt->execute();
}

int LabelInfoDao::Delete(LabelInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "delete from label where l_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_lId);
    return stmt->execute();
}

int LabelInfoDao::DeleteByLId( const int64_t& l_id, stone::IDB::ptr conn) {
    std::string sql = "delete from label where l_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, l_id);
    return stmt->execute();
}

int LabelInfoDao::DeleteByName( const std::string& name, stone::IDB::ptr conn) {
    std::string sql = "delete from label where name = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, name);
    return stmt->execute();
}

int LabelInfoDao::QueryAll(std::vector<LabelInfo::ptr>& results, stone::IDB::ptr conn) {
    std::string sql = "select l_id, name, is_deleted, create_time from label";
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
        LabelInfo::ptr v(new LabelInfo);
        v->m_lId = rt->getInt64(0);
        v->m_name = rt->getString(1);
        v->m_isDeleted = rt->getInt32(2);
        v->m_createTime = rt->getTime(3);
        results.push_back(v);
    }
    return 0;
}

LabelInfo::ptr LabelInfoDao::Query( const int64_t& l_id, stone::IDB::ptr conn) {
    std::string sql = "select l_id, name, is_deleted, create_time from label where l_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindInt64(1, l_id);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    LabelInfo::ptr v(new LabelInfo);
    v->m_lId = rt->getInt64(0);
    v->m_name = rt->getString(1);
    v->m_isDeleted = rt->getInt32(2);
    v->m_createTime = rt->getTime(3);
    return v;
}

LabelInfo::ptr LabelInfoDao::QueryByName( const std::string& name, stone::IDB::ptr conn) {
    std::string sql = "select l_id, name, is_deleted, create_time from label where name = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindString(1, name);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    LabelInfo::ptr v(new LabelInfo);
    v->m_lId = rt->getInt64(0);
    v->m_name = rt->getString(1);
    v->m_isDeleted = rt->getInt32(2);
    v->m_createTime = rt->getTime(3);
    return v;
}

int LabelInfoDao::CreateTableSQLite3(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE label("
            "l_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL DEFAULT '',"
            "is_deleted INTEGER NOT NULL DEFAULT 0,"
            "create_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00');"
            "CREATE UNIQUE INDEX label_name ON label(name);"
            );
}

int LabelInfoDao::CreateTableMySQL(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE label("
            "`l_id` bigint AUTO_INCREMENT COMMENT '标签id',"
            "`name` varchar(100) NOT NULL DEFAULT '' COMMENT '名称',"
            "`is_deleted` int NOT NULL DEFAULT 0 COMMENT '是否删除',"
            "`create_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '创建时间',"
            "PRIMARY KEY(`l_id`),"
            "UNIQUE KEY `label_name` (`name`)) COMMENT='标签表'");
}
} //namespace data
} //namespace blog
