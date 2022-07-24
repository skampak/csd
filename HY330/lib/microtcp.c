
#include "microtcp.h"


#include <stdio.h>
#include <stdlib.h>
#include "microtcp.h"



#include <string.h>
#include <arpa/inet.h>

#include <netinet/in.h>
#include <unistd.h>

#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/types.h>

int crc1,crc2,crc3,x;
socklen_t tmp;

uint32_t clientseq,lol;
microtcp_sock_t
microtcp_socket(int domain, int type, int protocol)
{
	microtcp_sock_t udps;
	udps.sd=socket(domain,type,protocol);
	if (udps.sd == -1) {
		perror(" opening UDP socket " );
		
	}
	udps.state=UNKNOWN;
	udps.init_win_size=8192;
	udps.curr_win_size=8192;
	
	
	return udps;
	
}

int
microtcp_bind(microtcp_sock_t socket, const struct sockaddr *address,
              socklen_t address_len)
{

	int x=bind(socket.sd,(struct sockaddr*)address,address_len);
	if(x==-1){
		perror("udp bind");
		
		
	}
	return x;
	
}

microtcp_sock_t
microtcp_connect(microtcp_sock_t socket, const struct sockaddr *address,
                 socklen_t address_len)
{
	uint16_t flowcontrolwin=0;
	srand(time(NULL));
    tmp=address_len;
	microtcp_header_t *h=(microtcp_header_t *)malloc(sizeof(microtcp_header_t));
	microtcp_header_t *h2=(microtcp_header_t *)malloc(sizeof(microtcp_header_t));
	microtcp_header_t *buff=(microtcp_header_t *)malloc(sizeof(microtcp_header_t));
	h->control=1<<14;
	h->seq_number=htonl(rand()%0xffffffff);
	h->ack_number=0;
	h->checksum=0;


    /*crc1=crc32(&h,sizeof(h));*/
	h->checksum=crc1;
	sendto(socket.sd,(void *)h,sizeof(*h),0,address,address_len);
   printf("sent with seq number");
   printf("%u\n",h->seq_number);
	printf("sent with ack number");
   printf("%u\n",h->ack_number);
	
    	
	x=recvfrom(socket.sd,(void *)buff,sizeof(*buff),0,(struct sockaddr *)address,&tmp);
	
	perror("");
	
	buff->seq_number=ntohl(buff->seq_number);
	buff->window=ntohl(buff->window);
	flowcontrolwin=buff->window;
	printf("recieved with seq number %u\n",buff->seq_number);
	printf("recieved with ack number %u\n",buff->ack_number);
	
	h2->control=(1<<12);
	h2->seq_number=htonl(buff->ack_number);
	h2->ack_number=htonl(buff->seq_number+1);
	h2->checksum=0;

	h2->checksum=crc2;
	sendto(socket.sd,(void*)h2,sizeof(*h2),0,address,address_len);
	 printf("sent with seq number");
   printf("%u\n",h2->seq_number);
	printf("sent with ack number");
   printf("%u\n",h2->ack_number);
	socket.state=ESTABLISHED;
	return socket;
  }


microtcp_sock_t
microtcp_accept(microtcp_sock_t socket, struct sockaddr *address,
                 socklen_t address_len)
				 
{   
    srand(time(NULL));
	microtcp_header_t *buff1=(microtcp_header_t *)malloc(sizeof(microtcp_header_t));
    microtcp_header_t *h3=(microtcp_header_t *)malloc(sizeof(microtcp_header_t));
    microtcp_header_t *buff2=(microtcp_header_t *)malloc(sizeof(microtcp_header_t));
    
	socklen_t tmp;
	tmp=address_len;
	 
	
	    if(recvfrom(socket.sd,(void*)buff1,sizeof(*buff1),0,address,&address_len)==-1){
			printf("recieved");
		}
	
	lol=ntohl(buff1->seq_number);
	buff1->seq_number=ntohl(buff1->seq_number);
    printf("recieved with seq number %u\n",lol);
	printf("recieved with ack number %u\n",buff1->ack_number);

	
	

	h3->seq_number=htonl(rand()%0xffffffff);
	h3->ack_number=ntohl(buff1->seq_number+1);
	h3->control=(1<<12|1<<14);
	h3->window=0;
	
	h3->checksum=0;
/*nt crc3=0;*/
  /*crc3=crc32(&h3,sizeof(h3));*/
	h3->checksum=crc3;
	h3->window=socket.init_win_size; /*antallagh tou window size gia to flow control*/
	sendto(socket.sd,(void*)h3,sizeof(*h3),0,address,address_len);
	printf("sent with seq number");
   printf("%u\n",h3->seq_number);
	printf("sent with ack number");
   printf("%u\n",h3->ack_number);
	
	
	
	    if(recvfrom(socket.sd,(void *)buff2,sizeof(*buff2),0,(struct sockaddr*)address,&tmp)==-1){
			printf("received2");
		}
		
		
	buff2->seq_number=ntohl(buff2->seq_number);
		buff2->ack_number=ntohl(buff2->ack_number);
		buff2->control=ntohs(buff2->control);
		 printf("recieved with seq number %u\n",buff2->seq_number);
	printf("recieved with ack number %u\n",buff2->ack_number);
    if(buff2->seq_number==clientseq+1){
    	socket.state=ESTABLISHED;
	}
		
    
	return socket;
}





