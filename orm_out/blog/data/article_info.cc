#include "article_info.h"
#include "src/log.hpp"

namespace blog {
namespace data {

static stone::Logger::ptr g_logger = STONE_LOG_NAME("orm");

ArticleInfo::ArticleInfo()
    :m_id()
    ,m_userId()
    ,m_views()
    ,m_state()
    ,m_appreciate()
    ,m_comment()
    ,m_recommend()
    ,m_statement()
    ,m_title()
    ,m_type()
    ,m_content()
    ,m_descContent()
    ,m_firstPicture()
    ,m_publishTime()
    ,m_createTime()
    ,m_updateTime() {
}

std::string ArticleInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["id"] = std::to_string(m_id);
    jvalue["user_id"] = std::to_string(m_userId);
    jvalue["title"] = m_title;
    jvalue["content"] = m_content;
    jvalue["desc_content"] = m_descContent;
    jvalue["first_picture"] = m_firstPicture;
    jvalue["type"] = m_type;
    jvalue["views"] = std::to_string(m_views);
    jvalue["state"] = std::to_string(m_state);
    jvalue["appreciate"] = std::to_string(m_appreciate);
    jvalue["comment"] = std::to_string(m_comment);
    jvalue["recommend"] = std::to_string(m_recommend);
    jvalue["statement"] = std::to_string(m_statement);
    jvalue["publish_time"] = stone::Time2Str(m_publishTime);
    jvalue["create_time"] = stone::Time2Str(m_createTime);
    jvalue["update_time"] = stone::Time2Str(m_updateTime);
    return stone::JsonUtil::ToString(jvalue);
}

void ArticleInfo::setId(const int64_t& v) {
    m_id = v;
}

void ArticleInfo::setUserId(const int64_t& v) {
    m_userId = v;
}

void ArticleInfo::setTitle(const std::string& v) {
    m_title = v;
}

void ArticleInfo::setContent(const std::string& v) {
    m_content = v;
}

void ArticleInfo::setDescContent(const std::string& v) {
    m_descContent = v;
}

void ArticleInfo::setFirstPicture(const std::string& v) {
    m_firstPicture = v;
}

void ArticleInfo::setType(const std::string& v) {
    m_type = v;
}

void ArticleInfo::setViews(const int64_t& v) {
    m_views = v;
}

void ArticleInfo::setState(const int64_t& v) {
    m_state = v;
}

void ArticleInfo::setAppreciate(const int64_t& v) {
    m_appreciate = v;
}

void ArticleInfo::setComment(const int64_t& v) {
    m_comment = v;
}

void ArticleInfo::setRecommend(const int64_t& v) {
    m_recommend = v;
}

void ArticleInfo::setStatement(const int64_t& v) {
    m_statement = v;
}

void ArticleInfo::setPublishTime(const int64_t& v) {
    m_publishTime = v;
}

void ArticleInfo::setCreateTime(const int64_t& v) {
    m_createTime = v;
}

void ArticleInfo::setUpdateTime(const int64_t& v) {
    m_updateTime = v;
}


int ArticleInfoDao::Update(ArticleInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "update article set user_id = ?, title = ?, content = ?, desc_content = ?, first_picture = ?, type = ?, views = ?, state = ?, appreciate = ?, comment = ?, recommend = ?, statement = ?, publish_time = ?, create_time = ?, update_time = ? where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_userId);
    stmt->bindString(2, info->m_title);
    stmt->bindString(3, info->m_content);
    stmt->bindString(4, info->m_descContent);
    stmt->bindString(5, info->m_firstPicture);
    stmt->bindString(6, info->m_type);
    stmt->bindInt64(7, info->m_views);
    stmt->bindInt64(8, info->m_state);
    stmt->bindInt64(9, info->m_appreciate);
    stmt->bindInt64(10, info->m_comment);
    stmt->bindInt64(11, info->m_recommend);
    stmt->bindInt64(12, info->m_statement);
    stmt->bindTime(13, info->m_publishTime);
    stmt->bindTime(14, info->m_createTime);
    stmt->bindTime(15, info->m_updateTime);
    stmt->bindInt64(16, info->m_id);
    return stmt->execute();
}

int ArticleInfoDao::Insert(ArticleInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "insert into article (user_id, title, content, desc_content, first_picture, type, views, state, appreciate, comment, recommend, statement, publish_time, create_time, update_time) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_userId);
    stmt->bindString(2, info->m_title);
    stmt->bindString(3, info->m_content);
    stmt->bindString(4, info->m_descContent);
    stmt->bindString(5, info->m_firstPicture);
    stmt->bindString(6, info->m_type);
    stmt->bindInt64(7, info->m_views);
    stmt->bindInt64(8, info->m_state);
    stmt->bindInt64(9, info->m_appreciate);
    stmt->bindInt64(10, info->m_comment);
    stmt->bindInt64(11, info->m_recommend);
    stmt->bindInt64(12, info->m_statement);
    stmt->bindTime(13, info->m_publishTime);
    stmt->bindTime(14, info->m_createTime);
    stmt->bindTime(15, info->m_updateTime);
    int rt = stmt->execute();
    if(rt == 0) {
        info->m_id = conn->getLastInsertId();
    }
    return rt;
}

int ArticleInfoDao::InsertOrUpdate(ArticleInfo::ptr info, stone::IDB::ptr conn) {
    if(info->m_id == 0) {
        return Insert(info, conn);
    }
    std::string sql = "replace into article (id, user_id, title, content, desc_content, first_picture, type, views, state, appreciate, comment, recommend, statement, publish_time, create_time, update_time) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    stmt->bindInt64(2, info->m_userId);
    stmt->bindString(3, info->m_title);
    stmt->bindString(4, info->m_content);
    stmt->bindString(5, info->m_descContent);
    stmt->bindString(6, info->m_firstPicture);
    stmt->bindString(7, info->m_type);
    stmt->bindInt64(8, info->m_views);
    stmt->bindInt64(9, info->m_state);
    stmt->bindInt64(10, info->m_appreciate);
    stmt->bindInt64(11, info->m_comment);
    stmt->bindInt64(12, info->m_recommend);
    stmt->bindInt64(13, info->m_statement);
    stmt->bindTime(14, info->m_publishTime);
    stmt->bindTime(15, info->m_createTime);
    stmt->bindTime(16, info->m_updateTime);
    return stmt->execute();
}

int ArticleInfoDao::Delete(ArticleInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "delete from article where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_id);
    return stmt->execute();
}

int ArticleInfoDao::DeleteById( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "delete from article where id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, id);
    return stmt->execute();
}

int ArticleInfoDao::DeleteByUserId( const int64_t& user_id, stone::IDB::ptr conn) {
    std::string sql = "delete from article where user_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, user_id);
    return stmt->execute();
}

int ArticleInfoDao::QueryAll(std::vector<ArticleInfo::ptr>& results, stone::IDB::ptr conn) {
    std::string sql = "select id, user_id, title, content, desc_content, first_picture, type, views, state, appreciate, comment, recommend, statement, publish_time, create_time, update_time from article";
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
        ArticleInfo::ptr v(new ArticleInfo);
        v->m_id = rt->getInt64(0);
        v->m_userId = rt->getInt64(1);
        v->m_title = rt->getString(2);
        v->m_content = rt->getString(3);
        v->m_descContent = rt->getString(4);
        v->m_firstPicture = rt->getString(5);
        v->m_type = rt->getString(6);
        v->m_views = rt->getInt64(7);
        v->m_state = rt->getInt64(8);
        v->m_appreciate = rt->getInt64(9);
        v->m_comment = rt->getInt64(10);
        v->m_recommend = rt->getInt64(11);
        v->m_statement = rt->getInt64(12);
        v->m_publishTime = rt->getTime(13);
        v->m_createTime = rt->getTime(14);
        v->m_updateTime = rt->getTime(15);
        results.push_back(v);
    }
    return 0;
}

