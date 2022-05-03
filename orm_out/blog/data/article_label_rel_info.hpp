#ifndef __BLOG_DATAARTICLE_LABEL_REL_INFO_HPP__
#define __BLOG_DATAARTICLE_LABEL_REL_INFO_HPP__

#include <json/json.h>
#include <vector>
#include "src/db/db.hpp"
#include "src/util.hpp"


namespace blog {
namespace data {

class ArticleLabelRelInfoDao;
class ArticleLabelRelInfo {
friend class ArticleLabelRelInfoDao;
public:
    typedef std::shared_ptr<ArticleLabelRelInfo> ptr;

    ArticleLabelRelInfo();

    const int64_t& getId() { return m_id; }
    void setId(const int64_t& v);

    const int64_t& getArticleId() { return m_articleId; }
    void setArticleId(const int64_t& v);

    const int64_t& getLabelId() { return m_labelId; }
    void setLabelId(const int64_t& v);

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
    int64_t m_labelId;
    int64_t m_createTime;
    int64_t m_updateTime;
};


class ArticleLabelRelInfoDao {
public:
    typedef std::shared_ptr<ArticleLabelRelInfoDao> ptr;
    static int Update(ArticleLabelRelInfo::ptr info, stone::IDB::ptr conn);
    static int Insert(ArticleLabelRelInfo::ptr info, stone::IDB::ptr conn);
    static int InsertOrUpdate(ArticleLabelRelInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(ArticleLabelRelInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(const int64_t& id, stone::IDB::ptr conn);
    static int DeleteById( const int64_t& id, stone::IDB::ptr conn);
    static int DeleteByArticleId( const int64_t& article_id, stone::IDB::ptr conn);
    static int DeleteByLabelId( const int64_t& label_id, stone::IDB::ptr conn);
    static int DeleteByArticleIdLabelId( const int64_t& article_id,  const int64_t& label_id, stone::IDB::ptr conn);
    static int QueryAll(std::vector<ArticleLabelRelInfo::ptr>& results, stone::IDB::ptr conn);
    static ArticleLabelRelInfo::ptr Query( const int64_t& id, stone::IDB::ptr conn);
    static int QueryByArticleId(std::vector<ArticleLabelRelInfo::ptr>& results,  const int64_t& article_id, stone::IDB::ptr conn);
    static int QueryByLabelId(std::vector<ArticleLabelRelInfo::ptr>& results,  const int64_t& label_id, stone::IDB::ptr conn);
    static ArticleLabelRelInfo::ptr QueryByArticleIdLabelId( const int64_t& article_id,  const int64_t& label_id, stone::IDB::ptr conn);
    static int CreateTableSQLite3(stone::IDB::ptr info);
    static int CreateTableMySQL(stone::IDB::ptr info);
};

} //namespace data
} //namespace blog
#endif //__BLOG_DATAARTICLE_LABEL_REL_INFO_HPP__
