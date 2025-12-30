#include <cstring>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include "protocol.h"

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

void sender(int sockfd) {
    ChatParser chat_parser;
    while (true)
    {   
        
        std::string message;
        std::cout << "请输入要发送的消息 (输入 'exit' 退出): ";
        std::getline(std::cin, message);
        if (message == "exit") {
            exit(0);
        }
        auto msg=chat_parser.serialize(message);
        ssize_t bytes_sent = send(sockfd, msg.data(),msg.size(), 0);
        if (bytes_sent < 0) {
            std::cerr << "发送消息失败" << std::endl;
            break;
        }
    }
}
void receiver(int sockfd){
    while(1){
        char buffer[BUFFER_SIZE];
        ssize_t bytes_received=recv(sockfd,buffer,BUFFER_SIZE-1,0);
        if(bytes_received>0){
            buffer[bytes_received]='\0';
            std::cout<<"服务端: "<<buffer<<std::endl;
        }
        else if(bytes_received==0){
            std::cout<<"服务器断开连接"<<std::endl;
            break;
        }
        else{
            std::cerr<<"接收消息失败"<<std::endl;
            break;
        }
    }



}

int main(int argc, char const *argv[])
{
    int clientfd;
    sockaddr_in server_addr;
    //创建socket// 
    clientfd=socket(AF_INET,SOCK_STREAM,0);
    if (clientfd<0)
    {
        std::cerr<<"无法创建socket"<<std::endl;
        return 1;
    }
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(PORT);
    inet_pton(AF_INET,SERVER_IP,&server_addr.sin_addr);


    //连接服务器//
    if(connect(clientfd,(sockaddr *)&server_addr,sizeof(server_addr))<0){
        std::cerr<<"连接服务器失败"<<std::endl;
        close(clientfd);
        return 1;
    }
    std::cout<<"已连接到服务器"<<std::endl;

    std::thread send_thread, recv_thread;
    //创建发送线程//  
    send_thread = std::thread(sender, clientfd);
    //创建接收线程//    
    recv_thread = std::thread(receiver, clientfd);

    
    send_thread.join();
    recv_thread.join();


    close(clientfd);



    return 0;
}
