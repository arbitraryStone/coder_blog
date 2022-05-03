#ifndef __BLOG_DATATAG_INFO_H__
#define __BLOG_DATATAG_INFO_H__

#include <json/json.h>
#include <vector>
#include "src/db/db.hpp"
#include "src/util.hpp"


namespace blog {
namespace data {

class TagInfoDao;
class TagInfo {
friend class TagInfoDao;
public:
    typedef std::shared_ptr<TagInfo> ptr;

    TagInfo();

    const int64_t& getId() { return m_id; }
    void setId(const int64_t& v);

    const std::string& getTagName() { return m_tagName; }
    void setTagName(const std::string& v);

    const int64_t& getCreateTime() { return m_createTime; }
    void setCreateTime(const int64_t& v);

    const int64_t& getUpdateTime() { return m_updateTime; }
    void setUpdateTime(const int64_t& v);

    std::string toJsonString() const;

private:
    int64_t m_id;
    std::string m_tagName;
    int64_t m_createTime;
    int64_t m_updateTime;
};


class TagInfoDao {
public:
    typedef std::shared_ptr<TagInfoDao> ptr;
    static int Update(TagInfo::ptr info, stone::IDB::ptr conn);
    static int Insert(TagInfo::ptr info, stone::IDB::ptr conn);
    static int InsertOrUpdate(TagInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(TagInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(const int64_t& id, stone::IDB::ptr conn);
    static int DeleteById( const int64_t& id, stone::IDB::ptr conn);
    static int DeleteByTagName( const std::string& tag_name, stone::IDB::ptr conn);
    static int QueryAll(std::vector<TagInfo::ptr>& results, stone::IDB::ptr conn);
    static TagInfo::ptr Query( const int64_t& id, stone::IDB::ptr conn);
    static TagInfo::ptr QueryByTagName( const std::string& tag_name, stone::IDB::ptr conn);
    static int CreateTableSQLite3(stone::IDB::ptr info);
    static int CreateTableMySQL(stone::IDB::ptr info);
};

} //namespace data
} //namespace blog
#endif //__BLOG_DATATAG_INFO_H__
