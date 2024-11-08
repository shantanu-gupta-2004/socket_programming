#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<unistd.h>
#include<cstring>

using namespace std;

int main(){
  int serverSocket = socket(AF_INET, SOCK_STREAM,0);
  struct sockaddr_in serverAdd;
  serverAdd.sin_family = AF_INET;
  serverAdd.sin_port = htons(2000);
  serverAdd.sin_addr.s_addr = INADDR_ANY;
  bind(serverSocket, (struct sockaddr*)&serverAdd, sizeof(serverAdd));
  listen(serverSocket, 7);
  int addLen = sizeof(serverAdd);
  int clientSocket = accept(serverSocket, NULL, NULL);
  char msg[256] = "Hello from TCP server!";
  send(clientSocket, msg, sizeof(msg), 0);
  close(serverSocket);
  return 0;
}
