cmake_minimum_required(VERSION 3.0)
project(orm_data)

set(LIB_SRC
    blog/data/article_info.cpp
    blog/data/article_class_rel_info.cpp
    blog/data/article_label_rel_info.cpp
    blog/data/classification_info.cpp
    blog/data/comment_info.cpp
    blog/data/label_info.cpp
    blog/data/user_info.cpp
    blog/data/user_friend_rel_info.cpp
)
add_library(orm_data ${LIB_SRC})
force_redefine_file_macro_for_sources(orm_data)
