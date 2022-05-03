#include "blog_module.hpp"
#include "src/log.hpp"
#include "src/config.hpp"
#include "src/db/sqlite3.hpp"
#include "src/stone.hpp"

#include "blog/manager/user_manager.hpp"
#include "blog/manager/article_manager.hpp"
#include "blog/manager/comment_manager.hpp"
#include "blog/manager/label_manager.hpp"
#include "blog/manager/class_manager.hpp"
#include "blog/manager/article_class_rel_manager.hpp"
#include "blog/manager/article_label_rel_manager.hpp"
#include "blog/manager/user_friend_rel_manager.hpp"
namespace blog{

static stone::Logger::ptr g_logger = STONE_LOG_ROOT();
static stone::ConfigVar<std::string>::ptr g_sqlite3_db_name =
    stone::Config::Lookup("sqlite3.db_name",
            std::string("blog.db"), "sqlite3 db file name");

BlogModule::BlogModule()
    :Module("coder_blog","1.1",""){
}

bool BlogModule::onLoad(){
    return true;
}

bool BlogModule::onUnload(){
    return true;
}

bool BlogModule::onServerReady(){
    STONE_LOG_INFO(blog::g_logger) << "on server ready";
    auto work_path = stone::Config::Lookup<std::string>("server.work_path");
    auto db_path = work_path->getValue() + "/" + g_sqlite3_db_name->getValue();

    stone::SQLite3::ptr db;
    db = stone::SQLite3::Create(db_path, stone::SQLite3::READWRITE);

    if(!db) {
        STONE_LOG_INFO(g_logger) << "init database begin";
        db = stone::SQLite3::Create(db_path);
        if(!db) {
            STONE_LOG_ERROR(g_logger) << "open database db=" << db_path
                << " failed";
            return false;
        }
#define XX(clazz, t) \
        if(blog::data::clazz::CreateTableSQLite3(db)) { \
            STONE_LOG_ERROR(g_logger) << "create table " t " failed"; \
            return false; \
        }
        XX(UserInfoDao, "user");
        XX(LabelInfoDao, "label");
        XX(ArticleInfoDao, "article");
        XX(CommentInfoDao, "comment");
        XX(ClassificationInfoDao, "classification");
        XX(ArticleClassRelInfoDao, "article_class_rel");
        XX(ArticleLabelRelInfoDao, "article_label_rel");
        XX(UserFriendRelInfoDao, "user_friend_rel");
#undef XX
        STONE_LOG_INFO(g_logger) << "init database end";
    }
    
    std::vector<stone::TcpServer::ptr> servers;
    if(!stone::Application::GetInstance()->getServer("http", servers)) {
        STONE_LOG_ERROR(g_logger) << "http_server not open";
        return false;
    }

    #define XX(clazz) \
    if(!clazz::GetInstance()->loadAll()) { \
        STONE_LOG_ERROR(g_logger) << #clazz " load all fail"; \
    }
    XX(UserMgr);
    XX(ArticleMgr);
    XX(ClassMgr);
    XX(LabelMgr);
    XX(CommentMgr);
    XX(ArticleClassRelMgr);
    XX(ArticleLabelRelMgr);
    XX(UserFriendRelMgr);
#undef XX

    return true;
}

bool BlogModule::onServerUp(){
    return true;
}

}

extern "C"{

stone::Module* CreateModule(){
    stone::Module* module = new blog::BlogModule;
    STONE_LOG_INFO(blog::g_logger) << "Create Blog Module" <<  module;
    return module; 
}

void DestoryModule(stone::Module* module){
    STONE_LOG_INFO(blog::g_logger) << "Destory Blog Module" << module;
    delete module;
}

}
