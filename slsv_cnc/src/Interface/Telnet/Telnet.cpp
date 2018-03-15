// This provides a telnet interface to the openOcd Debug module
// Adapted from \/ Sean Middleditch`s libtelnet library  
// @ https://github.com/seanmiddleditch/libtelnet


// I am dissapointed by the fact that I`m having to use such an infefiicennt approach to transfer data
// apparently i have two restrictions on me being 
// Telnet server only acting on printable chars ? - from a quick skimmy
// Telnet server having a max line lenght(MaxLen) which i can change

// So how i see this given the small time frame i have to deliver poc in
//	4b	// "SLSV" - application identifier
//	1b	// " " delimiter
//	1b	// "<ANY_PRINTABLECHAR>" operation select using an enum
//	1b	// " " delimiter
//	MaxLen-8b	// "N*<hex>" This is the argument passed to command formatted to the constraints im presented.
//	1b	// NewLine

// and apparently the MaxLen is magically 10*256 - looks like someone else is also trying to hack this for more utility old version was just 256 XD
// and the openocd telnet server sadly echoes everything you putinto it :P
// i think I should really just write a new server option for openocd after Im done with this - work for future inters !! :] 

#include "libtelnet.hpp"
#include <iostream>
#include <vector>

// sleep required ? 
#include <chrono>
#include <thread>

void wrap_event_handler(TelnetOCD *a,telnet_t *telnet, telnet_event_t *ev,void *user_data){
	(*a)._event_handler(telnet,ev,user_data);
}

static int getPackedHex(uint64_t* vector,uint count,char* hexString,uint width){
	// witdth is the width in bytes :: 8 for 32b , 16 for 64b
	//*count = strlen(sexString)/width; // the maximum number of segments of width extractable
	//vector = malloc(sizeof(uint64_t)*count);  // This seems better off is done by the calling fucntion
	// the range 32-126 is 94 printable ascii characters , 32 being the space symbol where string parseing will break the string
	//LOG_ERROR("SLSV string:: %s, width :: %u" ,hexString,width);
	char temp[32+1]; // assuming the widest word rv128 is 128 bits wide // Plus one to hold the null terminator
	for(uint i = 0;i<count;i++){
		// put error catching on the returns of strncpy and sscanf
		strncpy(temp,(hexString+(i*width)),width);
		temp[width] = '\0';
		sscanf(temp,"%lx",vector+i);
		//LOG_ERROR("SLSV parsed integer:: %lu , string:: %s,string:: %s" ,*(vector+i),temp,(hexString+(count*width)));
	}
	return 0;
}

// Wrapper Functions to the TelnetOCD class
TelnetOCD::TelnetOCD(std::string ip,std::string port,uint abits,uint width){

	return;
}

TelnetOCD::~TelnetOCD(){
	_cleanup();
	telnet_free(telnet);
	close(sock);
	return;
}

bool TelnetOCD::set_ip_port(std::string ip, int port){
	HostName = ip;
	PortNumber = port; 
	return true;
}


bool TelnetOCD::is_alive(){
	return true;
}

bool TelnetOCD::runCommand(std::string command,char* response){
	char str[512];
	strcpy(str,command.c_str());
	//printf("%s\r\n",command.c_str());
		/* read from stdin */
	//if(poll(pfd, 2, -1) != -1){
			rs = strlen(str);
			_input(str, rs);
	//}
	while (poll(pfd, 2, 20) != -1) {
		/* read from client */
		if (pfd[1].revents & POLLIN) {
			rs = recv(sock, buffer, sizeof(buffer), 0);
			if (rs > 0) {
				telnet_recv(telnet, buffer, rs);
				buffer[rs] = 0;
				//std::cout<< buffer << std::endl;
			} else if (rs == 0) {
				break;
			} else {
				fprintf(stderr, "recv(client) failed: %s\n",
						strerror(errno));
				exit(1);
			}
		} 
		else{
			break;
		} 
	}
	// printf("[%s]",telnet->response_buffer);
	// Parsing reply
	// Wait till some known Response // if not known response that means some error occured or things are taking too long
	response = telnet->response_buffer;

	//uint64_t results[10];
	//getPackedHex(results,(telnet->response_len)/16,telnet->response_buffer,16);
	//for(uint i = 0 ; i < (telnet->response_len)/16 ; i++)printf("%016lx\r\n" , results[i]);
	return true;
}

uint64_t* TelnetOCD::getMemory(uint64_t address ,uint64_t length,int width){
	return NULL;
}

bool TelnetOCD::setMemory(uint64_t address,uint64_t length,uint64_t* source,int width){
	
	return true;
}

