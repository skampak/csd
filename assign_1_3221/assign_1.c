#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/conf.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>
#define BLOCK_SIZE 16


/* function prototypes */
void print_hex(unsigned char *, size_t);
void print_string(unsigned char *, size_t); 
void usage(void);
void check_args(char *, char *, unsigned char *, int,char*);
void keygen(unsigned char *, unsigned char *, unsigned char *,char *);
void encrypt(unsigned char *, int , unsigned char *, unsigned char *,char *, unsigned char *);
int decrypt(unsigned char *, int, unsigned char *, unsigned char *,char *, unsigned char *);
void gen_hmac(unsigned char *, size_t, unsigned  char const*, unsigned char **);
int verify_hmac(unsigned char *, unsigned char *);

/* TODO Declare the rest of your function prototypes here... */



/*
 * Prints the hex value of the input
 * 16 values per line
 */
void
print_hex(unsigned char *data, size_t len)
{
	size_t i;

	if (!data)
		printf("NULL data\n");
	else {
		for (i = 0; i < len; i++) {
			if (!(i % 16) && (i != 0))
				printf("\n");
			printf("%02X ", data[i]);
		}
		printf("\n");
	}
}


/*
 * Prints the input as string
 */
void
print_string(unsigned char *data, size_t len)
{
	size_t i;

	if (!data)
		printf("NULL data\n");
	else {
		for (i = 0; i < len; i++)
			printf("%c", data[i]);
		printf("\n");
	}
}


/*
 * Prints the usage message
 * Describe the usage of the new arguments you introduce
 */
void
usage(void)
{
	printf(
	    "\n"
	    "Usage:\n"
	    "    assign_1 -i in_file -o out_file -p passwd  -b mode" 
	        " [-d | -e | -s | -v]\n"
	    "    assign_1 -h\n"
	);
	printf(
	    "\n"
	    "Options:\n"
	    " -i    path    Path to input file\n"
	    " -o    path    Path to output file\n"
	    " -p    psswd   Password for key generation\n"
	    " -d            Decrypt input and store results to output\n"
   	    " -b    mode     Select aes mode.CBC or ECB\n"

	    " -e            Encrypt input and store results to output\n"
	    " -s            Sign input and store results to output\n"
	    " -v            Verify input and store results to output\n"
	    " -h            This help message\n"
	);
	exit(EXIT_FAILURE);
}


/*
 * Checks the validity of the arguments
 * Check the new arguments you introduce
 */
void
check_args(char *input_file, char *output_file, unsigned char *password,  int op_mode, char *mode)
{
	if (!input_file) {
		printf("Error: No input file!\n");
		usage();
	}

	if (!output_file) {
		printf("Error: No output file!\n");
		usage();
	}

	if (!password) {
		printf("Error: No user key!\n");
		usage();
	}
	if (!mode) {
		printf("Error: No Aes Mode!\n");
		usage();
	}

	if (op_mode == -1) {
		printf("Error: No mode\n");
		usage();
	}
}

void handleErrors(void)
{
	ERR_print_errors_fp(stderr);
	abort();
}


/*
 * Generates a key using a password
 */
void
keygen(unsigned char *password, unsigned char *key, unsigned char *iv,char * mode)
{
  const EVP_CIPHER *ciph;
  const EVP_MD     *digest;
  digest = EVP_get_digestbyname("sha1"); 
  if (strcmp("ECB",mode) == 0)
  {
  	ciph = EVP_aes_128_ecb();
  }else if(strcmp("CBC",mode) == 0)
   {
	ciph = EVP_aes_128_cbc();
   }
 if(ciph == NULL){
    fprintf(stderr, "no cipher");
  }

 if(digest == NULL){
   fprintf(stderr, "no digest");
 }

 if(!EVP_BytesToKey(ciph, digest, NULL, (unsigned char *) password, strlen((const char *)password), 1, key, iv)){
   fprintf(stderr, "evp bytes to key fail");
 }
}


/*
 * Encrypts the data
 */
