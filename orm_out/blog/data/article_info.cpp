#include "article_info.hpp"
#include "src/log.hpp"

namespace blog {
namespace data {

static stone::Logger::ptr g_logger = STONE_LOG_NAME("orm");

ArticleInfo::ArticleInfo()
    :m_type()
    ,m_state()
    ,m_isDeleted()
    ,m_aId()
    ,m_userId()
    ,m_views()
    ,m_praise()
    ,m_title()
    ,m_content()
    ,m_publishTime()
    ,m_createTime()
    ,m_updateTime() {
}

std::string ArticleInfo::toJsonString() const {
    Json::Value jvalue;
    jvalue["a_id"] = std::to_string(m_aId);
    jvalue["user_id"] = std::to_string(m_userId);
    jvalue["title"] = m_title;
    jvalue["content"] = m_content;
    jvalue["type"] = m_type;
    jvalue["state"] = m_state;
    jvalue["is_deleted"] = m_isDeleted;
    jvalue["publish_time"] = stone::Time2Str(m_publishTime);
    jvalue["views"] = std::to_string(m_views);
    jvalue["praise"] = std::to_string(m_praise);
    jvalue["create_time"] = stone::Time2Str(m_createTime);
    jvalue["update_time"] = stone::Time2Str(m_updateTime);
    return stone::JsonUtil::ToString(jvalue);
}

void ArticleInfo::setAId(const int64_t& v) {
    m_aId = v;
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

void ArticleInfo::setType(const int32_t& v) {
    m_type = v;
}

void ArticleInfo::setState(const int32_t& v) {
    m_state = v;
}

void ArticleInfo::setIsDeleted(const int32_t& v) {
    m_isDeleted = v;
}

void ArticleInfo::setPublishTime(const int64_t& v) {
    m_publishTime = v;
}

void ArticleInfo::setViews(const int64_t& v) {
    m_views = v;
}

void ArticleInfo::setPraise(const int64_t& v) {
    m_praise = v;
}

void ArticleInfo::setCreateTime(const int64_t& v) {
    m_createTime = v;
}

void ArticleInfo::setUpdateTime(const int64_t& v) {
    m_updateTime = v;
}


int ArticleInfoDao::Update(ArticleInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "update article set user_id = ?, title = ?, content = ?, type = ?, state = ?, is_deleted = ?, publish_time = ?, views = ?, praise = ?, create_time = ?, update_time = ? where a_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_userId);
    stmt->bindString(2, info->m_title);
    stmt->bindString(3, info->m_content);
    stmt->bindInt32(4, info->m_type);
    stmt->bindInt32(5, info->m_state);
    stmt->bindInt32(6, info->m_isDeleted);
    stmt->bindTime(7, info->m_publishTime);
    stmt->bindInt64(8, info->m_views);
    stmt->bindInt64(9, info->m_praise);
    stmt->bindTime(10, info->m_createTime);
    stmt->bindTime(11, info->m_updateTime);
    stmt->bindInt64(12, info->m_aId);
    return stmt->execute();
}

int ArticleInfoDao::Insert(ArticleInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "insert into article (user_id, title, content, type, state, is_deleted, publish_time, views, praise, create_time, update_time) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_userId);
    stmt->bindString(2, info->m_title);
    stmt->bindString(3, info->m_content);
    stmt->bindInt32(4, info->m_type);
    stmt->bindInt32(5, info->m_state);
    stmt->bindInt32(6, info->m_isDeleted);
    stmt->bindTime(7, info->m_publishTime);
    stmt->bindInt64(8, info->m_views);
    stmt->bindInt64(9, info->m_praise);
    stmt->bindTime(10, info->m_createTime);
    stmt->bindTime(11, info->m_updateTime);
    int rt = stmt->execute();
    if(rt == 0) {
        info->m_aId = conn->getLastInsertId();
    }
    return rt;
}

int ArticleInfoDao::InsertOrUpdate(ArticleInfo::ptr info, stone::IDB::ptr conn) {
    if(info->m_aId == 0) {
        return Insert(info, conn);
    }
    std::string sql = "replace into article (a_id, user_id, title, content, type, state, is_deleted, publish_time, views, praise, create_time, update_time) values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_aId);
    stmt->bindInt64(2, info->m_userId);
    stmt->bindString(3, info->m_title);
    stmt->bindString(4, info->m_content);
    stmt->bindInt32(5, info->m_type);
    stmt->bindInt32(6, info->m_state);
    stmt->bindInt32(7, info->m_isDeleted);
    stmt->bindTime(8, info->m_publishTime);
    stmt->bindInt64(9, info->m_views);
    stmt->bindInt64(10, info->m_praise);
    stmt->bindTime(11, info->m_createTime);
    stmt->bindTime(12, info->m_updateTime);
    return stmt->execute();
}

int ArticleInfoDao::Delete(ArticleInfo::ptr info, stone::IDB::ptr conn) {
    std::string sql = "delete from article where a_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, info->m_aId);
    return stmt->execute();
}

int ArticleInfoDao::DeleteByAId( const int64_t& a_id, stone::IDB::ptr conn) {
    std::string sql = "delete from article where a_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return conn->getErrno();
    }
    stmt->bindInt64(1, a_id);
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
    std::string sql = "select a_id, user_id, title, content, type, state, is_deleted, publish_time, views, praise, create_time, update_time from article";
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
        v->m_aId = rt->getInt64(0);
        v->m_userId = rt->getInt64(1);
        v->m_title = rt->getString(2);
        v->m_content = rt->getString(3);
        v->m_type = rt->getInt32(4);
        v->m_state = rt->getInt32(5);
        v->m_isDeleted = rt->getInt32(6);
        v->m_publishTime = rt->getTime(7);
        v->m_views = rt->getInt64(8);
        v->m_praise = rt->getInt64(9);
        v->m_createTime = rt->getTime(10);
        v->m_updateTime = rt->getTime(11);
        results.push_back(v);
    }
    return 0;
}

ArticleInfo::ptr ArticleInfoDao::Query( const int64_t& a_id, stone::IDB::ptr conn) {
    std::string sql = "select a_id, user_id, title, content, type, state, is_deleted, publish_time, views, praise, create_time, update_time from article where a_id = ?";
    auto stmt = conn->prepare(sql);
    if(!stmt) {
        STONE_LOG_ERROR(g_logger) << "stmt=" << sql
                 << " errno=" << conn->getErrno() << " errstr=" << conn->getErrStr();
        return nullptr;
    }
    stmt->bindInt64(1, a_id);
    auto rt = stmt->query();
    if(!rt) {
        return nullptr;
    }
    if(!rt->next()) {
        return nullptr;
    }
    ArticleInfo::ptr v(new ArticleInfo);
    v->m_aId = rt->getInt64(0);
    v->m_userId = rt->getInt64(1);
    v->m_title = rt->getString(2);
    v->m_content = rt->getString(3);
    v->m_type = rt->getInt32(4);
    v->m_state = rt->getInt32(5);
    v->m_isDeleted = rt->getInt32(6);
    v->m_publishTime = rt->getTime(7);
    v->m_views = rt->getInt64(8);
    v->m_praise = rt->getInt64(9);
    v->m_createTime = rt->getTime(10);
    v->m_updateTime = rt->getTime(11);
    return v;
}

int ArticleInfoDao::QueryByUserId(std::vector<ArticleInfo::ptr>& results,  const int64_t& user_id, stone::IDB::ptr conn) {
    std::string sql = "select a_id, user_id, title, content, type, state, is_deleted, publish_time, views, praise, create_time, update_time from article where user_id = ?";
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
        v->m_aId = rt->getInt64(0);
        v->m_userId = rt->getInt64(1);
        v->m_title = rt->getString(2);
        v->m_content = rt->getString(3);
        v->m_type = rt->getInt32(4);
        v->m_state = rt->getInt32(5);
        v->m_isDeleted = rt->getInt32(6);
        v->m_publishTime = rt->getTime(7);
        v->m_views = rt->getInt64(8);
        v->m_praise = rt->getInt64(9);
        v->m_createTime = rt->getTime(10);
        v->m_updateTime = rt->getTime(11);
        results.push_back(v);
    };
    return 0;
}

