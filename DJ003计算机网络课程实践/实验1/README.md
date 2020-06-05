### 介绍

路径下有一个客户端和一个服务端的源代码

```
client.cpp server.cpp
```

### 编译方法

1. 使用命令`g++ -o client client.cpp`和`g++ -o server server.cpp`即可编译两个程序，
2. 为了使用方便，我编写了一个脚本

```bash
$cat build.sh
g++ -o client client.cpp
g++ -o server server.cpp
```

然后只需要执行此脚本即可编译两个程序

### 异常解决

#### command not found ....

如果使用命令编译或者启动脚本编译出现输出`bash: command not found:g++`那么说明本机没有安装g++编译环境。

如果是在ubuntu/Debian环境下使用以下命令即可安装g++

```bash
sudo apt update;
sudo apt install g++;
```

如果是在CentOS环境下使用以下命令

```bash
sudo yum install g++;
```

如果是在macos环境，系统自带clang++，无需安装g++

```bash
clang++ -o client.cpp
```

为了方便再mac下编译，我修改了build脚本

```bash
$cat build.sh
if [ $(uname) == "Darwin" ];then
    clang++ -o client client.cpp;
    clang++ -o server server.cpp;
    exit
fi
g++ -o client client.cpp
g++ -o server server.cpp
```

使得其可以更好的在mac下编译

#### 其他异常

请邮件联系dashjay@aliyun.com以获得更多的技术支持。