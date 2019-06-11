#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>
#define CFBMODE 1

void io(char opt);
//Modes ECB,CBC,OFB,CFB,CTR
void encrypt_ECB(FILE *file, FILE *file_dest,int mode);
void encrypt_MODE(FILE *file, FILE *file_dest,char*,int);

void head_handler(FILE *file,FILE *file_dest);
void skip(FILE *file,FILE *file_dest,int n);
void openFiles(FILE **file, FILE **file_dest,char operation,int mode);
void closeFiles(FILE *file, FILE *file_dest);


int main(){
	char opt;
	printf("DES Cipher BMP\n");
	printf("a)Encrypt\nb)Decript\n");
	printf("Select an operation:");
	scanf("%c",&opt);
	fflush(stdin);
	io(opt);
	
	return 0;
}


void io(char opt){	
	FILE *file=NULL,*file_dest=NULL;
	if(opt=='a'){
		//////////////ECB encrypt/////////////////
		printf("ECB encrypt\n");
		openFiles(&file,&file_dest,0,0);
		printf("Encrypting files...\n");
		encrypt_ECB(file,file_dest,DES_ENCRYPT);
		closeFiles(file,file_dest);
		printf("ECB done\n\n");
		//////////////CBC encrypt/////////////////
		printf("CBC encrypt\n");
		openFiles(&file,&file_dest,0,1);
		encrypt_MODE(file,file_dest,"CBC",DES_ENCRYPT);
		closeFiles(file,file_dest);
		printf("CBC done\n\n");
		//////////////OFB encrypt/////////////////
		printf("OFB encrypt\n");
		openFiles(&file,&file_dest,0,2);
		encrypt_MODE(file,file_dest,"OFB",DES_ENCRYPT);
		closeFiles(file,file_dest);
		printf("OFB done\n\n");
		//////////////CFB encrypt/////////////////
		printf("OFB encrypt\n");
		openFiles(&file,&file_dest,0,3);
		encrypt_MODE(file,file_dest,"CFB",DES_ENCRYPT);
		closeFiles(file,file_dest);
		printf("CFB done\n\n");
		
	}else if (opt=='b'){
		//////////////ECB decrypt/////////////////
		printf("ECB encrypt\n");
		openFiles(&file,&file_dest,1,0);
		encrypt_ECB(file,file_dest,DES_DECRYPT);
		closeFiles(file,file_dest);
		printf("ECB done\n\n");
		//////////////CBC decrypt/////////////////
		printf("CBC encrypt\n\n");
		openFiles(&file,&file_dest,1,1);
		encrypt_MODE(file,file_dest,"CBC",DES_DECRYPT);
		closeFiles(file,file_dest);
		printf("CBC done\n\n");
		//////////////OFB encrypt/////////////////
		printf("OFB encrypt\n");
		openFiles(&file,&file_dest,1,2);
		encrypt_MODE(file,file_dest,"OFB",DES_DECRYPT);
		closeFiles(file,file_dest);
		printf("OFB done\n\n");
		//////////////CFB encrypt/////////////////
		printf("CFB encrypt\n");
		openFiles(&file,&file_dest,1,3);
		encrypt_MODE(file,file_dest,"CFB",DES_DECRYPT);
		closeFiles(file,file_dest);
		printf("CFB done\n\n");
		
	}else
		printf("Invalid option");
}


void openFiles(FILE **file, FILE **file_dest,char operation,int mode){
	//Operation: 0 encrypt, 1 decrypt
	//Mode: 0 ECB, 1 CBC, 2 OFB, 3 CFB, 4 CTR
	char *filename=malloc(256*sizeof(char));
	char output_filename[256];
	const char modes[][8]={"ECB.bmp","CBC.bmp","OFB.bmp","CFB.bmp","CTR.bmp"};
	if(operation==0){
		strcpy(filename,"m.bmp");
		sprintf(output_filename,"c_%s",modes[mode]);
	}else{
		sprintf(filename,"c_%s",modes[mode]);
		sprintf(output_filename,"m_%s",modes[mode]);		
	}
	
	printf("Opening %s, and %s\n",filename,output_filename);
	*file = fopen(filename, "r");		
	*file_dest= fopen(output_filename,"w");
	
	if (*file==NULL){
		perror("Can't open file");
		exit(0);
	}
	
	if (*file_dest==NULL){
		perror("Can't create file");
		exit(0);
	}
	
	free(filename);
}


