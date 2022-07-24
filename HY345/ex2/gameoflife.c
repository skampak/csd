#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM 100
#define VECLEN 100

/*global board*/
int board[100][100];
int board2[100][100];


int i=0;
int j=0;
int k;
int z;
int c=0;

typedef struct{
	int st1;
	int st2;
	int en1;
	int en2;
}DIM;
DIM dimthr[100];



pthread_t callThd[NUM];
pthread_mutex_t mutexsum;

void copy_board(int board[100][100],int board2[100][100]){
	int i,j;
	for(i=0;i<100;i++){
		for(j=0;j<100;j++){
			board2[i][j]=board[i][j];
		}
	}
	
}

void check(int board[100][100],int st1,int en1,int st2,int en2){
	int dc=0;
	int ac=0;
	
	for(i=st1;i<=en1;i++){
		for(j=st2;j<=st2;j++){
		
		
	
	if (st1==0){
		if(st2==0){
		if (board[st1][st2++]==0) dc++;
		if (board[st1++][st2]==0)	dc++;
		if (board[st1++][st2++]==0)	dc++;
		
		if  (board[st1][st2++]==1)	ac++;
		if  (board[st1++][st2]==1)	ac++;
		if (board[st1++][st2++]==1)	ac++;
		}else if(en2==99){
			if (board[st1][en2--]==0) 	dc++;
			if (board[st1++][en2]==0)	dc++;
			if (board[st1++][en2--]==0) dc++;
			
			if (board[st1][en2--]==1) 	ac++;
			if (board[st1++][en2]==1)	ac++;
			if (board[st1++][en2--]==1)	ac++;
		}else{
			if (board[st1][st2--]==0) 	dc++;
			if (board[st1][st2++]==0)	dc++;
			if(board[st1++][st2]==0)	dc++;
			if (board[st1++][st2--]==0) dc++;
			if (board[st1++][st2++]==0)	dc++;
			
			if (board[st1][st2--]==1)	ac++;
			if (board[st1][st2++]==1)	ac++;
			if (board[st1++][st2]==1)	ac++;
			if (board[st1++][st2--]==1 ) ac++;
			if (board[st1++][st2++]==1)	ac++;	
		}
	}if(en1==99){
		if(st2==0){
			if (board[en1--][st2]==0) 	dc++;
			if (board[en1][st2++]==0)	dc++;
			if(board[en1--][st2++]==0)	dc++;
			
			if (board[en1--][st2]==1 )	ac++;
			if (board[en1][st2++]==1)	ac++;
			if (board[en1--][st2++]==1)	ac++;
		}else if(en2==99){
			if (board[en1--][en2]==0) 	dc++;
			if (board[en1][en2--]==0)	dc++;
			if(board[en1--][en2--]==0)	dc++;

			if (board[en1--][en2]==1) 	ac++;
			if (board[en1][en2--]==1)	ac++;
			if(board[en1--][en2--]==1)	ac++;
		}else{
			if (board[en1][st2--]==0) 	dc++;
			if (board[en1][st2++]==0)	dc++;
			if(board[en1--][st2]==0)	dc++;
			if (board[en1][st2--]==0 )	dc++;
			if (board[en1][st2++]==0)	dc++;

			if (board[en1][st2--]==1) 	ac++;
			if (board[en1][st2++]==1)	ac++;
			if(board[en1--][st2]==1)	ac++;
			if (board[en1][st2--]==1) 	ac++;
			if (board[en1][st2++]==1)	ac++;
		}
	}if (st2==0){
		if (board[st1--][st2]==0) 	dc++;
		if (board[st1++][st2]==0) 	dc++;
		if(board[st1][st2++]==0) 	dc++;
		if (board[st1--][st2++]==0)  	dc++;
		if (board[st1++][st2++]==0) 	dc++;
		
		if (board[st1--][st2]==1)  	ac++;
		if (board[st1++][st2]==1) 	ac++;
		if(board[st1][st2++]==1) 	ac++;
		if (board[st1--][st2++]==1 ) 	ac++;
		if (board[st1++][st2++]==1) 	ac++;
	}if(en2==99){
		if (board[en1--][en2]==0) 	dc++;
		if (board[en1++][en2]==0)	dc++;
		if(board[en1--][en2--]==0)	dc++;
		if (board[en1++][en2--]==0) 	dc++;
		if (board[en1][en2--]==0)	dc++;

		if (board[en1--][en2]==1) 	ac++;
		if (board[en1++][en2]==1)	ac++;
		if(board[en1--][en2--]==1)	ac++;
		if (board[en1++][en2--]==1) 	ac++;
		if (board[en1][en2--]==1)	ac++;
		
	}
		if (board[st1][st2++]==0) 	dc++;
		if (board[st1][st2--]==0) 	dc++;
		if(board[st1--][st2]==0) 	dc++;
		if (board[st1++][st2]==0 ) 	dc++;
		if (board[st1--][st2--]==0) 	dc++;
		if (board[st1--][st2++]==0 ) 	dc++;
		if (board[st1++][st2--]==0) 	dc++;
		if(board[st1++][st2++]==0) 	dc++;
		
		if (board[st1][st2++]==1) 	ac++;
		if (board[st1][st2--]==1) 	ac++;
		if(board[st1--][st2]==1) 	ac++;
		if (board[st1++][st2]==1 ) 	ac++;
		if (board[st1--][st2--]==1) 	ac++;
		if (board[st1--][st2++]==1)  	ac++;
		if (board[st1++][st2--]==1) 	ac++;
		if(board[st1++][st2++]==1) 	ac++;
		
		
		if(board[i][j]==1){
			if(ac<2||ac>3){
		
			board2[i][j]==0;
			}else if(ac==2||ac==3){
				board2[i][j]==1;
		}else{
			if(ac==3){
				board2[i][j]==1;
			}
		
			}
		}	
}

	}
	copy_board(board,board2);
		
	
}


