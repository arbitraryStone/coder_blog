#ifndef __BLOG_DATATYPE_INFO_H__
#define __BLOG_DATATYPE_INFO_H__

#include <json/json.h>
#include <vector>
#include "src/db/db.hpp"
#include "src/util.hpp"


namespace blog {
namespace data {

class TypeInfoDao;
class TypeInfo {
friend class TypeInfoDao;
public:
    typedef std::shared_ptr<TypeInfo> ptr;

    TypeInfo();

    const int64_t& getId() { return m_id; }
    void setId(const int64_t& v);

    const std::string& getTypeName() { return m_typeName; }
    void setTypeName(const std::string& v);

    const int64_t& getCreateTime() { return m_createTime; }
    void setCreateTime(const int64_t& v);

    const int64_t& getUpdateTime() { return m_updateTime; }
    void setUpdateTime(const int64_t& v);

    std::string toJsonString() const;

private:
    int64_t m_id;
    std::string m_typeName;
    int64_t m_createTime;
    int64_t m_updateTime;
};


class TypeInfoDao {
public:
    typedef std::shared_ptr<TypeInfoDao> ptr;
    static int Update(TypeInfo::ptr info, stone::IDB::ptr conn);
    static int Insert(TypeInfo::ptr info, stone::IDB::ptr conn);
    static int InsertOrUpdate(TypeInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(TypeInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(const int64_t& id, stone::IDB::ptr conn);
    static int DeleteById( const int64_t& id, stone::IDB::ptr conn);
    static int DeleteByTypeName( const std::string& type_name, stone::IDB::ptr conn);
    static int QueryAll(std::vector<TypeInfo::ptr>& results, stone::IDB::ptr conn);
    static TypeInfo::ptr Query( const int64_t& id, stone::IDB::ptr conn);
    static TypeInfo::ptr QueryByTypeName( const std::string& type_name, stone::IDB::ptr conn);
    static int CreateTableSQLite3(stone::IDB::ptr info);
    static int CreateTableMySQL(stone::IDB::ptr info);
};

} //namespace data
} //namespace blog
#endif //__BLOG_DATATYPE_INFO_H__
