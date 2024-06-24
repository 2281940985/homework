# 学习心得  
## C++基础知识  
*  vscode基础设置  
    **task.json文件配置：**  
    ```cpp
    {
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "g++",
            "args": [
                "-g",
                "${workspaceFolder}/*.cpp",//待编译的cpp文件
                "-o",
                "${workspaceFolder}/main"//编译完成后的输出的二进制文件
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": ["$gcc"],
            "detail": "Generated task by Debugger."
        }
    ]
    }
    ```   
    以上`${workspaceFolder}`代表当前的工作目录，即vscode的打开目录,可以不用更改，主要更改的是后面的文件待执行的cpp文件  
    **launch.json文件配置**
    ```cpp
    {
    "version": "0.2.0",
    "configurations": [
        {
            "name": "GDB Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/main", // 可执行文件路径
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "/usr/bin/gdb",//ubuntu默认路径
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "build",
            "logging": {
                "trace": true,
                "traceResponse": true,
                "engineLogging": true,
                "programOutput": true,
                "exceptions": true
            }
        }
    ]
    }
    ```  
    按照以上配置就行，注意**可执行文件路径**要与task.json文件保持一致。
* CMake语法    
    
    * camke命令是执行的CMakeLists.txt文件，会生成几个相关文件，因此一般单独再build文件夹下执行cmake命令  
    * 执行make命令需要Makefile文件，执行后才会生成可以运行的二进制文件   
    * 命令行一切皆字符串形式，数字要做转换。  
    * 执行cmake命令时，当前目录不能存在上一次运行过cmake的输出文件，否则不会覆盖。  
    * cmake中用`${变量}`来取变量的值
    * `cmake_minimum_required(VERSION 3.15)`指定cmake的版本  
    * `project(test)`创建项目名称，可随意更改  
    * `set(CMAKW_CXX_STANDARD 11)`指定c++的标准
    * `file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)`可以递归搜索。  
    `aux_source_directory($ {PROJECT_SOURCE_DIR} SRC )`搜索指定文件夹下所有文件放在变量SRC中  
    * `set(SRC add.cpp mulit.cpp main.cpp)`
将cpp文件编译后结果放进变量SRC  
    * `set(EXECUTABLE_OUTPUT_PATH /home/zty/cmake_study/demo1/out)`可执行文件的输出路径，文件夹会自行创建  
    * `include_directories(${PROJECT_SOURCE_DIR}/include)`指定头件的路径  
    * `add_executable(app ${SRC})`将SRC的内容提取到app可执行文件  
    * `set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)` 指定库的输出路径  
    * linux中的库文件 .a是静态库，.so是动态库  
    * `link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib1)`连接当前CMakeLists.txt文件夹下的库文件目录（动态库和静态库都可以链接）
    * `link_libraries(calc)`连接静态库文件（可以包含多个）  
    * 静态库的二进制文件内容会跟SRC变量一起打包在可执行的二进制文件中，而动态库不会
    * `target_link_libraries(app calc)`必须写在生成的可执行文件后面，即`add_executable()`后，链接动态库，第一个参数是需要链接动态库的源文件或者可执行文件，之后就是动态库  

    


    eg:   
```
#[[这是一个CMakeLists.txt文件]]
cmake_minimum_required(VERSION 3.15)
project(test)
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)#可以递归搜索
#aux_source_directory($ {PROJECT_SOURCE_DIR} SRC ) #搜索指定文件夹下所有文件放在变量SRC中
#set(SRC add.cpp mulit.cpp main.cpp)#将cpp文件编译后结果放进变量SRC
#set(EXECUTABLE_OUTPUT_PATH /home/zty/cmake_study/demo1/out)#输出路径，文件夹会自行创建
set(CMAKW_CXX_STANDARD 11)#指定c++的标准
include_directories(${PROJECT_SOURCE_DIR}/include)#指定头件的路径
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
#add_executable(app ${SRC})#将SRC的内容提取到app可执行文件  
add_library(calc SHARED ${SRC})
```






      




    
   



