#include "server_header.h"
#include<cstring>
using namespace std;

int main(){
  int size;
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serverAdd, clientAdd;
  socklen_t clientLen;
  struct stat statVariable; //used to store info about the file
  char buffer[100], file[1000]; //store filename and content
  FILE *filepointer;
  bzero(&serverAdd, sizeof(serverAdd)); //zeroes out the server adddress for consistency
  serverAdd.sin_family = AF_INET;
  serverAdd.sin_port = htons(9002);
  serverAdd.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(serverSocket, (struct sockaddr*)&serverAdd, sizeof(serverAdd));
  listen(serverSocket,7);
  cout<<"Server is listening"<<endl;
  int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAdd, &clientLen);
  while(true){
     bzero(buffer, sizeof(buffer));
     bzero(file, sizeof(file));
     recv(clientSocket, buffer, sizeof(buffer), 0);
     if(strcmp(buffer, "exit")==0){
       cout<<"Client requests to exit. Closing"<<endl;
       break;
     }
     filepointer = fopen(buffer, "r");
     if(filepointer==NULL){
       char msg[] = "File not found!\n";
       send(clientSocket, msg, sizeof(msg), 0);
       continue;
     }
     stat(buffer, &statVariable);
     size = statVariable.st_size;
     fread(file, sizeof(file), 1, filepointer);
     send(clientSocket, file, sizeof(file), 0);
     fclose(filepointer);
}
  close(serverSocket);
  close(clientSocket);
  return 0;
}
