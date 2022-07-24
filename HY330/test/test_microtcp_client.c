
 
#include "../lib/microtcp.h"
#include "../lib/microtcp.c"

int
main(int argc, char **argv)
{
	
	struct sockaddr_in si_me;
	microtcp_sock_t cl;
	int bindx;
	memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(9000);
    si_me.sin_addr.s_addr =inet_addr("127.0.0.1");
    
	cl=microtcp_socket(AF_INET,SOCK_DGRAM,0);
    
	

    cl=microtcp_connect(cl,(const struct sockaddr *)&si_me,sizeof(si_me));



}
