#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void programTwo(void){
	FILE * fp;
	fp = fopen ("ProgramTwo.out", "w+");
	
	int in[20]={66,114,117,99,101,32,83,97,121,115,32,72,105,33,7,9,50,48,49,57};
	for(int i=0;i<20;i++){
		char *type="";	
		if (in[i]<=32){
			type="Whitespace";
		}
		else if (in[i]>=57 && in[i]<=65 || in[i]>=91 && in[i]<=96 || in[i]>=33 && in[i]<=47){
			type="Special Character";
		}
		else if (in[i]<=48 && in[i]<=57){
			type="Digit";
		}
		else if (in[i]<=97 && in[i]<=122){
			type="Upper Case";
		}
		else if (in[i]<=65 && in[i]<=90){
			type="LowerCase";
		}
		fprintf(fp,"Code: %3d\tType: %15s\tASCII Char: %c\n", in[i], type, in[i]);
	}
	
	fclose(fp);

	return;
}	

int main(int argc,char *argv[]){
	programTwo();
	return 0;
}