int ArticleInfoDao::CreateTableSQLite3(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE article("
            "a_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "user_id INTEGER NOT NULL DEFAULT 0,"
            "title TEXT NOT NULL DEFAULT '',"
            "content TEXT NOT NULL DEFAULT '',"
            "type INTEGER NOT NULL DEFAULT 0,"
            "state INTEGER NOT NULL DEFAULT 0,"
            "is_deleted INTEGER NOT NULL DEFAULT 0,"
            "publish_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "views INTEGER NOT NULL DEFAULT 0,"
            "praise INTEGER NOT NULL DEFAULT 0,"
            "create_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00',"
            "update_time TIMESTAMP NOT NULL DEFAULT '1980-01-01 00:00:00');"
            "CREATE INDEX article_user_id ON article(user_id);"
            );
}

int ArticleInfoDao::CreateTableMySQL(stone::IDB::ptr conn) {
    return conn->execute("CREATE TABLE article("
            "`a_id` bigint AUTO_INCREMENT COMMENT '文章id',"
            "`user_id` bigint NOT NULL DEFAULT 0 COMMENT '用户id',"
            "`title` varchar(256) NOT NULL DEFAULT '' COMMENT '文章标题',"
            "`content` text NOT NULL DEFAULT '' COMMENT '文章内容',"
            "`type` int NOT NULL DEFAULT 0 COMMENT '类型 1:原创,2:转发',"
            "`state` int NOT NULL DEFAULT 0 COMMENT '状态1审核中2已发布3未通过4待发布',"
            "`is_deleted` int NOT NULL DEFAULT 0 COMMENT '是否删除',"
            "`publish_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '发布时间',"
            "`views` bigint NOT NULL DEFAULT 0 COMMENT '流量数',"
            "`praise` bigint NOT NULL DEFAULT 0 COMMENT '点赞数',"
            "`create_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' COMMENT '创建时间',"
            "`update_time` timestamp NOT NULL DEFAULT '1980-01-01 00:00:00' ON UPDATE current_timestamp  COMMENT '更新时间',"
            "PRIMARY KEY(`a_id`),"
            "KEY `article_user_id` (`user_id`)) COMMENT='博客文章'");
}
} //namespace data
} //namespace blog
