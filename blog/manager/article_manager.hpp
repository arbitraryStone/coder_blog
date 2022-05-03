#ifndef __BLOG_MANAGER_ARTICLE_MANAGER_HPP__
#define __BLOG_MANAGER_ARTICLE_MANAGER_HPP__

#include "blog/data/article_info.hpp"
#include "src/singleton.hpp"
#include "src/mutex.hpp"
#include "src/iomanager.hpp"
#include <map>
#include <unordered_map>

namespace blog {

class ArticleManager {
public:
    bool loadAll();
    void add(blog::data::ArticleInfo::ptr info);
    blog::data::ArticleInfo::ptr get(int64_t id);
    bool listByUserId(std::vector<data::ArticleInfo::ptr>& infos, int64_t id, bool valid);
    int64_t listByUserIdPages(std::vector<data::ArticleInfo::ptr>& infos, int64_t id
                              ,int32_t offset, int32_t size, bool valid, int state);

    void delVerify(int64_t id);
    void addVerify(data::ArticleInfo::ptr info);

    int64_t listVerifyPages(std::vector<data::ArticleInfo::ptr>& infos
                            ,int32_t offset, int32_t size);

    std::pair<data::ArticleInfo::ptr, data::ArticleInfo::ptr> nearby(int64_t id);

    std::string statusString();
    void start();
    void stop();

    bool incViews(uint64_t id, const std::string& cooke_id, uint64_t user_id);
    bool incPraise(uint64_t id, const std::string& cooke_id, uint64_t user_id);
    bool incFavorites(uint64_t id, const std::string& cooke_id, uint64_t user_id);
    bool decPraise(uint64_t id, const std::string& cooke_id, uint64_t user_id);
    bool decFavorites(uint64_t id, const std::string& cooke_id, uint64_t user_id);

    bool listUserFav(int64_t id, std::map<int64_t, int64_t>& articles);
    bool listUserPra(int64_t id, std::map<int64_t, int64_t>& articles);
    bool listArticleFav(int64_t id, std::map<int64_t, int64_t>& users);
    bool listArticlePra(int64_t id, std::map<int64_t, int64_t>& users);
private:
    void onTimer();
    void onUpdateTimer();
    bool addViews(uint64_t id, const std::string& cooke_id);
    void addUpdate(int64_t id);
private:
    stone::RWMutex m_mutex;
    std::map<int64_t, blog::data::ArticleInfo::ptr> m_datas;//全部数据
    std::unordered_map<int64_t, std::map<int64_t, blog::data::ArticleInfo::ptr> > m_users;//以用户id建立的映射，存储用户的全部文章(第二个键为文章id)
    std::map<int64_t, blog::data::ArticleInfo::ptr> m_verifys;//审核通过的文章，以文章id为键
    stone::RWMutex m_viewsMutex;
    std::map<int64_t, std::map<std::string, int64_t> > m_viewsCache;
    std::set<int64_t> m_updates;
    stone::Timer::ptr m_timer;
    stone::Timer::ptr m_updateTimer;
};

typedef stone::Singleton<ArticleManager> ArticleMgr;

}

#endif
