size_t ms_length(const char *pcstr);

/*Copies the string pointed to by src to dest*/
char *ms_copy(char *npcstr, const char *pcstr);

/*Copies up to n characters from the string pointed to by pcstr to npcstr*/
char *ms_ncopy(char *npcstr, const char *pcstr, size_t n);

/*Appends the string pointed to by pcstr to the end of the string 
 pointed to by npcstr*/
char *ms_concat(char *npcstr, const char *pcstr);

/*Appends the string pointed to by pcstr to the end of the string 
  pointed to by npcstr up to n characters long*/
char *ms_nconcat(char *npcstr, const char *pcstr, size_t n);

/*Compares the string pointed to by pcstr to the string pointed to by npcstr*/
int ms_compare(const char *pcstr, const char *npcstr);

/*Compares at most the first n bytes of pcstr and npcstr*/
int ms_ncompare(const char *pcstr, const char *npcstr, size_t n);

/*Finds the first occurrence of the entire string pcstr 
 (not including the terminating null character) which 
  appears in the string npcstr */
char *ms_search(char *npcstr, const char *pcstr);

