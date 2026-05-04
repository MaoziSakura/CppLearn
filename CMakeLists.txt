# 1. 最低版本要求 (建议 3.10+，以支持现代特性)
cmake_minimum_required(VERSION 3.10)

# 2. 项目名称、版本及语言
project(run 
        VERSION 1.0 
        LANGUAGES CXX)

# 3. 核心配置：导出编译数据库 (给 clangd/VS Code 使用)
# 这样你就不用在命令行手动输入 -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 4. 指定 C++ 标准 (推荐 17 或以上)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # 关闭编译器私有扩展，保证代码可移植性
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 5. 头文件目录 (将当前目录加入搜索路径)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# 6. 源文件管理
# 方式 A (手动列出，推荐)：更透明，大型项目必选
# set(SOURCES 
#     "src/main.cpp" 
#     # 如果有其他 .cpp 也可以写在这里
# )

# 方式 B (自动扫描)：适合小型练习项目
file(GLOB SOURCES "src/*.cpp" "tests/*.cpp")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
    message(STATUS "Debug mode is ON")
endif()

# 7. 生成可执行程序
add_executable(${PROJECT_NAME} ${SOURCES})

# 8. 编译器选项 (开启全警告模式，这对 C/C++ 学习至关重要)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    # 在 Arch (GCC/Clang) 下开启这些能帮你提前发现内存或逻辑 Bug
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()