#include "article_type_rel_info.h"
#include "src/log.hpp"

namespace blog {
namespace data {

static stone::Logger::ptr g_logger = STONE_LOG_NAME("orm");

ArticleTypeRelInfo::ArticleTypeRelInfo()
    :m_id()
    ,m_articleId()
    ,m_typeId()
    ,m_createTime()
    ,m_updateTime() {
}

std::string ArticleTypeRelInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["id"] = std::to_string(m_id);
    jvalue["article_id"] = std::to_string(m_articleId);
    jvalue["type_id"] = std::to_string(m_typeId);
    jvalue["create_time"] = stone::Time2Str(m_createTime);
    jvalue["update_time"] = stone::Time2Str(m_updateTime);
    return stone::JsonUtil::ToString(jvalue);
}

void ArticleTypeRelInfo::setId(const int64_t& v) {
    m_id = v;
}

void ArticleTypeRelInfo::setArticleId(const int64_t& v) {
    m_articleId = v;
}

void ArticleTypeRelInfo::setTypeId(const int64_t& v) {
    m_typeId = v;
}

void ArticleTypeRelInfo::setCreateTime(const int64_t& v) {
    m_createTime = v;
}

void ArticleTypeRelInfo::setUpdateTime(const int64_t& v) {
    m_updateTime = v;
}


int ArticleTypeRelInfoDao::Update(ArticleTypeRelInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "update article_type_rel set article_id = ?, type_id = ?, create_time = ?, update_time = ? where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_articleId);
    stmt->bindInt64(2, info->m_typeId);
    stmt->bindTime(3, info->m_createTime);
    stmt->bindTime(4, info->m_updateTime);
    stmt->bindInt64(5, info->m_id);
    return stmt->execute();
}

int ArticleTypeRelInfoDao::Insert(ArticleTypeRelInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "insert into article_type_rel (article_id, type_id, create_time, update_time) values (?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_articleId);
    stmt->bindInt64(2, info->m_typeId);
    stmt->bindTime(3, info->m_createTime);
    stmt->bindTime(4, info->m_updateTime);
    int rt = stmt->execute();
    if(rt == 0) {
        info->m_id = conn->getLastInsertId();
    }
    return rt;
}

int ArticleTypeRelInfoDao::InsertOrUpdate(ArticleTypeRelInfo::ptr info, stone::IDB::ptr conn) {
    if(info->m_id == 0) {
        return Insert(info, conn);
    }
    std::string sql = "replace into article_type_rel (id, article_id, type_id, create_time, update_time) values (?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    stmt->bindInt64(2, info->m_articleId);
    stmt->bindInt64(3, info->m_typeId);
    stmt->bindTime(4, info->m_createTime);
    stmt->bindTime(5, info->m_updateTime);
    return stmt->execute();
}

int ArticleTypeRelInfoDao::Delete(ArticleTypeRelInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "delete from article_type_rel where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    return stmt->execute();
}

int ArticleTypeRelInfoDao::DeleteById( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "delete from article_type_rel where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, id);
    return stmt->execute();
}

int ArticleTypeRelInfoDao::DeleteByArticleId( const int64_t& article_id, stone::IDB::ptr conn) {
    std::string sql = "delete from article_type_rel where article_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, article_id);
    return stmt->execute();
}

int ArticleTypeRelInfoDao::DeleteByTypeId( const int64_t& type_id, stone::IDB::ptr conn) {
    std::string sql = "delete from article_type_rel where type_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, type_id);
    return stmt->execute();
}

int ArticleTypeRelInfoDao::DeleteByArticleIdTypeId( const int64_t& article_id,  const int64_t& type_id, stone::IDB::ptr conn) {
    std::string sql = "delete from article_type_rel where article_id = ? and type_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, article_id);
    stmt->bindInt64(1, type_id);
    return stmt->execute();
}

int ArticleTypeRelInfoDao::QueryAll(std::vector<ArticleTypeRelInfo::ptr>& results, stone::IDB::ptr conn) {
    std::string sql = "select id, article_id, type_id, create_time, update_time from article_type_rel";
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
        ArticleTypeRelInfo::ptr v(new ArticleTypeRelInfo);
        v->m_id = rt->getInt64(0);
        v->m_articleId = rt->getInt64(1);
        v->m_typeId = rt->getInt64(2);
        v->m_createTime = rt->getTime(3);
        v->m_updateTime = rt->getTime(4);
        results.push_back(v);
    }
    return 0;
}

