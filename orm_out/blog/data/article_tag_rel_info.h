#ifndef __BLOG_DATAARTICLE_TAG_REL_INFO_H__
#define __BLOG_DATAARTICLE_TAG_REL_INFO_H__

#include <json/json.h>
#include <vector>
#include "src/db/db.hpp"
#include "src/util.hpp"


namespace blog {
namespace data {

class ArticleTagRelInfoDao;
class ArticleTagRelInfo {
friend class ArticleTagRelInfoDao;
public:
    typedef std::shared_ptr<ArticleTagRelInfo> ptr;

    ArticleTagRelInfo();

    const int64_t& getId() { return m_id; }
    void setId(const int64_t& v);

    const int64_t& getArticleId() { return m_articleId; }
    void setArticleId(const int64_t& v);

    const int64_t& getTagId() { return m_tagId; }
    void setTagId(const int64_t& v);

    const int64_t& getCreateTime() { return m_createTime; }
    void setCreateTime(const int64_t& v);

    const int64_t& getUpdateTime() { return m_updateTime; }
    void setUpdateTime(const int64_t& v);

    std::string toJsonString() const;

private:
    int64_t m_id;
    int64_t m_articleId;
    int64_t m_tagId;
    int64_t m_createTime;
    int64_t m_updateTime;
};


class ArticleTagRelInfoDao {
public:
    typedef std::shared_ptr<ArticleTagRelInfoDao> ptr;
    static int Update(ArticleTagRelInfo::ptr info, stone::IDB::ptr conn);
    static int Insert(ArticleTagRelInfo::ptr info, stone::IDB::ptr conn);
    static int InsertOrUpdate(ArticleTagRelInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(ArticleTagRelInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(const int64_t& id, stone::IDB::ptr conn);
    static int DeleteById( const int64_t& id, stone::IDB::ptr conn);
    static int DeleteByArticleId( const int64_t& article_id, stone::IDB::ptr conn);
    static int DeleteByTagId( const int64_t& tag_id, stone::IDB::ptr conn);
    static int DeleteByArticleIdTagId( const int64_t& article_id,  const int64_t& tag_id, stone::IDB::ptr conn);
    static int QueryAll(std::vector<ArticleTagRelInfo::ptr>& results, stone::IDB::ptr conn);
    static ArticleTagRelInfo::ptr Query( const int64_t& id, stone::IDB::ptr conn);
    static int QueryByArticleId(std::vector<ArticleTagRelInfo::ptr>& results,  const int64_t& article_id, stone::IDB::ptr conn);
    static int QueryByTagId(std::vector<ArticleTagRelInfo::ptr>& results,  const int64_t& tag_id, stone::IDB::ptr conn);
    static ArticleTagRelInfo::ptr QueryByArticleIdTagId( const int64_t& article_id,  const int64_t& tag_id, stone::IDB::ptr conn);
    static int CreateTableSQLite3(stone::IDB::ptr info);
    static int CreateTableMySQL(stone::IDB::ptr info);
};

} //namespace data
} //namespace blog
#endif //__BLOG_DATAARTICLE_TAG_REL_INFO_H__
