#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int  isValidAlpha(int alpha);
int gcd(int a, int b);
void encrypt(FILE *file,int alpha,int beta,char *letters);
void decrypt(FILE *file,int alpha,int beta,char *letters);
int findMultInv(int alpha);
int findAddInv(int beta);

int main(){
	char letters_lowercase[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char letters_uppercase[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	char opt;	
	int alpha,beta;
	printf("Affine Cipher\n");
	printf("a)Encrypt\nb)Decrypt\n");
	printf("Insert Operation:");
	scanf("%c",&opt);
	printf("Insert alpha and beta: ");
	scanf("%d %d",&alpha,&beta);
	
	//Alpha Validation	
	if(!isValidAlpha(alpha)){
			printf("Alpha is not valid.Exiting\n");
			return 0;
	}
	
	//File validation
	printf("Alpha is valid\nInsert filename: ");
	char filename[256];
	scanf("%s",filename);
	FILE *file;		
	file = fopen(filename, "r");		
	if(file!=NULL){
		printf("File %s opened\n",filename);
	}else{
		perror("Fail to open file:");
		return 0;
	}
	
	//Start of encrypt-decrypt	
	if(opt=='a'){
		printf("Starting encryption\n");
		encrypt(file,alpha,beta,letters_uppercase);
		
	}else if(opt=='b'){
		printf("Starting decryption\n");
		decrypt(file,alpha,beta,letters_lowercase);
		
	}else{
		printf("Invalid Option\n");
		return 0;
	}	
	
	return 0;		
}

int isValidAlpha(int alpha){	
	return gcd(26,alpha)==1;
	}
	
int gcd(int a, int b){
	int t;
    while (b != 0){
       t = b; 
       b = a % b; 
       a = t; 
    }
    return a;
}


void encrypt(FILE *file,int alpha,int beta,char *letters){
    //Creating file c.txt
    printf("Creating file c_out.txt\n");
	FILE *output_file;
	output_file= fopen("c_out.txt","w");
	if (output_file==NULL){
		perror("Can't create file");
		exit(0);
		}	

	int caracter,aux;
	while((caracter=fgetc(file))!=EOF){
		if(isalpha(caracter)){
			aux=letters[(alpha*(caracter-97)+beta)%26];
			fputc(aux,output_file);
			}
		}	
	printf("Encrypt done...\n");
	return;
}

void decrypt(FILE *file,int alpha,int beta,char *letters){
	printf("Creating file m_out.txt\n");
	FILE *output_file;
	output_file= fopen("m_out.txt","w");
	if (output_file==NULL){
		perror("Can't create file");
		exit(0);
		}
	
	int caracter,aux;
	int alpha_MultInv=findMultInv(alpha);
	int beta_AddInv=findAddInv(beta);
	printf("Alpha Mult Inverse: %d Beta Inv: %d\n",alpha_MultInv,beta_AddInv);
	while((caracter=fgetc(file))!=EOF){
		if(isalpha(caracter)){
			aux=letters[(alpha_MultInv*((caracter-65)+beta_AddInv))%26];
			fputc(aux,output_file);
			}
		}	
	printf("Decrypt done...\n");
		
	
	}
	
int findMultInv(int alpha){
		int i;
		for(i=1;i<26;i++){
			if((alpha*i)%26==1)
				return i;
		}
		return 0;
	}

int findAddInv(int beta){
		return 26-beta;
	
	}