void
encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
    unsigned char *iv,char *mode, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();
    if(strcmp("ECB",mode) == 0){
    	if( 1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, iv))
      		handleErrors();
    }else if(strcmp("CBC",mode) == 0){
	if( 1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
                handleErrors();
    }else{
	printf("no mode");
    }
    if( 1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
      {
      handleErrors();
      ciphertext_len = len;
      }
    if(1!= EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
      ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

	/* TODO Task B */

}


/*
 * Decrypts the data and returns the plaintext size
 */
int
decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
    unsigned char *iv,char *mode, unsigned char *plaintext)
{
	EVP_CIPHER_CTX *ctx;
	int plaintext_len;
	int len;
	

	if(!(ctx =  EVP_CIPHER_CTX_new())) handleErrors();
	if(strcmp("ECB",mode) == 0){
       		 if( 1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, iv))
                handleErrors();
   	 }else if(strcmp("CBC",mode) == 0){
       		 if( 1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
                handleErrors();
   	 }else{
        	printf("no mode");
   	 }



	if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) handleErrors();
	 	{ 
			plaintext_len = len;
			
	 	 }
	
	if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
	{
		plaintext_len += len;

	}
	EVP_CIPHER_CTX_free(ctx);

	
	return plaintext_len;
}


/*
 * Generates a HMAC
 */
void
gen_hmac(unsigned char *data, size_t data_len, unsigned char const* key,unsigned char **hmac)
{
	EVP_MD_CTX* mdctx = NULL;
	const EVP_MD* md = NULL;
	EVP_PKEY *pkey = NULL;

	unsigned char md_value[EVP_MAX_MD_SIZE];   
	size_t md_len = 20;
	unsigned char hkey[EVP_MAX_MD_SIZE];
	int size = EVP_MD_size(md);

	*hmac=md_value;

	OpenSSL_add_all_digests();

if(!(mdctx = EVP_MD_CTX_create()))
    handleErrors();
if(!(md = EVP_get_digestbyname("SHA1")))
    handleErrors();

if(!(pkey = EVP_PKEY_new_mac_key(EVP_PKEY_HMAC, NULL, hkey, size)))
    handleErrors();

if(1 != EVP_DigestSignInit(mdctx, NULL, md, NULL, pkey))
    handleErrors();

/* Call update with the message */
if(1 != EVP_DigestSignUpdate(mdctx, data, data_len))
    handleErrors();

if(1 != EVP_DigestSignFinal(mdctx, *hmac, &md_len))
    handleErrors();


printf("\nHMAC In hex");
print_hex(*hmac,20);
}


/*
 * Verifies a HMAC
 */
int
verify_hmac(unsigned char *hmac1, unsigned char *hmac2)
{
	int verify;

	verify = -1;
	

	unsigned char vkey[EVP_MAX_MD_SIZE];
        const EVP_MD* md = EVP_get_digestbyname("SHA1"); 
         int size = EVP_MD_size(md);
         RAND_bytes(vkey, size);
         EVP_PKEY *nkey =  EVP_PKEY_new_mac_key(EVP_PKEY_HMAC, NULL, vkey, size);
         OPENSSL_cleanse(vkey, sizeof(vkey));
        size_t* hmacl = malloc(sizeof(hmac2));
        size_t vlen = 20;
	print_hex(hmac2,20); 	//print the hmac from the sign function
        EVP_MD_CTX* ctx = NULL;
        do
        {
        ctx = EVP_MD_CTX_create();
        const EVP_MD* md = EVP_get_digestbyname("SHA1");
        
        EVP_DigestInit_ex(ctx, md, NULL);
       
        EVP_DigestSignInit(ctx, NULL, md, NULL, nkey);
      
        EVP_DigestSignUpdate(ctx, hmac2, sizeof(hmacl));
        unsigned char buff[EVP_MAX_MD_SIZE];
	size_t nsize = sizeof(buff);
        EVP_DigestSignFinal(ctx, buff, &nsize);
	const size_t m = (vlen < nsize ? vlen : nsize);
	verify = !!CRYPTO_memcmp(hmac2,buff,m);

	OPENSSL_cleanse(buff,sizeof(buff));
	}while(0);

	if(ctx) {
        EVP_MD_CTX_destroy(ctx);
        ctx = NULL;
        }

	return !!verify;
}



/* TODO Develop the rest of your functions here... */



/*
 * Encrypts the input file and stores the ciphertext to the output file
 *
 * Decrypts the input file and stores the plaintext to the output file
 *
 * Signs the input file and stores the ciphertext concatenated with 
 * the HMAC to the output file
 *
 * Verifies the input file and stores the plaintext to the output file
 */
