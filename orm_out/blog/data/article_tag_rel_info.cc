#include "article_tag_rel_info.h"
#include "src/log.hpp"

namespace blog {
namespace data {

static stone::Logger::ptr g_logger = STONE_LOG_NAME("orm");

ArticleTagRelInfo::ArticleTagRelInfo()
    :m_id()
    ,m_articleId()
    ,m_tagId()
    ,m_createTime()
    ,m_updateTime() {
}

std::string ArticleTagRelInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["id"] = std::to_string(m_id);
    jvalue["article_id"] = std::to_string(m_articleId);
    jvalue["tag_id"] = std::to_string(m_tagId);
    jvalue["create_time"] = stone::Time2Str(m_createTime);
    jvalue["update_time"] = stone::Time2Str(m_updateTime);
    return stone::JsonUtil::ToString(jvalue);
}

void ArticleTagRelInfo::setId(const int64_t& v) {
    m_id = v;
}

void ArticleTagRelInfo::setArticleId(const int64_t& v) {
    m_articleId = v;
}

void ArticleTagRelInfo::setTagId(const int64_t& v) {
    m_tagId = v;
}

void ArticleTagRelInfo::setCreateTime(const int64_t& v) {
    m_createTime = v;
}

void ArticleTagRelInfo::setUpdateTime(const int64_t& v) {
    m_updateTime = v;
}


int ArticleTagRelInfoDao::Update(ArticleTagRelInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "update article_tag_rel set article_id = ?, tag_id = ?, create_time = ?, update_time = ? where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_articleId);
    stmt->bindInt64(2, info->m_tagId);
    stmt->bindTime(3, info->m_createTime);
    stmt->bindTime(4, info->m_updateTime);
    stmt->bindInt64(5, info->m_id);
    return stmt->execute();
}

int ArticleTagRelInfoDao::Insert(ArticleTagRelInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "insert into article_tag_rel (article_id, tag_id, create_time, update_time) values (?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_articleId);
    stmt->bindInt64(2, info->m_tagId);
    stmt->bindTime(3, info->m_createTime);
    stmt->bindTime(4, info->m_updateTime);
    int rt = stmt->execute();
    if(rt == 0) {
        info->m_id = conn->getLastInsertId();
    }
    return rt;
}

int ArticleTagRelInfoDao::InsertOrUpdate(ArticleTagRelInfo::ptr info, stone::IDB::ptr conn) {
    if(info->m_id == 0) {
        return Insert(info, conn);
    }
    std::string sql = "replace into article_tag_rel (id, article_id, tag_id, create_time, update_time) values (?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    stmt->bindInt64(2, info->m_articleId);
    stmt->bindInt64(3, info->m_tagId);
    stmt->bindTime(4, info->m_createTime);
    stmt->bindTime(5, info->m_updateTime);
    return stmt->execute();
}

int ArticleTagRelInfoDao::Delete(ArticleTagRelInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "delete from article_tag_rel where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    return stmt->execute();
}

int ArticleTagRelInfoDao::DeleteById( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "delete from article_tag_rel where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, id);
    return stmt->execute();
}

int ArticleTagRelInfoDao::DeleteByArticleId( const int64_t& article_id, stone::IDB::ptr conn) {
    std::string sql = "delete from article_tag_rel where article_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, article_id);
    return stmt->execute();
}

int ArticleTagRelInfoDao::DeleteByTagId( const int64_t& tag_id, stone::IDB::ptr conn) {
    std::string sql = "delete from article_tag_rel where tag_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, tag_id);
    return stmt->execute();
}

int ArticleTagRelInfoDao::DeleteByArticleIdTagId( const int64_t& article_id,  const int64_t& tag_id, stone::IDB::ptr conn) {
    std::string sql = "delete from article_tag_rel where article_id = ? and tag_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, article_id);
    stmt->bindInt64(1, tag_id);
    return stmt->execute();
}

int ArticleTagRelInfoDao::QueryAll(std::vector<ArticleTagRelInfo::ptr>& results, stone::IDB::ptr conn) {
    std::string sql = "select id, article_id, tag_id, create_time, update_time from article_tag_rel";
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
        ArticleTagRelInfo::ptr v(new ArticleTagRelInfo);
        v->m_id = rt->getInt64(0);
        v->m_articleId = rt->getInt64(1);
        v->m_tagId = rt->getInt64(2);
        v->m_createTime = rt->getTime(3);
        v->m_updateTime = rt->getTime(4);
        results.push_back(v);
    }
    return 0;
}

