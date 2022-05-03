#ifndef __BLOG_DATACLASSIFICATION_INFO_HPP__
#define __BLOG_DATACLASSIFICATION_INFO_HPP__

#include <json/json.h>
#include <vector>
#include "src/db/db.hpp"
#include "src/util.hpp"


namespace blog {
namespace data {

class ClassificationInfoDao;
class ClassificationInfo {
friend class ClassificationInfoDao;
public:
    typedef std::shared_ptr<ClassificationInfo> ptr;

    ClassificationInfo();

    const int64_t& getClassId() { return m_classId; }
    void setClassId(const int64_t& v);

    const std::string& getName() { return m_name; }
    void setName(const std::string& v);

    const int32_t& getIsDeleted() { return m_isDeleted; }
    void setIsDeleted(const int32_t& v);

    const int64_t& getCreateTime() { return m_createTime; }
    void setCreateTime(const int64_t& v);

    std::string toJsonString() const;

private:
    int32_t m_isDeleted;
    int64_t m_classId;
    std::string m_name;
    int64_t m_createTime;
};


class ClassificationInfoDao {
public:
    typedef std::shared_ptr<ClassificationInfoDao> ptr;
    static int Update(ClassificationInfo::ptr info, stone::IDB::ptr conn);
    static int Insert(ClassificationInfo::ptr info, stone::IDB::ptr conn);
    static int InsertOrUpdate(ClassificationInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(ClassificationInfo::ptr info, stone::IDB::ptr conn);
    static int Delete(const int64_t& class_id, stone::IDB::ptr conn);
    static int DeleteByClassId( const int64_t& class_id, stone::IDB::ptr conn);
    static int DeleteByName( const std::string& name, stone::IDB::ptr conn);
    static int QueryAll(std::vector<ClassificationInfo::ptr>& results, stone::IDB::ptr conn);
    static ClassificationInfo::ptr Query( const int64_t& class_id, stone::IDB::ptr conn);
    static ClassificationInfo::ptr QueryByName( const std::string& name, stone::IDB::ptr conn);
    static int CreateTableSQLite3(stone::IDB::ptr info);
    static int CreateTableMySQL(stone::IDB::ptr info);
};

} //namespace data
} //namespace blog
#endif //__BLOG_DATACLASSIFICATION_INFO_HPP__
