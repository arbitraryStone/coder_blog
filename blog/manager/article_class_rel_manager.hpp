#ifndef __BLOG_MANAGER_ARTICLE_CLASS_REL_MANAGER_HPP__
#define __BLOG_MANAGER_ARTICLE_CLASS_REL_MANAGER_HPP__

#include "blog/data/article_class_rel_info.hpp"
#include "src/singleton.hpp"
#include "src/mutex.hpp"
#include <map>
#include <unordered_map>

namespace blog {

class ArticleClassRelManager {
public:
    bool loadAll();
    void add(blog::data::ArticleClassRelInfo::ptr info);
    blog::data::ArticleClassRelInfo::ptr get(int64_t id);
    bool listByArticleId(std::vector<data::ArticleClassRelInfo::ptr>& infos, int64_t id, bool valid);
    bool listByClassId(std::vector<data::ArticleClassRelInfo::ptr>& infos, int64_t id, bool valid);
    blog::data::ArticleClassRelInfo::ptr getByArticleIdClassId(int64_t article_id, int64_t class_id);

    std::string statusString();
private:
    stone::RWMutex m_mutex;
    std::unordered_map<int64_t, blog::data::ArticleClassRelInfo::ptr> m_datas;
    std::unordered_map<int64_t, std::map<int64_t, blog::data::ArticleClassRelInfo::ptr> > m_articles;
    std::unordered_map<int64_t, std::map<int64_t, blog::data::ArticleClassRelInfo::ptr> > m_classes;
};

typedef stone::Singleton<ArticleClassRelManager> ArticleClassRelMgr;

}

#endif
