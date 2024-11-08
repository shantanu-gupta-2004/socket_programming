#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<cstring>

using namespace std;

int main(){
   int server_fd = socket(AF_INET, SOCK_STREAM, 0); //it creates a TCP socket using IPv4
   if(server_fd == -1){
     cerr<<"Socket creation failed"<<endl;
     return -1;
   }
   sockaddr_in address; //declares an address structure to store info
   address.sin_family = AF_INET; //sets address family to IPv4
   address.sin_addr.s_addr = INADDR_ANY; //sets IP to any allowing server to accept on any host
   address.sin_port = htons(9090); //specifies port number 8080 where htons is use to convert to byte order
   if(bind(server_fd, (struct sockaddr*)&address, sizeof(address))<0){
     cerr<<"Bind failed"<<endl;
     return -1;
   }
   //The above binds socket to specified IP and port
   if(listen(server_fd, 3)<0){
     cerr<<"Listen failed"<<endl;
     return -1;
   }
   //marks socket as listening socket with queue size as 3
   cout<<"Server is listening on port 9090\n";
   int addrlen = sizeof(address);
   int new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
   // new_socket waits for client to connect if accept faisl return -1
   if(new_socket<0){
      cerr<<"Accept failed"<<endl;
      return -1;
   }
   cout<<"Connection accepted"<<endl;
   const char *message = "Hello from Server";
   send(new_socket, message, strlen(message), 0);
   close(new_socket);
   close(server_fd);
   return 0;
}
