#include<czmq.h>

int main(int argc, char **argv){
    zsock_t *responder = zsock_new(ZMQ_REP);
    int r = zsock_bind(responder, "tcp://*:5555");
    if(r!=5555){
        printf("Failed to bind port\n");
    }
    while(true){
        char *msg = zstr_recv(responder);
        if(!strcmp(msg, "Hello")){
            zstr_send(responder, "Hello Shantanu");
        }
        free(msg);
    }
    zsock_destroy(&responder);
}