#ifndef __BLOG_DATAARTICLE_CLASS_REL_INFO_HPP__
#define __BLOG_DATAARTICLE_CLASS_REL_INFO_HPP__

#include <json/json.h>
#include <vector>
#include "src/db/db.hpp"
#include "src/util.hpp"


namespace blog {
namespace data {

class ArticleClassRelInfoDao;
class ArticleClassRelInfo {
friend class ArticleClassRelInfoDao;
public:
    typedef std::shared_ptr<ArticleClassRelInfo> ptr;

    ArticleClassRelInfo();

    const int64_t& getId() { return m_id; }
    void setId(const int64_t& v);

    const int64_t& getArticleId() { return m_articleId; }
    void setArticleId(const int64_t& v);

    const int64_t& getClassId() { return m_classId; }
    void setClassId(const int64_t& v);

    const int32_t& getIsDeleted() { return m_isDeleted; }
    void setIsDeleted(const int32_t& v);

    const int64_t& getCreateTime() { return m_createTime; }
    void setCreateTime(const int64_t& v);

    const int64_t& getUpdateTime() { return m_updateTime; }
    void setUpdateTime(const int64_t& v);

    std::string toJsonString() const;

private:
    int32_t m_isDeleted;
    int64_t m_id;
    int64_t m_articleId;
    int64_t m_classId;
    int64_t m_createTime;
    int64_t m_updateTime;
};


class ArticleClassRelInfoDao {
public:
    typedef std::shared_ptr<ArticleClassRelInfoDao> ptr;
    static int Update(ArticleClassRelInfo::ptr info, stone::IDB::ptr conn);
    static int Insert(ArticleClassRelInfo::ptr info, stone::IDB::ptr conn);
    static int InsertOrUpdate(ArticleClassRelInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(ArticleClassRelInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(const int64_t& id, stone::IDB::ptr conn);
    static int DeleteById( const int64_t& id, stone::IDB::ptr conn);
    static int DeleteByArticleId( const int64_t& article_id, stone::IDB::ptr conn);
    static int DeleteByClassId( const int64_t& class_id, stone::IDB::ptr conn);
    static int DeleteByArticleIdClassId( const int64_t& article_id,  const int64_t& class_id, stone::IDB::ptr conn);
    static int QueryAll(std::vector<ArticleClassRelInfo::ptr>& results, stone::IDB::ptr conn);
    static ArticleClassRelInfo::ptr Query( const int64_t& id, stone::IDB::ptr conn);
    static int QueryByArticleId(std::vector<ArticleClassRelInfo::ptr>& results,  const int64_t& article_id, stone::IDB::ptr conn);
    static int QueryByClassId(std::vector<ArticleClassRelInfo::ptr>& results,  const int64_t& class_id, stone::IDB::ptr conn);
    static ArticleClassRelInfo::ptr QueryByArticleIdClassId( const int64_t& article_id,  const int64_t& class_id, stone::IDB::ptr conn);
    static int CreateTableSQLite3(stone::IDB::ptr info);
    static int CreateTableMySQL(stone::IDB::ptr info);
};

} //namespace data
} //namespace blog
#endif //__BLOG_DATAARTICLE_CLASS_REL_INFO_HPP__
