#include "server_header.h"
#include<cstring>

using namespace std;

int main(){
   int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
   struct sockaddr_in address;
   char buffer[100], file[1000];
   bzero(&address, sizeof(address));
   address.sin_family = AF_INET;
   address.sin_port = htons(9002);
   address.sin_addr.s_addr = inet_addr("127.0.0.1");
   connect(serverSocket, (struct sockaddr*)&address, sizeof(address));
   while(true){
      cout<<"File name: ";
      cin>>buffer;
      send(serverSocket, buffer, strlen(buffer)+1, 0);
      if(strcmp(buffer, "exit")==0){
        cout<<"Exiting!"<<endl;
        break;
      }
      cout<<"File output: "<<endl;
      recv(serverSocket, &file, sizeof(file), 0);
      cout<<file;
}
   close(serverSocket);
   return 0;
}
