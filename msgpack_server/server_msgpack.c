#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero

//#include <msgpack.h>
//#include "../../githup/MessagePack/messagepack/msgpack-c/src/objectc.c"
//#include "../../githup/MessagePack/messagepack/msgpack-hulu/parser.c"
#include "../../githup/MessagePack/messagepack/msgpack-hulu/packer.c"

/*
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
*/
#define HELLO_WORLD_SERVER_PORT  6666 
#define LENGTH_OF_LISTEN_QUEUE 20
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512

void msg_print(char const* buf, unsigned int len)
{
    size_t i = 0;
    for(; i < len ; ++i)
        printf("%02x ", 0xff & buf[i]);
    printf("\n");
}

//void msg_unpack(char const* buf, size_t len) {
//    /* buf is allocated by client. */
//    msgpack_unpacked result;
//    size_t off = 0;
//    msgpack_unpack_return ret;
//    int i = 0;
//    msgpack_unpacked_init(&result);
//    ret = msgpack_unpack_next(&result, buf, len, &off);
//    while (ret == MSGPACK_UNPACK_SUCCESS) {
//        msgpack_object obj = result.data;
//
//        /* Use obj. */
//        printf("Object no %d:\n", ++i);
//        msgpack_object_print(stdout, obj);
//        printf("\n");
//        /* If you want to allocate something on the zone, you can use zone. */
//        /* msgpack_zone* zone = result.zone; */
//        /* The lifetime of the obj and the zone,  */
//
//        ret = msgpack_unpack_next(&result, buf, len, &off);
//    }
//    msgpack_unpacked_destroy(&result);
//
//    if (ret == MSGPACK_UNPACK_CONTINUE) {
//        printf("All msgpack_object in the buffer is consumed.\n");
//    }
//    else if (ret == MSGPACK_UNPACK_PARSE_ERROR) {
//        printf("The data in the buf is invalid format.\n");
//    }
//}

int main(int argc, char **argv)
{
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    //server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_addr.s_addr = inet_addr("192.168.33.10");
    server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
 
    int server_socket = socket(PF_INET,SOCK_STREAM,0);
    if( server_socket < 0)
    {
        printf("Create Socket Failed!");
        exit(1);
    }

    int opt =1;
    setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
     
    if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
    {
        printf("Server Bind Port : %d Failed!", HELLO_WORLD_SERVER_PORT); 
        exit(1);
    }
 
    if ( listen(server_socket, LENGTH_OF_LISTEN_QUEUE) )
    {
        printf("Server Listen Failed!"); 
        exit(1);
    }
    while (1) 
    {
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);
 
        int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
        if ( new_server_socket < 0)
        {
            printf("Server Accept Failed!\n");
            break;
        }
         
        unsigned char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);
        //request
        length = recv(new_server_socket, buffer, BUFFER_SIZE, 0);
        if (length < 0)
        {
            printf("Server Recieve Data Failed!\n");
            break;
        }else{
            printf("-----------------Request:%d-----------------\n",new_server_socket);
            print(buffer, length);
        } 

        //do something
        printf("\n============unpacking==============\n");
        Object *obj = MessageUnpacker(buffer, length);
        printf("============packing==============\n");
        PackBuffer *pb = MessagePacker(obj);
        printf("============printJSON==============\n");
        printJSON(obj);
        printf("============printTree==============\n");
        printTree(obj, 0);
        printf("\n-----------------Response:%d-----------------\n",new_server_socket);
        print(pb->buffer, pb->off);
        const ubyte_t *response = pb->buffer; 
        //response
        if(send(new_server_socket, response, pb->off, 0)<0)
        {
            printf("Send Response:\t%s Failed\n", response);
            break;
        }
        printf("-----------------FINISH-------------------\n\n\n");
        bzero(buffer, BUFFER_SIZE);
        close(new_server_socket);
    }

    close(server_socket);
    return 0;
}
