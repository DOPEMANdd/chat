cmake_minimum_required(VERSION 3.0) #设置最低cmake版本
project(main)   #项目名称

#配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)  #-g 调试

#配置头文件搜索路径
#include_directories()
#配置库文件搜索路径
#link_directories()

#设置需要编译的源文件列表
set(SRC_LIST muduo_server.cpp)

#把.指定路径下的所有源文件名字放入变量名SRC_LIST里面
#aux_source_directory(. SRC_LIST)

#设置可执行文件存储的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#生成可执行文件server，由SRC_LIST变量所定义的源文件编译而来
add_executable(server ${SRC_LIST})
#表示server这个目标程序，需要链接muduo_net muduo_base pthread这三个库文件
target_link_libraries(server muduo_net muduo_base pthread)


#先cmake .(.为CMakeLists所在目录) 生成makefile以及各种中间文件，然后make（make会自动找makefile）生成可执行文件


