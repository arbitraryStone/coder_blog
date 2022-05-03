#ifndef __BLOG_DATALABEL_INFO_HPP__
#define __BLOG_DATALABEL_INFO_HPP__

#include <json/json.h>
#include <vector>
#include "src/db/db.hpp"
#include "src/util.hpp"


namespace blog {
namespace data {

class LabelInfoDao;
class LabelInfo {
friend class LabelInfoDao;
public:
    typedef std::shared_ptr<LabelInfo> ptr;

    LabelInfo();

    const int64_t& getLId() { return m_lId; }
    void setLId(const int64_t& v);

    const std::string& getName() { return m_name; }
    void setName(const std::string& v);

    const int32_t& getIsDeleted() { return m_isDeleted; }
    void setIsDeleted(const int32_t& v);

    const int64_t& getCreateTime() { return m_createTime; }
    void setCreateTime(const int64_t& v);

    std::string toJsonString() const;

private:
    int32_t m_isDeleted;
    int64_t m_lId;
    std::string m_name;
    int64_t m_createTime;
};


class LabelInfoDao {
public:
    typedef std::shared_ptr<LabelInfoDao> ptr;
    static int Update(LabelInfo::ptr info, stone::IDB::ptr conn);
    static int Insert(LabelInfo::ptr info, stone::IDB::ptr conn);
    static int InsertOrUpdate(LabelInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(LabelInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(const int64_t& l_id, stone::IDB::ptr conn);
    static int DeleteByLId( const int64_t& l_id, stone::IDB::ptr conn);
    static int DeleteByName( const std::string& name, stone::IDB::ptr conn);
    static int QueryAll(std::vector<LabelInfo::ptr>& results, stone::IDB::ptr conn);
    static LabelInfo::ptr Query( const int64_t& l_id, stone::IDB::ptr conn);
    static LabelInfo::ptr QueryByName( const std::string& name, stone::IDB::ptr conn);
    static int CreateTableSQLite3(stone::IDB::ptr info);
    static int CreateTableMySQL(stone::IDB::ptr info);
};

} //namespace data
} //namespace blog
#endif //__BLOG_DATALABEL_INFO_HPP__
