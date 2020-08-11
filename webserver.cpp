#include<iostream>
#include<cstdio>
#include<sys/socket.h>
#include<unistd.h>
#include<cstring>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/sendfile.h>

using namespace std;

#define PORT 8888

int main(){
    //build and init tcp socket.
    int tcpsock = socket(AF_INET, SOCK_STREAM, 0);
    
    //build and init addr.
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);
    cout << "init success!" << endl;
        
    //bind socket.
    bind(tcpsock, (struct sockaddr*)& addr, sizeof(addr));
    cout << "bind success!" << endl;

    //listen tcp socket
    listen(tcpsock, 10);
    cout << "listen success!" << endl;
     
    while(true){
	struct sockaddr_in client;
	socklen_t client_addr_length = sizeof(client);

	int connfd = accept(tcpsock, (struct sockaddr *)& client, &client_addr_length);
	if(connfd < 0){
	    cout << "receive fail!" << endl;
	}else{
	    int fd = open("./html/t1.html", O_RDONLY);
	    char recv_buf[1024];
	    char send_msg[] = "hello, world!";
	    char buf[520] = "HTTP/1.1 200 ok\r\nconnection: close\r\n\r\n";
		int fd = open("html/1.html", O_RDONLY);
//	    int s = send(connfd, buf, strlen(buf), 0);
//	    recv(connfd, recv_buf, 1024, 0);
//	    cout << "receive success!" << endl;
	    sendfile(connfd, fd, NULL, 2500);

	    close(connfd); 
	}
	

    }
    return 0;
}