bool TelnetOCD::getAbstReg(uint64_t* result,uint32_t hartid,uint32_t regno,uint32_t length,int width){
	// add the hart id support in a bit
	// compose the command message
	char str[512];
	strcpy(str,"slsv 4 ");
	char* position = str + strlen(str);
	uint l = 0;
	while(l < length){
		sprintf(position,"%05x",regno+l); position +=5;	
		l++;
	}
	sprintf(position,"\n"); position +=1;	
	//printf("%s\r\n",str);

	// send the message
	rs = strlen(str);
	_input(str, rs);
	// get the response
		while (poll(pfd, 2, 20) != -1) {
			/* read from client */
			if (pfd[1].revents & POLLIN) {
				rs = recv(sock, buffer, sizeof(buffer), 0);
				if (rs > 0) {
					telnet_recv(telnet, buffer, rs);
					buffer[rs] = 0;
					//std::cout<< buffer << std::endl;
				} else if (rs == 0) {
					break;
				} else {
					fprintf(stderr, "recv(client) failed: %s\n",
							strerror(errno));
					exit(1);
				}
			} 
			else{
				break;
			} 
		}
		
	getPackedHex(result,(telnet->response_len)/16,telnet->response_buffer,16);
	//for(uint i = 0 ; i < (telnet->response_len)/16 ; i++) printf(">>%016lx<<\r\n" , result[i]);
	return true;
}

bool TelnetOCD::setAbstReg(uint32_t hartid,uint32_t regno,uint32_t length,uint64_t* source,int width){
		
	return true;
}

	
int TelnetOCD::send_message(const char* message){
//	poll(pfd, 2, -1) != -1
//	/* read from stdin */
//	pfd[0].revents & POLLIN // some condition that stdin has something
	rs = strlen(message-1);
	strncpy(buffer,message,rs); // essenta.step(1);ially fill buffer srom stdin
	_input(buffer, rs); // handle the terminal usaer input
//
	return 0;
}

char* TelnetOCD::get_response(int bytes){
	// is this comment correct  ? :: /* read from client */
	if(pfd[1].revents & POLLIN){
		if((rs = recv(sock, buffer, sizeof(buffer), 0)) > 0)telnet_recv(telnet, buffer, rs);			
	}
	return buffer;
}



void TelnetOCD::_cleanup(void) {
	tcsetattr(STDOUT_FILENO, TCSADRAIN, &orig_tios);
}

void TelnetOCD::_input(char *buffer, int size) {
	static char crlf[] = { '\r', '\n' };
	int i;
	telnet->lcbfr_len = size;
	strncpy(telnet->lc_buffer , buffer , size);
	telnet->lc_buffer[size] = 0;
	for (i = 0; i != size; ++i) {
		/* if we got a CR or LF, replace with CRLF
		 * NOTE that usually you'd get a CR in UNIX, but in raw
		 * mode we get LF instead (not sure why)
		 */
		if (buffer[i] == '\r' || buffer[i] == '\n') {
			//if (do_echo)printf("\r\n");
			telnet_send(telnet, crlf, 2);
		} else {
			//if (do_echo)putchar(buffer[i]);
			telnet_send(telnet, buffer + i, 1);
		}
	}
	fflush(stdout);
}

void TelnetOCD::_send(int sock, const char *buffer, size_t size) {
	int rs;

	/* send data */
	while (size > 0) {
		if ((rs = send(sock, buffer, size, 0)) == -1) {
			fprintf(stderr, "send() failed: %s\n", strerror(errno));
			exit(1);
		} else if (rs == 0) {
			fprintf(stderr, "send() unexpectedly returned 0\n");
			exit(1);
		}

		/* update pointer and size to see if we've got more to send */
		buffer += rs;
		size -= rs;
	}
}

void TelnetOCD::_event_handler(telnet_t *telnet, telnet_event_t *ev,
		void *user_data) {
	int sock = *(int*)user_data;

	switch (ev->type) {
	/* data received */
	case TELNET_EV_DATA:
		// if (ev->data.size && fwrite(ev->data.buffer, 1, ev->data.size, stdout) != ev->data.size) {
        //       		fprintf(stderr, "ERROR: Could not write complete buffer to stdout");
		// }
		fflush(stdout);
		break;
	/* data must be sent */
	case TELNET_EV_SEND:
		_send(sock, ev->data.buffer, ev->data.size);
		break;
	/* request to enable remote feature (or receipt) */
	case TELNET_EV_WILL:
		/* we'll agree to turn off our echo if server wants us to stop */
		if (ev->neg.telopt == TELNET_TELOPT_ECHO)
			do_echo = 0;
		break;
	/* notification of disabling remote feature (or receipt) */
	case TELNET_EV_WONT:
		if (ev->neg.telopt == TELNET_TELOPT_ECHO)
			do_echo = 0;
		break;
	/* request to enable local feature (or receipt) */
	case TELNET_EV_DO:
		break;
	/* demand to disable local feature (or receipt) */
	case TELNET_EV_DONT:
		break;
	/* respond to TTYPE commands */
	case TELNET_EV_TTYPE:
		/* respond with our terminal type, if requested */
		if (ev->ttype.cmd == TELNET_TTYPE_SEND) {
			telnet_ttype_is(telnet, getenv("TERM"));
		}
		break;
	/* respond to particular subnegotiations */
	case TELNET_EV_SUBNEGOTIATION:
		break;
	/* error */
	case TELNET_EV_ERROR:
		fprintf(stderr, "ERROR: %s\n", ev->error.msg);
		exit(1);
	default:
		/* ignore */
		break;
	}
}

