#include "article_class_rel_info.hpp"
#include "src/log.hpp"

namespace blog {
namespace data {

static stone::Logger::ptr g_logger = STONE_LOG_NAME("orm");

ArticleClassRelInfo::ArticleClassRelInfo()
    :m_isDeleted()
    ,m_id()
    ,m_articleId()
    ,m_classId()
    ,m_createTime()
    ,m_updateTime() {
}

std::string ArticleClassRelInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["id"] = std::to_string(m_id);
    jvalue["article_id"] = std::to_string(m_articleId);
    jvalue["class_id"] = std::to_string(m_classId);
    jvalue["is_deleted"] = m_isDeleted;
    jvalue["create_time"] = stone::Time2Str(m_createTime);
    jvalue["update_time"] = stone::Time2Str(m_updateTime);
    return stone::JsonUtil::ToString(jvalue);
}

void ArticleClassRelInfo::setId(const int64_t& v) {
    m_id = v;
}

void ArticleClassRelInfo::setArticleId(const int64_t& v) {
    m_articleId = v;
}

void ArticleClassRelInfo::setClassId(const int64_t& v) {
    m_classId = v;
}

void ArticleClassRelInfo::setIsDeleted(const int32_t& v) {
    m_isDeleted = v;
}

void ArticleClassRelInfo::setCreateTime(const int64_t& v) {
    m_createTime = v;
}

void ArticleClassRelInfo::setUpdateTime(const int64_t& v) {
    m_updateTime = v;
}


int ArticleClassRelInfoDao::Update(ArticleClassRelInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "update article_class_rel set article_id = ?, class_id = ?, is_deleted = ?, create_time = ?, update_time = ? where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_articleId);
    stmt->bindInt64(2, info->m_classId);
    stmt->bindInt32(3, info->m_isDeleted);
    stmt->bindTime(4, info->m_createTime);
    stmt->bindTime(5, info->m_updateTime);
    stmt->bindInt64(6, info->m_id);
    return stmt->execute();
}

int ArticleClassRelInfoDao::Insert(ArticleClassRelInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "insert into article_class_rel (article_id, class_id, is_deleted, create_time, update_time) values (?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_articleId);
    stmt->bindInt64(2, info->m_classId);
    stmt->bindInt32(3, info->m_isDeleted);
    stmt->bindTime(4, info->m_createTime);
    stmt->bindTime(5, info->m_updateTime);
    int rt = stmt->execute();
    if(rt == 0) {
        info->m_id = conn->getLastInsertId();
    }
    return rt;
}

int ArticleClassRelInfoDao::InsertOrUpdate(ArticleClassRelInfo::ptr info, stone::IDB::ptr conn) {
    if(info->m_id == 0) {
        return Insert(info, conn);
    }
    std::string sql = "replace into article_class_rel (id, article_id, class_id, is_deleted, create_time, update_time) values (?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    stmt->bindInt64(2, info->m_articleId);
    stmt->bindInt64(3, info->m_classId);
    stmt->bindInt32(4, info->m_isDeleted);
    stmt->bindTime(5, info->m_createTime);
    stmt->bindTime(6, info->m_updateTime);
    return stmt->execute();
}

int ArticleClassRelInfoDao::Delete(ArticleClassRelInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "delete from article_class_rel where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    return stmt->execute();
}

int ArticleClassRelInfoDao::DeleteById( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "delete from article_class_rel where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, id);
    return stmt->execute();
}

int ArticleClassRelInfoDao::DeleteByArticleId( const int64_t& article_id, stone::IDB::ptr conn) {
    std::string sql = "delete from article_class_rel where article_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, article_id);
    return stmt->execute();
}

int ArticleClassRelInfoDao::DeleteByClassId( const int64_t& class_id, stone::IDB::ptr conn) {
    std::string sql = "delete from article_class_rel where class_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, class_id);
    return stmt->execute();
}

int ArticleClassRelInfoDao::DeleteByArticleIdClassId( const int64_t& article_id,  const int64_t& class_id, stone::IDB::ptr conn) {
    std::string sql = "delete from article_class_rel where article_id = ? and class_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, article_id);
    stmt->bindInt64(1, class_id);
    return stmt->execute();
}

int ArticleClassRelInfoDao::QueryAll(std::vector<ArticleClassRelInfo::ptr>& results, stone::IDB::ptr conn) {
    std::string sql = "select id, article_id, class_id, is_deleted, create_time, update_time from article_class_rel";
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
        ArticleClassRelInfo::ptr v(new ArticleClassRelInfo);
        v->m_id = rt->getInt64(0);
        v->m_articleId = rt->getInt64(1);
        v->m_classId = rt->getInt64(2);
        v->m_isDeleted = rt->getInt32(3);
        v->m_createTime = rt->getTime(4);
        v->m_updateTime = rt->getTime(5);
        results.push_back(v);
    }
    return 0;
}

