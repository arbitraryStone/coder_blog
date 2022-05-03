#ifndef __BLOG_MODULE_HPP__
#define __BLOG_MODULE_HPP__
#include "src/module.hpp"
#include <memory>
namespace blog{

class BlogModule:public stone::Module{

public:
    typedef std::shared_ptr<BlogModule> ptr;
    BlogModule();
    bool onLoad() override;
    bool onUnload() override;
    bool onServerReady() override;
    bool onServerUp() override;
};
};
#endif