void closeFiles(FILE *file, FILE *file_dest){
		fclose(file);
		fclose(file_dest);
		return;
	}

void encrypt_ECB(FILE *file, FILE *file_dest,int mode){
	head_handler(file,file_dest);
	char plaintext[8];	
	//SSL Data types
	DES_cblock key;
	DES_cblock plain_data; //Input Data Block
	DES_cblock cipher_data;		//Resultant Data Block
	DES_key_schedule schedule;	//Scheduled Key
	//Cleaning Blocks
	bzero(key,sizeof(DES_cblock));
	bzero(plain_data,sizeof(DES_cblock));
	bzero(cipher_data,sizeof(DES_cblock));
	bzero(&schedule,sizeof(DES_key_schedule));
	//Asking key
	printf("ECB. Insert key: \n");
	scanf("%s",key);	
	fflush(stdin);
	//Generate Key
	DES_set_key(&key,&schedule);
	
	int n=0;
	while(feof(file)==0){
		//Reading Data from file
		n=fread(plaintext,sizeof(unsigned char),8,file);
		//Copying Data readed to Data Block
		memcpy(plain_data,plaintext,8*sizeof(unsigned char));
		//Data encrypt
		DES_ecb_encrypt((C_Block *)plain_data,(C_Block *)cipher_data,&schedule,mode);
		fwrite(cipher_data,sizeof(unsigned char),n,file_dest);

	}
		
	return;		
}
	
	
	
void head_handler(FILE *file,FILE *file_dest){
	int offset;	
	skip(file,file_dest,10);	
	fread(&offset,sizeof(int),1,file );
	fwrite(&offset,sizeof(int),1,file_dest);	
	skip(file,file_dest,offset-14);	
	}

void skip(FILE *file,FILE *file_dest,int n){
	unsigned char caracter;
	int i;
	for(i=0;i<n;i++){
			caracter=getc(file);
			fputc(caracter,file_dest);
			}
	
}

void encrypt_MODE(FILE *file, FILE *file_dest,char type[4],int mode){
	head_handler(file,file_dest);
	int numbits=8;
	unsigned char llave[9];
	//SSL Data Types
	unsigned char *input;
	unsigned char *output;
	long length;
	DES_key_schedule schedule;
	DES_cblock ivec={0xE1, 0xE2, 0xE3, 0xD4, 0xD5, 0xC6, 0xC7, 0xA8};
	DES_cblock key;
	//Getting file size
	long actual=ftell(file);	
	fseek(file, 0, SEEK_END); 
	length= ftell(file);
	fseek(file, actual, SEEK_SET); 
	//Allocating Buffer
	input=calloc(length,sizeof(unsigned char));
	output=calloc(length,sizeof(unsigned char));
	fread(input,sizeof(unsigned char),length,file);
	//Cleaning Blocks
	bzero(key,sizeof(DES_cblock));
	//bzero(ivec,sizeof(DES_cblock));
	bzero(&schedule,sizeof(DES_key_schedule));
	//Asking Key
	printf("%s. Insert key: \n",type);
	scanf("%s",llave);	
	DES_string_to_key((const char*)llave, &key);//
	fflush(stdin);
	//Generate Key
	DES_set_key(&key,&schedule);
	//Asking for IV
		//printf("%s. Write IV: \n",type);
		//scanf("%8s",ivec);
		//fflush(stdin);
		//printf("IV: %s\n",ivec);
	//Encrypt
	//Available modes: CBC,OFB,CFB,CTR
	if  	(strcmp(type,"CBC")==0){
		DES_cbc_encrypt(input,output,length,&schedule,(C_Block *)ivec,mode);
	}else if(strcmp(type,"OFB")==0){
		DES_ofb_encrypt(input, output,numbits,length,&schedule,(C_Block *)ivec);
	}else if(strcmp(type,"CFB")==0){
		DES_cfb_encrypt(input, output,CFBMODE,length,&schedule,(C_Block *)ivec,mode);		
	}else if(strcmp(type,"CTR")==0){
		
		printf("Not implemented yet\n");
	}
	//Writing Result
	fwrite(output,length,sizeof(unsigned char),file_dest);
	free(input);
	free(output);
	return;	
}

