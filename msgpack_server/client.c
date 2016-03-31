#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero
/*
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
*/
 
#define HELLO_WORLD_SERVER_PORT    6666 
#define BUFFER_SIZE 1024 
#define FILE_NAME_MAX_SIZE 512

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
//    if(argc != 2){
//        printf("please input json string\n");
//        exit(1);
//    }

    //char IP[] = "127.0.0.1";
    char IP[] = "10.0.2.15";
 
    struct sockaddr_in client_addr;
    bzero(&client_addr,sizeof(client_addr)); 
    client_addr.sin_family = AF_INET;    
    client_addr.sin_addr.s_addr = htons(INADDR_ANY);
    client_addr.sin_port = htons(0);    
    
    int client_socket = socket(AF_INET,SOCK_STREAM,0);
    if( client_socket < 0)
    {
        printf("Create Socket Failed!\n");
        exit(1);
    }

    if( bind(client_socket,(struct sockaddr*)&client_addr,sizeof(client_addr)))
    {
        printf("Client Bind Port Failed!\n"); 
        exit(1);
    }
 
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    if(inet_aton(IP, &server_addr.sin_addr) == 0) 
    {
        printf("Server IP Address Error!\n");
        exit(1);
    }
    server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);
    socklen_t server_addr_length = sizeof(server_addr);
    
    if(connect(client_socket,(struct sockaddr*)&server_addr, server_addr_length) < 0)
    {
        printf("Can Not Connect To %s!\n", IP);
        exit(1);
    }
    
	wchar_t buffer[]=L"{\n\"name\": \"德克士\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";	
    //wchar_t buffer[] = L"哈哈";
    char str[BUFFER_SIZE] = {0};
    wcstombs(str, buffer, BUFFER_SIZE);
    printf("%s\n",str);
    send(client_socket, str, BUFFER_SIZE, 0);
    int length = 0;
    while( length = recv(client_socket,buffer,BUFFER_SIZE,0))
    {
        if(length < 0)
        {
            printf("Recieve Data From Server %s Failed!\n", argv[1]);
            break;
        }else{
            printf("Response From Server: %s\n",buffer);
        }
    }

    close(client_socket);
    return 0;
}
