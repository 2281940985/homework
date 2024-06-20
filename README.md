# 学习心得  
## C++基础知识  
*  vscode基础设置  
    task.json文件配置：  
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
* launch.json文件配置
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



      




    
   



