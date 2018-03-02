// This provides a telnet interface to the openOcd Debug module
// Adapted from \/ Sean Middleditch`s libtelnet library  
// @ https://github.com/seanmiddleditch/libtelnet

#include "libtelnet.hpp"
#include <iostream>

void wrap_event_handler(TelnetOCD *a,telnet_t *telnet, telnet_event_t *ev,void *user_data){
	(*a)._event_handler(telnet,ev,user_data);
}

// Wrapper Functions to the TelnetOCD class
TelnetOCD::TelnetOCD(){

	return;
}

TelnetOCD::~TelnetOCD(){
	_cleanup();
	telnet_free(telnet);
	close(sock);
	return;
}

bool TelnetOCD::set_ip_port(std::string ip, int port){
	return true;
}


bool TelnetOCD::is_alive(){
	return true;
}

bool TelnetOCD::step(int n){
	std::string step_str = "step\n";
	send_message(step_str.c_str());
	return true;
}



int TelnetOCD::send_message(const char* message){
//	poll(pfd, 2, -1) != -1
//	/* read from stdin */
//	pfd[0].revents & POLLIN // some condition that stdin has something
//	rs = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0 // essentially fill buffer srom stdin
//	_input(buffer, rs); // handle the terminal usaer input
//
	return 0;
}

char* TelnetOCD::get_response(int bytes){
// is this comment correct  ? :: /* read from client */
	//pfd[1].revents & POLLIN
	//rs = recv(sock, buffer, sizeof(buffer), 0)) > 0
	//telnet_recv(telnet, buffer, rs);		
	///* clean up */
	return buffer;
}



void TelnetOCD::_cleanup(void) {
	tcsetattr(STDOUT_FILENO, TCSADRAIN, &orig_tios);
}

void TelnetOCD::_input(char *buffer, int size) {
	static char crlf[] = { '\r', '\n' };
	int i;

	for (i = 0; i != size; ++i) {
		/* if we got a CR or LF, replace with CRLF
		 * NOTE that usually you'd get a CR in UNIX, but in raw
		 * mode we get LF instead (not sure why)
		 */
		if (buffer[i] == '\r' || buffer[i] == '\n') {
			if (do_echo)
				printf("\r\n");
			telnet_send(telnet, crlf, 2);
		} else {
			if (do_echo)
				putchar(buffer[i]);
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
		if (ev->data.size && fwrite(ev->data.buffer, 1, ev->data.size, stdout) != ev->data.size) {
              		fprintf(stderr, "ERROR: Could not write complete buffer to stdout");
		}
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
			do_echo = 1;
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
	pfd[0].fd = STDIN_FILENO;
	pfd[0].events = POLLIN;
	pfd[1].fd = sock;
	pfd[1].events = POLLIN;

	return true;
}



int main(){
	TelnetOCD a;
	a.set_ip_port("localhost",10001);
	a.Tconnect();
	if(a.is_alive()){
		a.step(1);
	}
	return 0;
}