if [ $(uname) == "Darwin" ];then
    clang++ -o client client.cpp;
    clang++ -o server server.cpp;
    exit
fi
g++ -o client client.cpp
g++ -o server server.cpp
