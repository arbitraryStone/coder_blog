#include "classification_info.hpp"
#include "src/log.hpp"

namespace blog {
namespace data {

static stone::Logger::ptr g_logger = STONE_LOG_NAME("orm");

ClassificationInfo::ClassificationInfo()
    :m_isDeleted()
    ,m_classId()
    ,m_name()
    ,m_createTime() {
}

std::string ClassificationInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["class_id"] = std::to_string(m_classId);
    jvalue["name"] = m_name;
    jvalue["is_deleted"] = m_isDeleted;
    jvalue["create_time"] = stone::Time2Str(m_createTime);
    return stone::JsonUtil::ToString(jvalue);
}

void ClassificationInfo::setClassId(const int64_t& v) {
    m_classId = v;
}

void ClassificationInfo::setName(const std::string& v) {
    m_name = v;
}

void ClassificationInfo::setIsDeleted(const int32_t& v) {
    m_isDeleted = v;
}

void ClassificationInfo::setCreateTime(const int64_t& v) {
    m_createTime = v;
}


int ClassificationInfoDao::Update(ClassificationInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "update classification set name = ?, is_deleted = ?, create_time = ? where class_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, info->m_name);
    stmt->bindInt32(2, info->m_isDeleted);
    stmt->bindTime(3, info->m_createTime);
    stmt->bindInt64(4, info->m_classId);
    return stmt->execute();
}

int ClassificationInfoDao::Insert(ClassificationInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "insert into classification (name, is_deleted, create_time) values (?, ?, ?)";
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
        info->m_classId = conn->getLastInsertId();
    }
    return rt;
}

int ClassificationInfoDao::InsertOrUpdate(ClassificationInfo::ptr info, stone::IDB::ptr conn) {
    if(info->m_classId == 0) {
        return Insert(info, conn);
    }
    std::string sql = "replace into classification (class_id, name, is_deleted, create_time) values (?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_classId);
    stmt->bindString(2, info->m_name);
    stmt->bindInt32(3, info->m_isDeleted);
    stmt->bindTime(4, info->m_createTime);
    return stmt->execute();
}

int ClassificationInfoDao::Delete(ClassificationInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "delete from classification where class_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_classId);
    return stmt->execute();
}

int ClassificationInfoDao::DeleteByClassId( const int64_t& class_id, stone::IDB::ptr conn) {
    std::string sql = "delete from classification where class_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, class_id);
    return stmt->execute();
}

int ClassificationInfoDao::DeleteByName( const std::string& name, stone::IDB::ptr conn) {
    std::string sql = "delete from classification where name = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindString(1, name);
    return stmt->execute();
}

int ClassificationInfoDao::QueryAll(std::vector<ClassificationInfo::ptr>& results, stone::IDB::ptr conn) {
    std::string sql = "select class_id, name, is_deleted, create_time from classification";
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
        ClassificationInfo::ptr v(new ClassificationInfo);
        v->m_classId = rt->getInt64(0);
        v->m_name = rt->getString(1);
        v->m_isDeleted = rt->getInt32(2);
        v->m_createTime = rt->getTime(3);
        results.push_back(v);
    }
    return 0;
}

ClassificationInfo::ptr ClassificationInfoDao::Query( const int64_t& class_id, stone::IDB::ptr conn) {
    std::string sql = "select class_id, name, is_deleted, create_time from classification where class_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindInt64(1, class_id);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    ClassificationInfo::ptr v(new ClassificationInfo);
    v->m_classId = rt->getInt64(0);
    v->m_name = rt->getString(1);
    v->m_isDeleted = rt->getInt32(2);
    v->m_createTime = rt->getTime(3);
    return v;
}

ClassificationInfo::ptr ClassificationInfoDao::QueryByName( const std::string& name, stone::IDB::ptr conn) {
    std::string sql = "select class_id, name, is_deleted, create_time from classification where name = ?";
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
    ClassificationInfo::ptr v(new ClassificationInfo);
    v->m_classId = rt->getInt64(0);
    v->m_name = rt->getString(1);
    v->m_isDeleted = rt->getInt32(2);
    v->m_createTime = rt->getTime(3);
    return v;
}

int ClassificationInfoDao::CreateTableSQLite3(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE classification("
            "class_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name TEXT NOT NULL DEFAULT '',"
            "is_deleted INTEGER NOT NULL DEFAULT 0,"
            "create_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00');"
            "CREATE UNIQUE INDEX classification_name ON classification(name);"
            );
}

int ClassificationInfoDao::CreateTableMySQL(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE classification("
            "`class_id` bigint AUTO_INCREMENT COMMENT '类目id',"
            "`name` varchar(100) NOT NULL DEFAULT '' COMMENT '名称',"
            "`is_deleted` int NOT NULL DEFAULT 0 COMMENT '是否删除',"
            "`create_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '创建时间',"
            "PRIMARY KEY(`class_id`),"
            "UNIQUE KEY `classification_name` (`name`)) COMMENT='类目表'");
}
} //namespace data
} //namespace blog