ArticleTypeRelInfo::ptr ArticleTypeRelInfoDao::Query( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "select id, article_id, type_id, create_time, update_time from article_type_rel where id = ?";
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
    ArticleTypeRelInfo::ptr v(new ArticleTypeRelInfo);
    v->m_id = rt->getInt64(0);
    v->m_articleId = rt->getInt64(1);
    v->m_typeId = rt->getInt64(2);
    v->m_createTime = rt->getTime(3);
    v->m_updateTime = rt->getTime(4);
    return v;
}

int ArticleTypeRelInfoDao::QueryByArticleId(std::vector<ArticleTypeRelInfo::ptr>& results,  const int64_t& article_id, stone::IDB::ptr conn) {
    std::string sql = "select id, article_id, type_id, create_time, update_time from article_type_rel where article_id = ?";
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
        ArticleTypeRelInfo::ptr v(new ArticleTypeRelInfo);
        v->m_id = rt->getInt64(0);
        v->m_articleId = rt->getInt64(1);
        v->m_typeId = rt->getInt64(2);
        v->m_createTime = rt->getTime(3);
        v->m_updateTime = rt->getTime(4);
        results.push_back(v);
    };
    return 0;
}

int ArticleTypeRelInfoDao::QueryByTypeId(std::vector<ArticleTypeRelInfo::ptr>& results,  const int64_t& type_id, stone::IDB::ptr conn) {
    std::string sql = "select id, article_id, type_id, create_time, update_time from article_type_rel where type_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, type_id);
    auto rt = stmt->query();
    if(!rt) {
        return 0;
    }
    while (rt->next()) {
        ArticleTypeRelInfo::ptr v(new ArticleTypeRelInfo);
        v->m_id = rt->getInt64(0);
        v->m_articleId = rt->getInt64(1);
        v->m_typeId = rt->getInt64(2);
        v->m_createTime = rt->getTime(3);
        v->m_updateTime = rt->getTime(4);
        results.push_back(v);
    };
    return 0;
}

ArticleTypeRelInfo::ptr ArticleTypeRelInfoDao::QueryByArticleIdTypeId( const int64_t& article_id,  const int64_t& type_id, stone::IDB::ptr conn) {
    std::string sql = "select id, article_id, type_id, create_time, update_time from article_type_rel where article_id = ? and type_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindInt64(1, article_id);
    stmt->bindInt64(2, type_id);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    ArticleTypeRelInfo::ptr v(new ArticleTypeRelInfo);
    v->m_id = rt->getInt64(0);
    v->m_articleId = rt->getInt64(1);
    v->m_typeId = rt->getInt64(2);
    v->m_createTime = rt->getTime(3);
    v->m_updateTime = rt->getTime(4);
    return v;
}

int ArticleTypeRelInfoDao::CreateTableSQLite3(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE article_type_rel("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "article_id INTEGER NOT NULL DEFAULT 0,"
            "type_id INTEGER NOT NULL DEFAULT 0,"
            "create_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "update_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00');"
            "CREATE INDEX article_type_rel_article_id ON article_type_rel(article_id);"
            "CREATE INDEX article_type_rel_type_id ON article_type_rel(type_id);"
            "CREATE UNIQUE INDEX article_type_rel_article_id_type_id ON article_type_rel(article_id,type_id);"
            );
}

int ArticleTypeRelInfoDao::CreateTableMySQL(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE article_type_rel("
            "`id` bigint AUTO_INCREMENT COMMENT '自增id',"
            "`article_id` bigint NOT NULL DEFAULT 0 COMMENT '文章id',"
            "`type_id` bigint NOT NULL DEFAULT 0 COMMENT '分类id',"
            "`create_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '创建时间',"
            "`update_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '更新时间',"
            "PRIMARY KEY(`id`),"
            "KEY `article_type_rel_article_id` (`article_id`),"
            "KEY `article_type_rel_type_id` (`type_id`),"
            "UNIQUE KEY `article_type_rel_article_id_type_id` (`article_id`,`type_id`)) COMMENT='文章分类关系表'");
}
} //namespace data
} //namespace blog