ArticleTagRelInfo::ptr ArticleTagRelInfoDao::Query( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "select id, article_id, tag_id, create_time, update_time from article_tag_rel where id = ?";
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
    ArticleTagRelInfo::ptr v(new ArticleTagRelInfo);
    v->m_id = rt->getInt64(0);
    v->m_articleId = rt->getInt64(1);
    v->m_tagId = rt->getInt64(2);
    v->m_createTime = rt->getTime(3);
    v->m_updateTime = rt->getTime(4);
    return v;
}

int ArticleTagRelInfoDao::QueryByArticleId(std::vector<ArticleTagRelInfo::ptr>& results,  const int64_t& article_id, stone::IDB::ptr conn) {
    std::string sql = "select id, article_id, tag_id, create_time, update_time from article_tag_rel where article_id = ?";
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
        ArticleTagRelInfo::ptr v(new ArticleTagRelInfo);
        v->m_id = rt->getInt64(0);
        v->m_articleId = rt->getInt64(1);
        v->m_tagId = rt->getInt64(2);
        v->m_createTime = rt->getTime(3);
        v->m_updateTime = rt->getTime(4);
        results.push_back(v);
    };
    return 0;
}

int ArticleTagRelInfoDao::QueryByTagId(std::vector<ArticleTagRelInfo::ptr>& results,  const int64_t& tag_id, stone::IDB::ptr conn) {
    std::string sql = "select id, article_id, tag_id, create_time, update_time from article_tag_rel where tag_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, tag_id);
    auto rt = stmt->query();
    if(!rt) {
        return 0;
    }
    while (rt->next()) {
        ArticleTagRelInfo::ptr v(new ArticleTagRelInfo);
        v->m_id = rt->getInt64(0);
        v->m_articleId = rt->getInt64(1);
        v->m_tagId = rt->getInt64(2);
        v->m_createTime = rt->getTime(3);
        v->m_updateTime = rt->getTime(4);
        results.push_back(v);
    };
    return 0;
}

ArticleTagRelInfo::ptr ArticleTagRelInfoDao::QueryByArticleIdTagId( const int64_t& article_id,  const int64_t& tag_id, stone::IDB::ptr conn) {
    std::string sql = "select id, article_id, tag_id, create_time, update_time from article_tag_rel where article_id = ? and tag_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindInt64(1, article_id);
    stmt->bindInt64(2, tag_id);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    ArticleTagRelInfo::ptr v(new ArticleTagRelInfo);
    v->m_id = rt->getInt64(0);
    v->m_articleId = rt->getInt64(1);
    v->m_tagId = rt->getInt64(2);
    v->m_createTime = rt->getTime(3);
    v->m_updateTime = rt->getTime(4);
    return v;
}

int ArticleTagRelInfoDao::CreateTableSQLite3(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE article_tag_rel("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "article_id INTEGER NOT NULL DEFAULT 0,"
            "tag_id INTEGER NOT NULL DEFAULT 0,"
            "create_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "update_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00');"
            "CREATE INDEX article_tag_rel_article_id ON article_tag_rel(article_id);"
            "CREATE INDEX article_tag_rel_tag_id ON article_tag_rel(tag_id);"
            "CREATE UNIQUE INDEX article_tag_rel_article_id_tag_id ON article_tag_rel(article_id,tag_id);"
            );
}

int ArticleTagRelInfoDao::CreateTableMySQL(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE article_tag_rel("
            "`id` bigint AUTO_INCREMENT COMMENT '自增长id',"
            "`article_id` bigint NOT NULL DEFAULT 0 COMMENT '文章id',"
            "`tag_id` bigint NOT NULL DEFAULT 0 COMMENT '标签id',"
            "`create_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '创建时间',"
            "`update_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' ON UPDATE current_timestamp  COMMENT '更新时间',"
            "PRIMARY KEY(`id`),"
            "KEY `article_tag_rel_article_id` (`article_id`),"
            "KEY `article_tag_rel_tag_id` (`tag_id`),"
            "UNIQUE KEY `article_tag_rel_article_id_tag_id` (`article_id`,`tag_id`)) COMMENT='文章标签关系表'");
}
} //namespace data
} //namespace blog
