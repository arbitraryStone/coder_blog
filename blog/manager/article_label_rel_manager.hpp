#ifndef __BLOG_MANAGER_ARTICLE_LABEL_REL_MANAGER_HPP__
#define __BLOG_MANAGER_ARTICLE_LABEL_REL_MANAGER_HPP__

#include "blog/data/article_label_rel_info.hpp"
#include "src/singleton.hpp"
#include "src/mutex.hpp"
#include <map>
#include <unordered_map>

namespace blog {

class ArticleLabelRelManager {
public:
    bool loadAll();
    void add(blog::data::ArticleLabelRelInfo::ptr info);
    blog::data::ArticleLabelRelInfo::ptr get(int64_t id);
    blog::data::ArticleLabelRelInfo::ptr getByArticleIdLabelId(int64_t article_id, int64_t label_id);
    bool listByArticleId(std::vector<data::ArticleLabelRelInfo::ptr>& infos, int64_t article_id, bool valid);
    bool listByLabelId(std::vector<data::ArticleLabelRelInfo::ptr>& infos, int64_t label_id, bool valid);

    std::string statusString();
private:
    stone::RWMutex m_mutex;
    std::unordered_map<int64_t, blog::data::ArticleLabelRelInfo::ptr> m_datas;
    std::unordered_map<int64_t, std::map<int64_t, blog::data::ArticleLabelRelInfo::ptr> > m_articles;
    std::unordered_map<int64_t, std::map<int64_t, blog::data::ArticleLabelRelInfo::ptr> > m_labels;
};

typedef stone::Singleton<ArticleLabelRelManager> ArticleLabelRelMgr;

}

#endif