int
main(int argc, char **argv)
{
	int opt;			/* used for command line arguments */
	int op_mode;			/* operation mode */
	char *input_file;		/* path to the input file */
	char *output_file;		/* path to the output file */
	unsigned char *password;	/* the user defined password */
	char *mode;
	int filsize;
	FILE *inp, *outp;
	unsigned char *ind;
	unsigned char *outd;
	/* Init arguments */
	unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];
	input_file = NULL;
	output_file = NULL;
	password = NULL;
	op_mode = -1;
	mode=NULL;


	/*
	 * Get arguments
	 */
	while ((opt = getopt(argc, argv, "i:m:o:p:b:desvh:")) != -1) {
		switch (opt) {

		case 'i':
			input_file = strdup(optarg);
			break;
		case 'o':
			output_file = strdup(optarg);
			break;
		case 'p':
			password = (unsigned char *)strdup(optarg);
			break;
		case 'b':
			mode = strdup(optarg);
			break;
		case 'd':
			/* if op_mode == 1 the tool decrypts */
			op_mode = 1;
			break;
		case 'e':
			/* if op_mode == 1 the tool encrypts */
			op_mode = 0;
			break;
		case 's':
			/* if op_mode == 1 the tool signs */
			op_mode = 2;
			break;
		case 'v':
			/* if op_mode == 1 the tool verifies */
			op_mode = 3;
			break;
		case 'h':
		default:
			usage();
		}
	}


	/* check arguments */
	check_args(input_file, output_file, password, op_mode,mode);



	/* TODO Develop the logic of your tool here... */

	


	/* Initialize the library */
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	OPENSSL_config(NULL);

	/* Keygen from password */
	keygen(password, key, iv, mode);
	print_hex(key, strlen((const char*)key));

	/* Operate on the data according to the mode */
	printf("opmode is: %d \n", op_mode);
	inp = fopen(input_file, "rb");
	outp = fopen(output_file, "wb+");
	fseek(inp, 0L, SEEK_END);
	filsize = ftell(inp);
	fseek(inp, 0L, SEEK_SET); 
	/* encrypt */
	if(op_mode == 0){
	ind = malloc(filsize);
	outd = malloc(((filsize/BLOCK_SIZE)+1)*BLOCK_SIZE);
	if(!(fread(ind,sizeof(char),filsize, inp))){
		printf("error in fread/n");
		return 1;
	}
	printf("indata: %s \n",ind);
	encrypt(ind , filsize, key, iv, mode,  outd);
	print_hex(outd,strlen((const char*)outd));
	fwrite(outd,sizeof(char),((filsize/BLOCK_SIZE)+1)*BLOCK_SIZE,outp);
	}
	/* decrypt */
	if(op_mode == 1){
	ind = malloc(filsize);
        outd = malloc(filsize);
        if(!(fread(ind,sizeof(char),filsize, inp))){
		printf("error in fread");
                return 1;
	}
        printf("indata: %s \n",ind);
        filsize = decrypt(ind , filsize, key, iv, mode,  outd);
	outd[filsize] = '\0';
        print_hex(outd,strlen((const char*)outd));
        fwrite(outd,sizeof(char),filsize, outp);
	}


	/* sign */
	if(op_mode == 2)
	{
		ind = malloc(filsize);
		outd = malloc(((filsize/BLOCK_SIZE)+1)*BLOCK_SIZE+20);
		if(!(fread(ind,sizeof(char),filsize, inp))){
				printf("error in fread\n");
				return 1;
		}
			//fwrite(indata,sizeof(char),filsize,outp);
			printf("indata: %s \n",ind);
			printf("fsize:  %d \n",filsize);
			gen_hmac(ind , 20, key, &outd);
			printf("fsize:  %d \n",((filsize/BLOCK_SIZE)+1)*BLOCK_SIZE+20);
			print_hex(outd,20);
			strcat(ind,outd); //concat the two strings into one
			
			printf("outdata print %s\n", outd);
			fwrite(ind,sizeof(char),((filsize/BLOCK_SIZE)+1)*BLOCK_SIZE+20,outp);
			print_hex(ind,20);
	}
	/* verify */	
	 if(op_mode == 3)
        {
		int  tsek,ff;
		
                ind = malloc(filsize);
 	        
      		
		fseek(inp, 0, SEEK_END);
   		ff = ftell(inp);
		printf("ftell says: %d\n",ff);
   		fseek(inp, (ff - 20), SEEK_SET); //read the last 20 bytes
		//fseek(inp, -16, SEEK_END);
		
                if(!(fread(ind,sizeof(char), 20, inp))){

                                return 1;
            }
			print_hex(ind,20);
                        printf("indata: %s \n",ind);
                        printf("filesize: %d \n",filsize);
                        tsek = verify_hmac(key,ind);
			printf("verify is  %d\n",tsek);
                        printf("filsize: %d \n",((filsize/BLOCK_SIZE)+1)*BLOCK_SIZE);
                        

        }

	/* Clean up */
	free(input_file);
	free(output_file);
	free(password);


	/* END */
	return 0;
}

