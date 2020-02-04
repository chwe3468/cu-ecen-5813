#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


//edited from https://www.geeksforgeeks.org/program-decimal-binary-conversion/
void octal_dec_hex(FILE * fp,int n, int opSize) 
{ 
    n=abs(n);
    int m=pow(2,opSize)-1;
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!%i\n",m);
    if(n<(pow(2,opSize))){
        fprintf(fp, "Octal (abs)\t\t0%o\t0%o\t%o\n", abs(n), m, 0);
        fprintf(fp, "Decimal (abs)\t\t%d\t%d\t%d\n", abs(n), m, 0);
        fprintf(fp, "Hexadecimal (abs)\t\t0x%X\t0x%X\t0x%X\n", abs(n), m, 0);
    }
    else{
        fprintf(fp, "Octal (abs)\t\tERROR\tERROR\tERROR\n");
        fprintf(fp, "Decimal (abs)\t\tERROR\tERROR\tERROR\n");
        fprintf(fp, "Hexadecimal (abs)\t\tERROR\tERROR\tERROR\n");
    }
    return;
} 

void decToBin(FILE * fp,int n, int opSize) 
{ 
    int value=n;
    n=abs(n);
    //edited from https://stackoverflow.com/questions/25829669/how-do-you-multiply-a-character-in-c-like-python
    char str[opSize+1];
    memset(str, '0', sizeof(str)-1);
    str[sizeof(str)-1] = '\0';
    
    printf("%s\n",str);
    
    // array to store binary number 
    char binaryNum[opSize+1];
    memset(binaryNum, '0', sizeof(binaryNum)-1);
    binaryNum[sizeof(binaryNum)-1] = '\0';
  
    // counter for binary array 
    int i = 0; 
    while (n > 0) { 
  
        // storing remainder in binary array
        if (n%2==0){
            binaryNum[i] = '0';
        }
        else{
            binaryNum[i] = '1';
        }
        n = n / 2; 
        i++; 
    } 

    printf("%s\n",binaryNum);
    printf("x%d\n",(int) sizeof(binaryNum));
  
    // printing binary array in reverse order 
    for (int j = 0; j < sizeof(binaryNum)-1; j++){
        str[opSize-j-1]= binaryNum[j]; //2 for 0b
        printf("%s\n",str);
    }
    
    //max
    char max[opSize+1];
    memset(max, '1', sizeof(max)-1);
    max[sizeof(max)-1] = '\0';
    
    //min
    char min[opSize+1];
    memset(min, '0', sizeof(min)-1);
    min[sizeof(min)-1] = '\0';
    
    printf("!!!!!!!!!!%i\n",n);
    printf("!!!!!!!!!!%i\n",opSize);
    if(abs(value)<(pow(2,opSize))){
        fprintf(fp,"Binary (abs) 0b%s\t0b%s\t0b%s\n",str,max,min);
    }
    else{
        fprintf(fp,"Binary (abs)\t\tERROR\tERROR\tERROR\n");   
    }
    octal_dec_hex(fp,value,opSize);
    
    memset(max, '1', sizeof(max)-1);
    max[sizeof(max)-1] = '\0';
    max[0]='0';
    
    min[0]='1';
    
    
    char newstr[opSize+1];
    memset(newstr, '0', sizeof(newstr)-1);
    newstr[sizeof(newstr)-1] = '\0';
    
    for (int i=0;i<opSize;i++){
        if (str[i]=='0'){
            newstr[i]='1';
        }
        else{
            newstr[i]='0';
        }
    }
    
    int lower=-(pow(2,opSize)/2)+1;
    int higher=pow(2,opSize)/2-1;
    if (value>=lower && value<=higher){
        fprintf(fp,"Signed One's Compliment\t0b%s\t0b%s\t0b%s\n",newstr,max,min);
    }
    else{
        fprintf(fp,"Signed One's Compliment\tERROR\t0b%s\t0b%s\n",max,min);
    }
    
    signed_Twos(fp,value,opSize);
    
    for (int i=0;i<opSize;i++){
        newstr[i]=str[i];
    }
    memset(min, '1', sizeof(min)-1);
    lower=-(pow(2,opSize)/2)+1;
    if (value>=lower && value<=higher){
        if(value>=0){
            newstr[0]='0';
        }
        else{
            newstr[0]='1';
        }
        fprintf(fp,"Sign-Magnitude\t\t0b%s\t0b%s\t0b%s\n",newstr,max,min);
    }
    else{
        fprintf(fp,"Sign-Magnitude\t\tERROR\t0b%s\t0b%s\n",max,min);
    }
    return;
}

