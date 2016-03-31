#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero

#include "cJSON.h"
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

char *doit(char *text)
{
	char *out; cJSON *json;
	
    json=cJSON_Parse(text);
	if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
	else
	{
		out=cJSON_Print(json);
		cJSON_Delete(json);
		printf("%s\n",out);
	}

    return out;
}

cJSON *GetJSON(char * text){
    cJSON *json = cJSON_Parse(text);
	if (!json) {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
    }

    return json;
}

void parseJSON(cJSON *json){
        cJSON *root = json;
        cJSON *node = root->child;
        while(node != NULL){
            cJSON * val = node->child;
            char *name = val->valuestring;
            val = val->next;
            int age = val->valueint;
            printf("name: %s, age: %d\n", name, age);
            node = node->next;
        }
}

char * GetName(cJSON *json){
	char *name;
    cJSON *json_value;

    json_value = cJSON_GetObjectItem(json, "name"); 
    if( json_value->type == cJSON_String){
        name = json_value->valuestring;
    }

    return name;
}

int GetAge(cJSON *json){
	int age;
    cJSON *json_value;

    json_value = cJSON_GetObjectItem(json, "age"); 
    if( json_value->type == cJSON_Number){
        age = json_value->valueint;
    }
   	
    return age;
}
 
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
         
        char buffer[BUFFER_SIZE];
        bzero(buffer, BUFFER_SIZE);
        //request
        length = recv(new_server_socket,buffer, BUFFER_SIZE, 0);
        if (length < 0)
        {
            printf("Server Recieve Data Failed!\n");
            break;
        }else{
            printf("-----------------Request:%d-----------------\n%s\n-----------------JSON-------------------\n",new_server_socket, buffer);
        } 

        //do something
        cJSON *json = GetJSON(buffer); 
        parseJSON(json);
        cJSON_Delete(json);
        char *response = doit(buffer); 
        //response
        if(send(new_server_socket, response, strlen(response), 0)<0)
        {
            printf("Send Response:\t%s Failed\n", response);
            break;
        }
        printf("-----------------FINISH-------------------\n\n\n");
        free(response);
        bzero(buffer, BUFFER_SIZE);
        close(new_server_socket);
    }

    close(server_socket);
    return 0;
}