bool TelnetOCD::Tconnect(){
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	// PLZZZ FIXME !!!!! the line below is absolute crap.
	if ((rs = getaddrinfo(HostName.c_str(), std::to_string(PortNumber).c_str(), &hints, &ai)) != 0) {
		fprintf(stderr, "getaddrinfo() failed for %s: %s\n", HostName.c_str(),
				gai_strerror(rs));
		return 1;
	}
	
	/* create server socket */
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "socket() failed: %s\n", strerror(errno));
		return 1;
	}
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
	/* bind server socket */
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		fprintf(stderr, "bind() failed: %s\n", strerror(errno));
		return 1;
	}

	/* connect */
	if (connect(sock, ai->ai_addr, ai->ai_addrlen) == -1) {
		fprintf(stderr, "connect() failed: %s\n", strerror(errno));
		return 1;
	}

	/* free address lookup info */
	freeaddrinfo(ai);

	/* get current terminal settings, set raw mode, make sure we
	 * register atexit handler to restore terminal settings
	 */
	tcgetattr(STDOUT_FILENO, &orig_tios);
	//void (*fptr)() = (void(*))_cleanup;
	
	tios = orig_tios;
	cfmakeraw(&tios);
	tcsetattr(STDOUT_FILENO, TCSADRAIN, &tios);

	/* set input echoing on by default */
	do_echo = 1;

	/* initialize telnet box */
	//wrap_event_handler
	//void point = this._event_handler;
	telnet = telnet_init(telopts,wrap_event_handler, 0, &sock,this);
	//telnet = telnet_init(telopts, _event_handler, 0, &sock);

	/* initialize poll descriptors */
	memset(pfd, 0, sizeof(pfd));
	pfd[0].fd = 0;// STDIN_FILENO;
	pfd[0].events = POLLIN;
	pfd[1].fd = sock;
	pfd[1].events = POLLIN;


	return true;
}

	// 	// put error catching on the returns of strncpy and sscanf
	// 	strncpy(temp,(hexString+(count*width)),width);
	// 	temp[width] = '\0';
	// 	sscanf(temp,"%lux",vector+i);
	// uint width = (*hex) - 32;
/*
int main(){
	TelnetOCD a("localhost","4444",6,32);
	a.set_ip_port("localhost",4444);
	a.Tconnect();
	uint64_t results[1024];
	char* result;
	while(1){
		a.getAbstReg(results,0,0x7b0,100,1);
		//a.getAbstReg(results,0,0x0,10,1);
		//a.getAbstReg(results,0,0x7b0,10,1);
		a.runCommand("slsv 2\n",result);
	}
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//a.getAbstReg(results,0,0x20,10,1);
	//a.runCommand("slsv 2\n",result);
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	////a.getAbstReg(results,0,0x20,10,1);
	//a.runCommand("slsv 2\n",result);
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	////a.getAbstReg(results,0,0x20,10,1);
	//a.runCommand("slsv 2\n",result);
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	////a.getAbstReg(results,0,0x20,10,1);
	//a.runCommand("slsv 2\n",result);
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//a.getAbstReg(results,0,0x20,10,1);
	//printf("%016lx\n\r",results[0]);
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	return 0;
}
//a.runCommand("slsv 0\n",result);
//a.runCommand("slsv 1\n",result);
//a.runCommand("slsv 0\n",result);	
//Commands.push_back("slsv 3 0000000000000001\n");
//Commands.push_back("slsv 4 0002000021000220002300024\n");
//Commands.push_back("slsv 4 0002000021000220002300024\n");
//Commands.push_back("slsv 0\n");
//Commands.push_back("slsv 4 0002000021000220002300024\n");
//Commands.push_back("slsv 4 0002000021000220002300024\n");
	
*/