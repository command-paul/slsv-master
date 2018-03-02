// This provides a telnet interface to the openOcd Debug module
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

class TelnetOCD{
public:
	TelnetOCD();
	~TelnetOCD();
	bool is_alive();
	bool step(int n);
	bool set_ip_port(std::string ip,int port);
private:
	std::string HostName;
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[4096];
	int send_message(char* message);
	char* get_response(int bytes);
};

void error(const char *msg){
	perror(msg);
}

TelnetOCD::TelnetOCD(){
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	server = gethostbyname(HostName.c_str());
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
		 (char *)&serv_addr.sin_addr.s_addr,
		 server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR connecting");
	return;
}

TelnetOCD::~TelnetOCD(){
	close(sockfd);
	return;
}

bool TelnetOCD::set_ip_port(std::string ip, int port){
	return true;
}


bool TelnetOCD::is_alive(){
	return true;
}

bool TelnetOCD::step(int n){
	return true;
}

int TelnetOCD::send_message(char* message){
	bzero(buffer,256);
	int l_message = strlen(message);
	int sent =0;
	while(sent < l_message){
		fgets(buffer,255,stdin);
		n = write(sockfd,buffer,strlen(buffer));
		if (n < 0) 
			 error("ERROR writing to socket");
	}
	return 0;
}

char* TelnetOCD::get_response(int bytes){
	int recieved = read(sockfd,buffer,255);
	if (n < bytes) error("ERROR reading from socket");
	printf("%s\n",buffer);
	bzero(buffer,256);
}

int main(){
	TelnetOCD a;
	a.set_ip_port("0.0.0.0",3456);
	if(a.is_alive()){
		a.step(1);
	}
	return 0;
}