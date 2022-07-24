
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char **cmd_split(char *cmd){
	int buf_size=100,p=0;
	char *tok;
	char **tokens;
	tokens=malloc(buf_size * sizeof(char*));
	tok=strtok(cmd," ");
	while(tok != NULL){
		
		printf("%s\n",tok);
		tokens[p]=tok;
		p++;
		tok=strtok(NULL," ");
		

	}
	tokens[p]=NULL;
	return tokens;
}
char **eq_split(char *cmd){
	
	int buf_size=100,p=0;
	char *tok;
	char **tokens;
	tokens=malloc(buf_size * sizeof(char*));
	tok=strtok(cmd,"=");
	
		while(tok != NULL){
		printf("%s\n",tok);
		tokens[p]=tok;
		p++;
		tok=strtok(NULL," ");
		

	}
	tokens[p]=NULL;
	return tokens;
}
typedef struct node{
	char *vr;
	char *cp;
	struct node *next;
}variable;

void insert(variable **head, char *val,char* pop) {
    variable * new_node;
    new_node = malloc(sizeof(variable));

    new_node->vr = val;
	new_node->cp=pop;
    new_node->next = *head;
	printf("%s\n",new_node->vr);
	printf("%s\n",new_node->cp);
    *head = new_node;
}
void delete(variable ** head, char * n) {
    
   
    variable * current = *head;
    variable * temp_node = NULL;

    /*if (n == 0) {
        return pop(head);
    }*/

    while(current!=NULL) {
        if(current->cp=n){
			
     temp_node = current->next;
     current->next = temp_node->next;
		break;
		}
	}
    free(temp_node);

  

}

void execute(variable **head,char *p){
			variable *cur;
			char **p2;
			cur=malloc(sizeof(variable));
			cur=*head;
			
			printf("%s",p);
			
			while(cur!=NULL){
				if(cur->cp=p){
				p2=cmd_split(cur->vr);
				execvp(p2[0],p2);
				break;
				}
				cur=cur->next;
			}
}



char *read_command(){
	char *cmd=NULL;
	
	ssize_t buf=0;
	getline(&cmd,&buf,stdin);
	return cmd;
}


char **c_split(char *cmd){
	int buf_size=100,p=0;
	char *tok;
	char **tokens;
	tokens=malloc(buf_size * sizeof(char*));
	tok=strtok(cmd,"\"");
	while(tok != NULL){
		printf("%s\n",tok);
		tokens[p]=tok;
		p++;
		tok=strtok(NULL," ");
		

	}
	tokens[p]=NULL;
	return tokens;
}
char **pipe_split(char *cmd){
	int buf_size=100,p=0;
	char *tok;
	char **tokens;
	tokens=malloc(buf_size * sizeof(char*));
	tok=strtok(cmd,"|" );
	while(tok != NULL){
		printf("%s\n",tok);
		tokens[p]=tok;
		p++;
		tok=strtok(NULL," ");
		

	}
	tokens[p]=NULL;
	return tokens;
}
void strip(char *s) {
    char *p2 = s;
    while(*s != '\0') {
    	if(*s != '\t' && *s != '\n') {
    		*p2++ = *s++;
    	} else {
    		++s;
    	}
    }
    *p2 = '\0';
}
void strip2(char *s) {
    char *p2 = s;
    while(*s != '\0') {
    	if(*s != '&') {
    		*p2++ = *s++;
    	} else {
    		++s;
    	}
    }
    *p2 = '\0';
}

int main(int argc,char *argv[]){
	
	char *name,*command,*temp,*fin,*tst,*tst3;
	char **params,**newcommand,**cmd1,**cmd2,**tst2;
	variable **head2;
	
	int status,pipefd[2],pid;
	char dir[1024];
	
	variable *head=NULL;
	
	
	
	
	head=malloc(sizeof(variable));
	head->vr="start";
	head->next=NULL;
	
	*head2=head;
	params=(char **)malloc(3*sizeof(char **));
	
	while(1){
	name=getlogin();

		if(getcwd(dir,sizeof(dir))!=NULL){
		printf("%s@cs345sh/%s/$ ",name,dir);
		}
	command=read_command();
	
	params=cmd_split(command);
	
	tst=strstr(params[0],"\n");
	tst3=strstr(params[0],"&");
	
	printf("%s",params[0]);
	if(strcmp(params[0],"exit\n")==0){
		printf("Exiting shell now\n");
		break;
	}else if(strcmp(params[0],"set")==0 || strcmp(params[0],"unset")==0){
			newcommand=eq_split(params[1]);
			strip(newcommand[1]);
			tst2=c_split(newcommand[1]);
			
		if(strcmp(params[0],"set")==0){
			
			
			insert(head2,tst2[0],newcommand[0]);
			
			
			/*execvp(tst2[0],tst2);*/
			
		}else{
			delete(head2,tst2[0]);
		}
	}else if(strcmp(params[0],"cd")==0){
			
			if(params[1]==NULL){
				printf("error no params");
			}else{
				strip(params[1]);
				temp=strcat(dir,"/");
				
				printf("%d\n",strlen(params[1]));
				fin=strcat(temp,params[1]);
				
				if(chdir(fin)!=0){
					perror("ok");
				}	
			}
		
	
	}else if(tst3!=NULL){
			strip2(params[0]);
			execute(head2,params[0]);
			
	
			
	}else if(tst==NULL){
			    if(strcmp(params[1],"|")==0){
					pid=fork();
					if(pid==0) {
						cmd1=pipe_split(params[0]);
						cmd2=pipe_split(params[2]);
						printf("PIPE");
						pipe(pipefd);
						dup2(pipefd[1],STDOUT_FILENO);
						execvp(cmd2[0],cmd2);
						close(pipefd[1]);
				}else{	
						dup2(pipefd[0],STDIN_FILENO);
						dup2(pipefd[1],STDOUT_FILENO);
						execvp(cmd1[0],cmd1);
						close(pipefd[1]);
						waitpid(-1,&status,0);
				}
				
			}
		
		}else if(fork()!=0){
			waitpid(-1,&status,0);
		}else{
			strip(params[0]);
			execvp(params[0],params);
		}	
	
	}
	
 return 0;
}
