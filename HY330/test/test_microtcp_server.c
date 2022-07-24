#include "../lib/microtcp.h"
#include "../lib/microtcp.c"


int
main(int argc, char **argv)
{
	microtcp_sock_t srv;
	int bindsrv;
   struct sockaddr_in si_me;
   
   memset((char *) &si_me, 0, sizeof(si_me));
   si_me.sin_family = AF_INET;
   si_me.sin_port = htons(9000);
   si_me.sin_addr.s_addr =htonl(INADDR_ANY);
   
   
   srv=microtcp_socket(AF_INET,SOCK_DGRAM,0);
   
   
   bindsrv=microtcp_bind(srv,(const struct sockaddr *)&si_me,sizeof(si_me));
   
   srv=microtcp_accept(srv,(struct sockaddr *)&si_me,sizeof(si_me));
   
   
   
}
