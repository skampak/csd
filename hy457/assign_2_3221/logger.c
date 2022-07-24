#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <openssl/md5.h>
#define MAXVAL 1000
#define PATH_MAX 1023

FILE *fopen(const char *path, const char *mode) {
        char titles[] ="UID\tfile_name\tdate\t\ttime\t\ttype\taction_denied\tfingerprint\n";
        unsigned char outpstr[MAXVAL];
	unsigned char ttime[30];
	unsigned char tdate[30];
	int type,acc;
	unsigned char c[MD5_DIGEST_LENGTH];
	MD5_CTX val;
	int i,bytes;
	unsigned char data[1024];
	time_t t=time(NULL);
	struct tm *tm = localtime(&t);
	strftime(ttime, sizeof(ttime), "%X", tm);
	strftime(tdate, sizeof(tdate), "%x", tm);

        printf("In our own fopen, opening %s\n", path);


        FILE *(*original_fopen)(const char*, const char*);
        original_fopen =  dlsym(RTLD_NEXT, "fopen");
	size_t(*original_fwrite)(const void *, size_t, size_t, FILE*);
	original_fwrite = dlsym(RTLD_NEXT, "fwrite");
	type=0;
	FILE *lgfil=(*original_fopen)("logfile.txt","a+");

	FILE *inp = (*original_fopen)(path,"rb");
	if(inp==NULL){
		acc=1;
	}else{
	acc=0;
	MD5_Init (&val);
	while((bytes = fread(data,1,1024,inp))!= 0)
	{
		MD5_Update(&val, data, bytes);
	}
	MD5_Final(c,&val);
	fclose(inp);
	}

	sprintf((char*)outpstr,"%s%d\t%s\t%s\t%s\t%d\t%d\t\t%02x\n",titles,getuid(),path,tdate,ttime,type,acc,c);
	(*original_fwrite)(outpstr,1,strlen((const char *)outpstr),lgfil);
	fclose(lgfil);
        return (*original_fopen)(path,mode);

}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream){

	char titles[] ="\nUID\tfile_name\tdate\t\ttime\t\ttype\taction_denied\tfingerprint\n";
        unsigned char outpstr[MAXVAL];
        unsigned char ttime[30];
        unsigned char tdate[30];
        int type,l,bytes,acc;
	int filedesc;
	char *ssc;
	unsigned char data[1024];
	unsigned char c[MD5_DIGEST_LENGTH];
	char path[PATH_MAX+1];
	char res[PATH_MAX+1];

	char *nres;
	size_t ret;
	MD5_CTX val;
        time_t t=time(NULL);
        struct tm *tm = localtime(&t);
        strftime(ttime, sizeof(ttime), "%X", tm);
        strftime(tdate, sizeof(tdate), "%x", tm);
	filedesc = fileno(stream);
	sprintf(path,"/proc/self/fd/%d",filedesc);
	memset(res, 0, sizeof(res));
	readlink(path, res, sizeof(res)-1);
	l=0;
	nres = res;
	
	nres = basename(nres);
	printf("%s\n%s",nres,res);

        FILE *(*original_fopen)(const char*, const char*);
        original_fopen =  dlsym(RTLD_NEXT, "fopen");
        size_t(*original_fwrite)(const void *, size_t, size_t, FILE*);
        original_fwrite = dlsym(RTLD_NEXT, "fwrite");
        type=1;
        FILE *lgfil=(*original_fopen)("logfile.txt","a+");


	FILE *inp = (*original_fopen)(path,"rb");
	if(inp == NULL){
		acc=1;
	}else{
	acc=0;
        MD5_Init (&val);
        while((bytes = fread(data,1,1024,inp))!= 0)
        {
                MD5_Update(&val, data, bytes);
        }
        MD5_Final(c,&val);
        fclose(inp);
	}

	printf("In our own fwrite\n");
	ret = (*original_fwrite)(ptr,size,nmemb,stream);
	fflush(stream);

        sprintf((char*)outpstr,"%s%d\t%s\t%s\t%s\t%d\t%d\t\t%02x\n",titles,getuid(),nres,tdate,ttime,type,acc,c);
        (*original_fwrite)(outpstr,1,strlen((const char *)outpstr),lgfil);
        fclose(lgfil);
	return ret;
}
