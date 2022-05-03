#include "blog_module.hpp"
#include "src/log.hpp"

namespace blog{

static stone::Logger::ptr g_logger = STONE_LOG_ROOT();

BlogModule::BlogModule()
    :Module("blog","1.1",""){
}

bool BlogModule::onLoad(){
    return true;
}

bool BlogModule::onUnload(){
    return true;
}

bool BlogModule::onServerReady(){
    STONE_LOG_INFO(blog::g_logger) << "on server ready";
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
