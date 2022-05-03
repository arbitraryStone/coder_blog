#ifndef __BLOG_DATAARTICLE_INFO_H__
#define __BLOG_DATAARTICLE_INFO_H__

#include <json/json.h>
#include <vector>
#include "src/db/db.hpp"
#include "src/util.hpp"


namespace blog {
namespace data {

class ArticleInfoDao;
class ArticleInfo {
friend class ArticleInfoDao;
public:
    typedef std::shared_ptr<ArticleInfo> ptr;

    ArticleInfo();

    const int64_t& getId() { return m_id; }
    void setId(const int64_t& v);

    const int64_t& getUserId() { return m_userId; }
    void setUserId(const int64_t& v);

    const std::string& getTitle() { return m_title; }
    void setTitle(const std::string& v);

    const std::string& getContent() { return m_content; }
    void setContent(const std::string& v);

    const std::string& getDescContent() { return m_descContent; }
    void setDescContent(const std::string& v);

    const std::string& getFirstPicture() { return m_firstPicture; }
    void setFirstPicture(const std::string& v);

    const std::string& getType() { return m_type; }
    void setType(const std::string& v);

    const int64_t& getViews() { return m_views; }
    void setViews(const int64_t& v);

    const int64_t& getState() { return m_state; }
    void setState(const int64_t& v);

    const int64_t& getAppreciate() { return m_appreciate; }
    void setAppreciate(const int64_t& v);

    const int64_t& getComment() { return m_comment; }
    void setComment(const int64_t& v);

    const int64_t& getRecommend() { return m_recommend; }
    void setRecommend(const int64_t& v);

    const int64_t& getStatement() { return m_statement; }
    void setStatement(const int64_t& v);

    const int64_t& getPublishTime() { return m_publishTime; }
    void setPublishTime(const int64_t& v);

    const int64_t& getCreateTime() { return m_createTime; }
    void setCreateTime(const int64_t& v);

    const int64_t& getUpdateTime() { return m_updateTime; }
    void setUpdateTime(const int64_t& v);

    std::string toJsonString() const;

private:
    int64_t m_id;
    int64_t m_userId;
    int64_t m_views;
    int64_t m_state;
    int64_t m_appreciate;
    int64_t m_comment;
    int64_t m_recommend;
    int64_t m_statement;
    std::string m_title;
    std::string m_type;
    std::string m_content;
    std::string m_descContent;
    std::string m_firstPicture;
    int64_t m_publishTime;
    int64_t m_createTime;
    int64_t m_updateTime;
};


class ArticleInfoDao {
public:
    typedef std::shared_ptr<ArticleInfoDao> ptr;
    static int Update(ArticleInfo::ptr info, stone::IDB::ptr conn);
    static int Insert(ArticleInfo::ptr info, stone::IDB::ptr conn);
    static int InsertOrUpdate(ArticleInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(ArticleInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(const int64_t& id, stone::IDB::ptr conn);
    static int DeleteById( const int64_t& id, stone::IDB::ptr conn);
    static int DeleteByUserId( const int64_t& user_id, stone::IDB::ptr conn);
    static int QueryAll(std::vector<ArticleInfo::ptr>& results, stone::IDB::ptr conn);
    static ArticleInfo::ptr Query( const int64_t& id, stone::IDB::ptr conn);
    static int QueryByUserId(std::vector<ArticleInfo::ptr>& results,  const int64_t& user_id, stone::IDB::ptr conn);
    static int CreateTableSQLite3(stone::IDB::ptr info);
    static int CreateTableMySQL(stone::IDB::ptr info);
};

} //namespace data
} //namespace blog
#endif //__BLOG_DATAARTICLE_INFO_H__
