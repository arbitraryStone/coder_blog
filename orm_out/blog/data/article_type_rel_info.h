#ifndef __BLOG_DATAARTICLE_TYPE_REL_INFO_H__
#define __BLOG_DATAARTICLE_TYPE_REL_INFO_H__

#include <json/json.h>
#include <vector>
#include "src/db/db.hpp"
#include "src/util.hpp"


namespace blog {
namespace data {

class ArticleTypeRelInfoDao;
class ArticleTypeRelInfo {
friend class ArticleTypeRelInfoDao;
public:
    typedef std::shared_ptr<ArticleTypeRelInfo> ptr;

    ArticleTypeRelInfo();

    const int64_t& getId() { return m_id; }
    void setId(const int64_t& v);

    const int64_t& getArticleId() { return m_articleId; }
    void setArticleId(const int64_t& v);

    const int64_t& getTypeId() { return m_typeId; }
    void setTypeId(const int64_t& v);

    const int64_t& getCreateTime() { return m_createTime; }
    void setCreateTime(const int64_t& v);

    const int64_t& getUpdateTime() { return m_updateTime; }
    void setUpdateTime(const int64_t& v);

    std::string toJsonString() const;

private:
    int64_t m_id;
    int64_t m_articleId;
    int64_t m_typeId;
    int64_t m_createTime;
    int64_t m_updateTime;
};


class ArticleTypeRelInfoDao {
public:
    typedef std::shared_ptr<ArticleTypeRelInfoDao> ptr;
    static int Update(ArticleTypeRelInfo::ptr info, stone::IDB::ptr conn);
    static int Insert(ArticleTypeRelInfo::ptr info, stone::IDB::ptr conn);
    static int InsertOrUpdate(ArticleTypeRelInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(ArticleTypeRelInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(const int64_t& id, stone::IDB::ptr conn);
    static int DeleteById( const int64_t& id, stone::IDB::ptr conn);
    static int DeleteByArticleId( const int64_t& article_id, stone::IDB::ptr conn);
    static int DeleteByTypeId( const int64_t& type_id, stone::IDB::ptr conn);
    static int DeleteByArticleIdTypeId( const int64_t& article_id,  const int64_t& type_id, stone::IDB::ptr conn);
    static int QueryAll(std::vector<ArticleTypeRelInfo::ptr>& results, stone::IDB::ptr conn);
    static ArticleTypeRelInfo::ptr Query( const int64_t& id, stone::IDB::ptr conn);
    static int QueryByArticleId(std::vector<ArticleTypeRelInfo::ptr>& results,  const int64_t& article_id, stone::IDB::ptr conn);
    static int QueryByTypeId(std::vector<ArticleTypeRelInfo::ptr>& results,  const int64_t& type_id, stone::IDB::ptr conn);
    static ArticleTypeRelInfo::ptr QueryByArticleIdTypeId( const int64_t& article_id,  const int64_t& type_id, stone::IDB::ptr conn);
    static int CreateTableSQLite3(stone::IDB::ptr info);
    static int CreateTableMySQL(stone::IDB::ptr info);
};

} //namespace data
} //namespace blog
#endif //__BLOG_DATAARTICLE_TYPE_REL_INFO_H__