void *update(void *arg){
	/*local board*/
	
	int pos,start1,start2,end1,end2;
	
	pos=(int)arg;
	start1=dimthr[pos].st1;
	start2=dimthr[pos].st2;
	end1=dimthr[pos].en1;
	end2=dimthr[pos].en2;
	pthread_mutex_lock(&mutexsum);
	check(board,start1,end1,start2,end2);
	pthread_mutex_unlock (&mutexsum);
	
	pthread_exit((void*)0);
	
}
	

int main(int argc,char *argv[]){
	copy_board(board2,board);
	int l=0;
	int l1;
	int l2;
	int p=0;
	int c;
	int f=0;
	pthread_attr_t attr;
	void *status;
	FILE *fil;
	fil=fopen("oscillator_beacon.txt","r");
	
	while((c=getc(fil))!=EOF){
		
			
			
			if(c==48||c==49){
				board[l][f]=c-48;
				
			
				if(f==99){
					l++;
					f=0;
				}else{
					f++;
				}	
			
		}
		}
	
		
		
	
		
		
	
	
	
	
  
		
	
	
	
	
	
	for(z=0;z<100;z++){
	while(i<100){
	

		while(j<100){
			dimthr[z].st1=i; 
			dimthr[z].st2=j;
			dimthr[z].en1=i+9;
			dimthr[z].en2=j+9;
			j+=10;
			c++;
			break;
		}
		
		if(c<10){
			
			break;
		}
			i+=10;
		
		
	}
	
}
	
   
		pthread_mutex_init(&mutexsum,NULL);
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
		for(k=0; k<NUM;k++){
			
			pthread_create(&callThd[k],&attr,update,(void *)k);
		}
			pthread_attr_destroy(&attr);
	for(k=0;k<NUM; k++){
		pthread_join(callThd[k],&status);
	}
	
	
	copy_board(board,board2);
	pthread_mutex_destroy(&mutexsum);
	pthread_exit(NULL);
	
	return 1;
}