void signed_Twos(FILE *fp, int n, int opSize){
    int value=n;
    if (value<0){
        n=pow(2,opSize)+n;
    }
    //edited from https://stackoverflow.com/questions/25829669/how-do-you-multiply-a-character-in-c-like-python
    char str[opSize+1];
    memset(str, '0', sizeof(str)-1);
    str[sizeof(str)-1] = '\0';
    
    printf("%s\n",str);
    
    // array to store binary number 
    char binaryNum[opSize+1];
    memset(binaryNum, '0', sizeof(binaryNum)-1);
    binaryNum[sizeof(binaryNum)-1] = '\0';
  
    // counter for binary array 
    int i = 0; 
    while (n > 0) { 
  
        // storing remainder in binary array
        if (n%2==0){
            binaryNum[i] = '0';
        }
        else{
            binaryNum[i] = '1';
        }
        n = n / 2; 
        i++; 
    } 

    printf("%s\n",binaryNum);
    printf("x%d\n",(int) sizeof(binaryNum));
  
    // printing binary array in reverse order 
    for (int j = 0; j < sizeof(binaryNum)-1; j++){
        str[opSize-j-1]= binaryNum[j]; //2 for 0b
        printf("%s\n",str);
    }
    
    //max
    char max[opSize+1];
    memset(max, '1', sizeof(max)-1);
    max[sizeof(max)-1] = '\0';
    max[0] = '0';
    
    //min
    char min[opSize+1];
    memset(min, '0', sizeof(min)-1);
    min[sizeof(min)-1] = '\0';
    min[0] = '1';
    min[sizeof(min)-2] = '1';
    
    int higher=pow(2,opSize)/2-1;
    int lower=-pow(2,opSize)/2;
    if (value>=lower && value<=higher){
        fprintf(fp,"Signed Two's Compliment\t0b%s\t0b%s\t0b%s\n",str,max,min);
    }
    else{
        fprintf(fp,"Signed Two's Compliment\tERROR\t0b%s\t0b%s\n",max,min);
    }
    return;
}

int main(int argc,char *argv[]){
    
    FILE * fp;
    fp = fopen ("ProgramOne.out", "w+");
    int input[11][3]={{-7, 10, 4}, {-7, 9, 4}, {-7, 10, 5}, {-10, 10, 4}, {236, 10, 8}, {0354, 8, 8}, {0xEB, 16, 8}, {-125, 10, 8}, {65400, 10, 8}, {65400, 10, 16}, {-32701, 10, 16}};
    for (int i=0; i<11; i++){
        int value=input[i][0];
        int radix=input[i][1];
        int operand=input[i][2];
        if (operand!=4 && operand!=8 && operand!=16 || radix!=8 && radix!=10 && radix!=16 || value>pow(2,operand)-1){
            
            fprintf(fp,"Binary (abs)\t\tERROR\tERROR\tERROR\n");    
            fprintf(fp, "Octal (abs)\t\tERROR\tERROR\tERROR\n");
            fprintf(fp, "Decimal (abs)\t\tERROR\tERROR\tERROR\n");
            fprintf(fp, "Hexadecimal (abs)\t\tERROR\tERROR\tERROR\n");
        
            fprintf(fp,"Signed One's Compliment\tERROR\tERROR\tERROR\n");
    
        
            fprintf(fp,"Signed Two's Compliment\tERROR\tERROR\tERROR\n");
            fprintf(fp,"Sign-Magnitude\t\tERROR\tERROR\tERROR\n");
            fprintf(fp,"\n\n");
    
        }
        else{
            decToBin(fp,value,operand);
            fprintf(fp,"\n\n");
        }
    }
    return 0;
}