ArticleClassRelInfo::ptr ArticleClassRelInfoDao::Query( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "select id, article_id, class_id, is_deleted, create_time, update_time from article_class_rel where id = ?";
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
    ArticleClassRelInfo::ptr v(new ArticleClassRelInfo);
    v->m_id = rt->getInt64(0);
    v->m_articleId = rt->getInt64(1);
    v->m_classId = rt->getInt64(2);
    v->m_isDeleted = rt->getInt32(3);
    v->m_createTime = rt->getTime(4);
    v->m_updateTime = rt->getTime(5);
    return v;
}

int ArticleClassRelInfoDao::QueryByArticleId(std::vector<ArticleClassRelInfo::ptr>& results,  const int64_t& article_id, stone::IDB::ptr conn) {
    std::string sql = "select id, article_id, class_id, is_deleted, create_time, update_time from article_class_rel where article_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, article_id);
    auto rt = stmt->query();
    if(!rt) {
        return 0;
    }
    while (rt->next()) {
        ArticleClassRelInfo::ptr v(new ArticleClassRelInfo);
        v->m_id = rt->getInt64(0);
        v->m_articleId = rt->getInt64(1);
        v->m_classId = rt->getInt64(2);
        v->m_isDeleted = rt->getInt32(3);
        v->m_createTime = rt->getTime(4);
        v->m_updateTime = rt->getTime(5);
        results.push_back(v);
    };
    return 0;
}

int ArticleClassRelInfoDao::QueryByClassId(std::vector<ArticleClassRelInfo::ptr>& results,  const int64_t& class_id, stone::IDB::ptr conn) {
    std::string sql = "select id, article_id, class_id, is_deleted, create_time, update_time from article_class_rel where class_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, class_id);
    auto rt = stmt->query();
    if(!rt) {
        return 0;
    }
    while (rt->next()) {
        ArticleClassRelInfo::ptr v(new ArticleClassRelInfo);
        v->m_id = rt->getInt64(0);
        v->m_articleId = rt->getInt64(1);
        v->m_classId = rt->getInt64(2);
        v->m_isDeleted = rt->getInt32(3);
        v->m_createTime = rt->getTime(4);
        v->m_updateTime = rt->getTime(5);
        results.push_back(v);
    };
    return 0;
}

ArticleClassRelInfo::ptr ArticleClassRelInfoDao::QueryByArticleIdClassId( const int64_t& article_id,  const int64_t& class_id, stone::IDB::ptr conn) {
    std::string sql = "select id, article_id, class_id, is_deleted, create_time, update_time from article_class_rel where article_id = ? and class_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindInt64(1, article_id);
    stmt->bindInt64(2, class_id);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    ArticleClassRelInfo::ptr v(new ArticleClassRelInfo);
    v->m_id = rt->getInt64(0);
    v->m_articleId = rt->getInt64(1);
    v->m_classId = rt->getInt64(2);
    v->m_isDeleted = rt->getInt32(3);
    v->m_createTime = rt->getTime(4);
    v->m_updateTime = rt->getTime(5);
    return v;
}

int ArticleClassRelInfoDao::CreateTableSQLite3(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE article_class_rel("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "article_id INTEGER NOT NULL DEFAULT 0,"
            "class_id INTEGER NOT NULL DEFAULT 0,"
            "is_deleted INTEGER NOT NULL DEFAULT 0,"
            "create_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "update_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00');"
            "CREATE INDEX article_class_rel_article_id ON article_class_rel(article_id);"
            "CREATE INDEX article_class_rel_class_id ON article_class_rel(class_id);"
            "CREATE UNIQUE INDEX article_class_rel_article_id_class_id ON article_class_rel(article_id,class_id);"
            );
}

int ArticleClassRelInfoDao::CreateTableMySQL(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE article_class_rel("
            "`id` bigint AUTO_INCREMENT COMMENT '自增长id',"
            "`article_id` bigint NOT NULL DEFAULT 0 COMMENT '文章id',"
            "`class_id` bigint NOT NULL DEFAULT 0 COMMENT '分类id',"
            "`is_deleted` int NOT NULL DEFAULT 0 COMMENT '是否删除',"
            "`create_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '创建时间',"
            "`update_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' ON UPDATE current_timestamp  COMMENT '更新时间',"
            "PRIMARY KEY(`id`),"
            "KEY `article_class_rel_article_id` (`article_id`),"
            "KEY `article_class_rel_class_id` (`class_id`),"
            "UNIQUE KEY `article_class_rel_article_id_class_id` (`article_id`,`class_id`)) COMMENT='文章分类关系表'");
}
} //namespace data
} //namespace blog
