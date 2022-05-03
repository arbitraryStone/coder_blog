#include "util.hpp"
#include <regex>
#include "src/stone.hpp"
#include "src/db/mysql.h"
#include "src/config.hpp"

namespace blog {

static stone::ConfigVar<int32_t>::ptr g_db_type =
    stone::Config::Lookup("db.type", (int32_t)1, "db type 1:sqlite3, 2:mysql");

bool is_email(const std::string& str) {
    static const std::regex s_email_regex("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,8}(\\.[a-z]{2,8})?)");
    return std::regex_match(str, s_email_regex);
}

stone::IDB::ptr GetDB() {
    if(g_db_type->getValue() == 2) {
        return stone::MySQLMgr::GetInstance()->get("blog");
    } else {
        return stone::SQLite3Mgr::GetInstance()->get("blog");
    }
}

//std::string get_max_length_string(const std::string& str, size_t len) {
//    auto wstr = stone::StringUtil::StringToWString(str);
//    wstr.resize(len);
//    return stone::StringUtil::WStringToString(wstr);
//}
//
//void SendWX(const std::string& group, const std::string& msg) {
//    stone::IOManager::GetThis()->schedule([group, msg](){
//        std::string url = "http://127.0.0.1:8072/send_wx?group=" + group
//            + "&msg=" + stone::StringUtil::UrlEncode(msg);
//        stone::http::HttpConnection::DoGet(url, 5000);
//    });
//}
//
}
