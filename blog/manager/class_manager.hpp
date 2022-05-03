#ifndef __BLOG_MANAGER_CATEGORY_MANAGER_HPP__
#define __BLOG_MANAGER_CATEGORY_MANAGER_HPP__

#include "blog/data/classification_info.hpp"
#include "src/singleton.hpp"
#include "src/mutex.hpp"
#include <map>
#include <unordered_map>

namespace blog {

class ClassManager {
public:
    bool loadAll();
    void add(blog::data::ClassificationInfo::ptr info);
    blog::data::ClassificationInfo::ptr get(int64_t id);
    bool exists(int64_t id, const std::string& name);

    std::string statusString();
private:
    stone::RWMutex m_mutex;
    std::unordered_map<int64_t, blog::data::ClassificationInfo::ptr> m_datas;
};

typedef stone::Singleton<ClassManager> ClassMgr;

}

#endif
