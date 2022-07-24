#include <stdio.h>
#include <string.h>


enum fsm{init=0,sn,sN,sm,sM};  /*dilwnoume to enumeration pou xreiazete gia thn fsm mas*/   

void cmap_init(char A[256][3]){   /*o pinakas A einai o pinakas pou ulopoiei ta mappings*/
      int i,j;
       j = 97;
        for(i=225; i<250; i++){       
                A[i][0] = j;
                j++;
        }        




        A[226][0] = 118;    
        A[227][0] = 103;
        A[230][0] = 122;
        A[231][0] = 104;
        A[232][0] = 56;
        A[233][0] = 105;
        A[234][0] = 107;
        A[235][0] = 108;
        A[236][0] = 109;
        A[237][0] = 110;
        A[238][0] = 107;
        A[238][1] = 115;
        A[241][0] = 114;
        A[242][0] = 115;
        A[243][0] = 115;
        A[244][0] = 116;
        A[245][0] = 121;
        A[246][0] = 102;
        A[247][0] = 120;
        A[248][0] = 112;
        A[248][1] = 115;
        A[249][0] = 119;
     j=65;
     for(i=193; i<218; i++) {
        A[i][0]=j;
       j++;
}
        A[194][0] = 86;
        A[195][0] = 71;
        A[198][0] = 90;
        A[199][0] = 72;
        A[200][0] = 56;
        A[202][0] = 75;
        A[203][0] = 76;
        A[204][0] = 77;
        A[205][0] = 78;
        A[206][0] = 75;
        A[206][1] = 83;
        A[213][0] = 89;
        A[214][0] = 70;
        A[211][0] = 83;
        A[212][0] = 84;
        A[215][0] = 88;
        A[216][0] = 80;
        A[216][1] = 83;
        A[217][0] = 87;


        A[220][0] = 97;  
        A[220][1] = 39;
        A[221][0] = 101;
        A[221][1] = 39;
        A[222][0] = 104;
        A[222][1] = 39;
        A[223][0] = 105;
        A[223][1] = 39;
        A[252][0] = 111;
        A[252][1] = 39;
        A[254][0] = 119;
        A[254][1] = 39;
        A[253][0] = 121;
        A[253][1] = 39;

        A[182][0] = 39;                 
        A[182][1] = 65;
        A[184][0] = 39;
        A[184][1] = 69;
        A[185][0] = 39;
        A[185][1] = 72;
        A[186][0] = 39;
        A[186][1] = 73;
        A[188][0] = 39;
        A[188][1] = 79;
        A[191][0] = 39;
        A[191][1] = 87;
        A[190][0] = 39;
        A[190][1] = 89;


        A[218][0] = 'I';   /*to 39 einai o tonos kai to 34 ta dialitika*/
        A[218][1] = 39;
        A[218][2] = 39;
        A[219][0] = 'Y';
        A[219][1] = 39;
        A[219][2] = 39;
        A[250][0] = 'i';
        A[250][1] = 39;
        A[250][2] = 39;
        A[251][0] = 'y';
        A[251][1] = 39;
        A[251][2] = 39;
        A[192][0] = 'i';
        A[192][1] = 39;
        A[192][2] = 39;
        A[224][0] = 'y';
        A[224][1] = 39;
        A[224][2] = 34;

}

void printc(char A[256][3],int c) {    /*edw xreiazete h putchar gia na mas voithisei sto print otan metafrazoume*/


	if(A[c][0] != '\0')       
    putchar(A[c][0]);
  if(A[c][1] != '\0')
    putchar(A[c][1]);
  if(A[c][2] != '\0')
    putchar(A[c][2]);
}

enum fsm f_init(char A[256][3], int c){  /*gia thn arxikh katastash*/
  if(c==237) {return sn;}
  else if(c==205){return sN;}
  else if(c==236){return sm;}
  else if(c==204){return sM;}
  else{ printc(A,c);
        return init;
      }
}




enum fsm funn(char A[256][3],int c){  /*an exw dei n*/
  if(c==237) {
    printc(A,237);
    return sn; }
  else if(c==205) {
    printc(A,237);
    return sN; }
  else if(c==236) {
    printc(A,237);
    return sm; }
  else if(c==204) {
    printc(A,237);
    return sM; }
  else if(c==212) {  
    printc(A,100);   
    return init; }
  else if(c==244) {  
    printc(A,100);  
    return init; }
  else {
    printc(A,237);
    printc(A,c);
    return init; }
} 



enum fsm funN(char A[256][3],int c){   /*an exw dei N*/
  if(c==237) {
    printc(A,205); 
    return sn; }
  else if(c==205) {
    printc(A,205);  
    return sN; }
  else if(c==236) {  
    printc(A,205);
    return sm; }
  else if(c==204) {
    printc(A,205);   
    return sM; }
  else if(c==212) { 
    printc(A,68);  
    return init; }
  else if(c==244) { 
    printc(A,68);
    return init; }
  else {
    printc(A,205);
    printc(A,c);
    return init; }
}
  
enum fsm funm(char A[256][3],int c)    /*an exw dei m*/   
{
  if(c==237) {
    printc(A,236);
    return sn; }
  else if(c==205) {
    printc(A,236);
    return sN;    }
  else if(c==236) {
    printc(A,236);
    return sm;    }
   else if(c==204) {
    printc(A,204);
    return sM; }
  else if(c==208) {
    printc(A,98);
    return init; }
  else if(c==240) {
    printc(A,98);
    return init; }
  else {
    printc(A,236);
    printc(A,c);
    return init; }
}



enum fsm funM(char A[256][3],int c){   /*an exw dei M*/
  if(c==237) {
    printc(A,204);
    return sn; }
  else if(c==205) {
    printc(A,204);
    return sN; }
  else if(c==236) {
    printc(A,204);
    return sm; }
  else if(c==204) {
    printc(A,204);
    return sM; }
  else if(c==208) {
    printc(A,66);
    return init; }
  else if(c==240) {
    printc(A,66);
    return init; }
  else {
    printc(A,204);
    printc(A,c);
    return init;
  }
}

/*****BONUS*****/
enum fsm (*actions[])(char A[256][3],int c) = {f_init,funn,funN,funm,funM};   /*array of pointers to a function that returns type enum*/



int main(){ /*h main arxikopoiei ton pinaka A kai ton  gemizei kalwntas thn cmap_init kai h while diabazei thn epomenh katastash ths fsm*/
  int c;
  int i;
  enum fsm state;
  char A[256][3];
    for(i=0;i<256;i++)       
    {
    A[i][0]=i;
    A[i][1]='\0';
    A[i][2]='\0';
    }

 cmap_init(A);
 state=init; 
   while((c=getchar())!=EOF)   /*oso diavazei apo arxeio*/
   {
	
   
    state = (actions[state])(A,c);
  
   }
   return 1;
 }
 