ArticleInfo::ptr ArticleInfoDao::Query( const int64_t& id, stone::IDB::ptr conn) {
    std::string sql = "select id, user_id, title, content, desc_content, first_picture, type, views, state, appreciate, comment, recommend, statement, publish_time, create_time, update_time from article where id = ?";
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
    ArticleInfo::ptr v(new ArticleInfo);
    v->m_id = rt->getInt64(0);
    v->m_userId = rt->getInt64(1);
    v->m_title = rt->getString(2);
    v->m_content = rt->getString(3);
    v->m_descContent = rt->getString(4);
    v->m_firstPicture = rt->getString(5);
    v->m_type = rt->getString(6);
    v->m_views = rt->getInt64(7);
    v->m_state = rt->getInt64(8);
    v->m_appreciate = rt->getInt64(9);
    v->m_comment = rt->getInt64(10);
    v->m_recommend = rt->getInt64(11);
    v->m_statement = rt->getInt64(12);
    v->m_publishTime = rt->getTime(13);
    v->m_createTime = rt->getTime(14);
    v->m_updateTime = rt->getTime(15);
    return v;
}

int ArticleInfoDao::QueryByUserId(std::vector<ArticleInfo::ptr>& results,  const int64_t& user_id, stone::IDB::ptr conn) {
    std::string sql = "select id, user_id, title, content, desc_content, first_picture, type, views, state, appreciate, comment, recommend, statement, publish_time, create_time, update_time from article where user_id = ?";
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
        ArticleInfo::ptr v(new ArticleInfo);
        v->m_id = rt->getInt64(0);
        v->m_userId = rt->getInt64(1);
        v->m_title = rt->getString(2);
        v->m_content = rt->getString(3);
        v->m_descContent = rt->getString(4);
        v->m_firstPicture = rt->getString(5);
        v->m_type = rt->getString(6);
        v->m_views = rt->getInt64(7);
        v->m_state = rt->getInt64(8);
        v->m_appreciate = rt->getInt64(9);
        v->m_comment = rt->getInt64(10);
        v->m_recommend = rt->getInt64(11);
        v->m_statement = rt->getInt64(12);
        v->m_publishTime = rt->getTime(13);
        v->m_createTime = rt->getTime(14);
        v->m_updateTime = rt->getTime(15);
        results.push_back(v);
    };
    return 0;
}

