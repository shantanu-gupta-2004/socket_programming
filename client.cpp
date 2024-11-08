#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
using namespace std;

int main(){
   int client_fd = socket(AF_INET, SOCK_STREAM, 0);
   if(client_fd<0){
     cerr<<"Socket creation failed"<<endl;
     return -1;
   }
   sockaddr_in server_address;
   server_address.sin_family = AF_INET;
   server_address.sin_port = htons(9090);
   if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr)<=0){
     cerr<<"Invalid address"<<endl;
     return -1;
   }
   if(connect(client_fd, (struct sockaddr*)&server_address, sizeof(server_address))<0){
     cerr<<"Connection failed";
     return -1;
   }
   cout<<"Connected to server"<<endl;
   char buffer[1024]={0};
   read(client_fd, buffer, 1024);
   cout<<"Server: "<<buffer<<endl;
   close(client_fd);
   return 0;

}
