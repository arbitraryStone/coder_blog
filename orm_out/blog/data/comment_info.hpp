#ifndef __BLOG_DATACOMMENT_INFO_HPP__
#define __BLOG_DATACOMMENT_INFO_HPP__

#include <json/json.h>
#include <vector>
#include "src/db/db.hpp"
#include "src/util.hpp"


namespace blog {
namespace data {

class CommentInfoDao;
class CommentInfo {
friend class CommentInfoDao;
public:
    typedef std::shared_ptr<CommentInfo> ptr;

    CommentInfo();

    const int64_t& getCId() { return m_cId; }
    void setCId(const int64_t& v);

    const int64_t& getUserId() { return m_userId; }
    void setUserId(const int64_t& v);

    const int64_t& getArticleId() { return m_articleId; }
    void setArticleId(const int64_t& v);

    const std::string& getContent() { return m_content; }
    void setContent(const std::string& v);

    const int64_t& getParentId() { return m_parentId; }
    void setParentId(const int64_t& v);

    const int32_t& getState() { return m_state; }
    void setState(const int32_t& v);

    const int32_t& getIsDeleted() { return m_isDeleted; }
    void setIsDeleted(const int32_t& v);

    const int64_t& getPraise() { return m_praise; }
    void setPraise(const int64_t& v);

    const int64_t& getCreateTime() { return m_createTime; }
    void setCreateTime(const int64_t& v);

    std::string toJsonString() const;

private:
    int32_t m_state;
    int32_t m_isDeleted;
    int64_t m_cId;
    int64_t m_userId;
    int64_t m_articleId;
    int64_t m_parentId;
    int64_t m_praise;
    std::string m_content;
    int64_t m_createTime;
};


class CommentInfoDao {
public:
    typedef std::shared_ptr<CommentInfoDao> ptr;
    static int Update(CommentInfo::ptr info, stone::IDB::ptr conn);
    static int Insert(CommentInfo::ptr info, stone::IDB::ptr conn);
    static int InsertOrUpdate(CommentInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(CommentInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(const int64_t& c_id, stone::IDB::ptr conn);
    static int DeleteByCId( const int64_t& c_id, stone::IDB::ptr conn);
    static int DeleteByUserId( const int64_t& user_id, stone::IDB::ptr conn);
    static int DeleteByArticleId( const int64_t& article_id, stone::IDB::ptr conn);
    static int QueryAll(std::vector<CommentInfo::ptr>& results, stone::IDB::ptr conn);
    static CommentInfo::ptr Query( const int64_t& c_id, stone::IDB::ptr conn);
    static int QueryByUserId(std::vector<CommentInfo::ptr>& results,  const int64_t& user_id, stone::IDB::ptr conn);
    static int QueryByArticleId(std::vector<CommentInfo::ptr>& results,  const int64_t& article_id, stone::IDB::ptr conn);
    static int CreateTableSQLite3(stone::IDB::ptr info);
    static int CreateTableMySQL(stone::IDB::ptr info);
};

} //namespace data
} //namespace blog
#endif //__BLOG_DATACOMMENT_INFO_HPP__