int ArticleInfoDao::CreateTableSQLite3(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE article("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "user_id INTEGER NOT NULL DEFAULT 0,"
            "title TEXT NOT NULL DEFAULT '',"
            "content TEXT NOT NULL DEFAULT '',"
            "desc_content TEXT NOT NULL DEFAULT '',"
            "first_picture TEXT NOT NULL DEFAULT '',"
            "type TEXT NOT NULL DEFAULT '',"
            "views INTEGER NOT NULL DEFAULT 0,"
            "state INTEGER NOT NULL DEFAULT 0,"
            "appreciate INTEGER NOT NULL DEFAULT 0,"
            "comment INTEGER NOT NULL DEFAULT 0,"
            "recommend INTEGER NOT NULL DEFAULT 0,"
            "statement INTEGER NOT NULL DEFAULT 0,"
            "publish_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "create_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "update_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00');"
            "CREATE INDEX article_user_id ON article(user_id);"
            );
}

int ArticleInfoDao::CreateTableMySQL(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE article("
            "`id` bigint AUTO_INCREMENT COMMENT '文章id',"
            "`user_id` bigint NOT NULL DEFAULT 0 COMMENT '用户id',"
            "`title` varchar(256) NOT NULL DEFAULT '' COMMENT '文章标题',"
            "`content` text NOT NULL DEFAULT '' COMMENT '文章内容',"
            "`desc_content` text NOT NULL DEFAULT '' COMMENT '文章描述',"
            "`first_picture` text NOT NULL DEFAULT '' COMMENT '首图引用地址',"
            "`type` varchar(30) NOT NULL DEFAULT '' COMMENT '分类',"
            "`views` bigint NOT NULL DEFAULT 0 COMMENT '流量数',"
            "`state` bigint NOT NULL DEFAULT 0 COMMENT '文章发表状态',"
            "`appreciate` bigint NOT NULL DEFAULT 0 COMMENT '赞赏是否开启',"
            "`comment` bigint NOT NULL DEFAULT 0 COMMENT '评论是否开启',"
            "`recommend` bigint NOT NULL DEFAULT 0 COMMENT '是否推荐',"
            "`statement` bigint NOT NULL DEFAULT 0 COMMENT '版权说明是否开启',"
            "`publish_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '发布时间',"
            "`create_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '创建时间',"
            "`update_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' ON UPDATE current_timestamp  COMMENT '更新时间',"
            "PRIMARY KEY(`id`),"
            "KEY `article_user_id` (`user_id`)) COMMENT='博客文章'");
}
} //namespace data
} //namespace blog
