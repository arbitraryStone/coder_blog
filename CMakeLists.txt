##设置cmake所需最低版本号
cmake_minimum_required(VERSION 2.8)

##设置系统名称
set(CMAKE_SYSTEM_NAME Linux)

##设置编译器
set(CMAKE_C_COMPILER /apps/stone/bin/gcc)
set(CMAKE_CXX_COMPILER /apps/stone/bin/g++)

##设置项目名
project(blog)

##添加子文件夹
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/stone)

##显示详细的原始编译信息
set(CMAKE_VERBOSE_MAKEFILE ON)

##设置编译选项
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -fPIC")

##设置包含目录
include_directories(.)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/stone)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/orm_out)

##添加子文件夹
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/orm_out)
set(LIB_SRC 
        blog/blog_module.cpp
        blog/util.cpp
        blog/struct.cpp
        blog/manager/user_manager.cpp
        blog/manager/article_manager.cpp
        blog/manager/comment_manager.cpp
        blog/manager/class_manager.cpp
        blog/manager/label_manager.cpp
        blog/manager/article_class_rel_manager.cpp
        blog/manager/article_label_rel_manager.cpp
        blog/manager/user_friend_rel_manager.cpp

   )

##添加blog库
add_library(blog SHARED ${LIB_SRC})

add_dependencies(blog orm_data)
target_link_libraries(blog orm_data)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
