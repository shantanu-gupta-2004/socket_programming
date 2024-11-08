#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<unistd.h>
#include<cstring>

using namespace std;

int main(){
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serverAdd;
  serverAdd.sin_family = AF_INET;
  serverAdd.sin_port = htons(2000);
  serverAdd.sin_addr.s_addr = INADDR_ANY;
  connect(clientSocket, (struct sockaddr*)&serverAdd, sizeof(serverAdd));
  char res[1024]={0};
  read(clientSocket, res, 256);
  cout<<"The server response is: "<<res;
  close(clientSocket);
  return 0;
}
