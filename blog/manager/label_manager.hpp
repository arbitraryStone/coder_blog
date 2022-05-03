#ifndef __BLOG_MANAGER_LABEL_MANAGER_HPP__
#define __BLOG_MANAGER_LABEL_MANAGER_HPP__

#include "blog/data/label_info.hpp"
#include "src/singleton.hpp"
#include "src/mutex.hpp"
#include <map>
#include <unordered_map>

namespace blog {

class LabelManager {
public:
    bool loadAll();
    void add(blog::data::LabelInfo::ptr info);
    blog::data::LabelInfo::ptr get(int64_t id);

    std::string statusString();
private:
    stone::RWMutex m_mutex;
    std::unordered_map<int64_t, blog::data::LabelInfo::ptr> m_datas;
};

typedef stone::Singleton<LabelManager> LabelMgr;

}

#endif
