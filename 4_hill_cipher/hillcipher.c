#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "matrix.h"

void io(char filename[255],char output_filename[255],char opt);
void encrypt(FILE *file, FILE *file_dest);
void decrypt(FILE *file, FILE *file_dest);
void head_handler(FILE *file,FILE *file_dest);
void skip(FILE *file,FILE *file_dest,int n);
void hillCipher(int **matix_m,int **key);

void xor(int **matrix_m,int **block);

void encrypt_CBC(FILE *file, FILE *file_dest);
void encrypt_CFB(FILE *file, FILE *file_dest);
void encrypt_OFB(FILE *file, FILE *file_dest);

void decrypt_CFB(FILE *file, FILE *file_dest);
void decrypt_CBC(FILE *file, FILE *file_dest);
void decrypt_OFB(FILE *file, FILE *file_dest);

char input[255];

int main(int argc, char *argv[]){
	char opt;
	printf("Hill Cipher BMP\n");
	printf("a)Encrypt\nb)Decript\n");
	printf("Select an operation:");
	scanf("%c",&opt);
	strcpy(input,argv[1]);
	
	char filename[256],output_filename[256];			
	
	io(filename,output_filename,opt);	
	return 0;
	
	}

void io(char filename[256],char output_filename[256],char opt){
	FILE *file,*file_dest;

	
	if(opt=='a'){
		
		///////////////////////ECB////////////////////////////
		sprintf(filename,"%s",input);
		sprintf(output_filename,"%s","c_ecb.bmp");
		file = fopen(filename, "r");		
		file_dest= fopen(output_filename,"w");
	
		if (file==NULL){
			perror("Can't open file");
			exit(0);
			}
		
		if (file_dest==NULL){
			perror("Can't create file");
			exit(0);
			}	
		
		encrypt(file,file_dest);
		//Close Streams
		fclose(file);
		fclose(file_dest);
		
		//////////////////CBC////////////////////////////////
		sprintf(filename,"%s",input);
		sprintf(output_filename,"%s","c_cbc.bmp");
		file = fopen(filename, "r");		
		file_dest= fopen(output_filename,"w");
	
		if (file==NULL){
			perror("Can't open file");
			exit(0);
			}
		
		if (file_dest==NULL){
			perror("Can't create file");
			exit(0);
			}	
		
		encrypt_CBC(file,file_dest);
		//Close Streams
		fclose(file);
		fclose(file_dest);
		
		////////////CFB/////////////////
		sprintf(filename,"%s",input);
		sprintf(output_filename,"%s","c_cfb.bmp");
		file = fopen(filename, "r");		
		file_dest= fopen(output_filename,"w");
	
		if (file==NULL){
			perror("Can't open file");
			exit(0);
			}
		
		if (file_dest==NULL){
			perror("Can't create file");
			exit(0);
			}	
		
		encrypt_CFB(file,file_dest);
		//Close Streams
		fclose(file);
		fclose(file_dest);
		
		////////////OFB/////////////////
		sprintf(filename,"%s",input);
		sprintf(output_filename,"%s","c_ofb.bmp");
		file = fopen(filename, "r");		
		file_dest= fopen(output_filename,"w");
	
		if (file==NULL){
			perror("Can't open file");
			exit(0);
			}
		
		if (file_dest==NULL){
			perror("Can't create file");
			exit(0);
			}	
		
		encrypt_OFB(file,file_dest);
		//Close Streams
		fclose(file);
		fclose(file_dest);
		
		
		
		
		
		}
	else if (opt=='b'){
		///////////////////////ECB/////////////
		sprintf(filename,"%s","c_ecb.bmp");
		sprintf(output_filename,"%s","m_ecb.bmp");
		file = fopen(filename, "r");		
		file_dest= fopen(output_filename,"w");
	
		if (file==NULL){
			perror("Can't open file");
			exit(0);
			}
		
		if (file_dest==NULL){
			perror("Can't create file");
			exit(0);
			}	
			
		decrypt(file,file_dest);
		//Close Streams
		fclose(file);
		fclose(file_dest);
		
		//////////////////CBC////////////////////////////////
		sprintf(filename,"%s","c_cbc.bmp");
		sprintf(output_filename,"%s","m_cbc.bmp");
		file = fopen(filename, "r");		
		file_dest= fopen(output_filename,"w");
	
		if (file==NULL){
			perror("Can't open file");
			exit(0);
			}
		
		if (file_dest==NULL){
			perror("Can't create file");
			exit(0);
			}	
			
		decrypt_CBC(file,file_dest);
		//Close Streams
		fclose(file);
		fclose(file_dest);
		
		//////////////////CFB////////////////////////////////
		sprintf(filename,"%s","c_cfb.bmp");
		sprintf(output_filename,"%s","m_cfb.bmp");
		file = fopen(filename, "r");		
		file_dest= fopen(output_filename,"w");
	
		if (file==NULL){
			perror("Can't open file");
			exit(0);
			}
		
		if (file_dest==NULL){
			perror("Can't create file");
			exit(0);
			}	
			
		decrypt_CFB(file,file_dest);
		//Close Streams
		fclose(file);
		fclose(file_dest);
		
		//////////////////OFB////////////////////////////////
		sprintf(filename,"%s","c_ofb.bmp");
		sprintf(output_filename,"%s","o_cfb.bmp");
		file = fopen(filename, "r");		
		file_dest= fopen(output_filename,"w");
	
		if (file==NULL){
			perror("Can't open file");
			exit(0);
			}
		
		if (file_dest==NULL){
			perror("Can't create file");
			exit(0);
			}	
			
		decrypt_OFB(file,file_dest);
		//Close Streams
		fclose(file);
		fclose(file_dest);
		
		
		
		}
	else
		printf("Invalid option");
		
		


	
	
}

void encrypt(FILE *file, FILE *file_dest){
	head_handler(file,file_dest);			
	
	int caracter=0;
	int **matrix_m;
	int **key;
	creador_matrices_dinamicas(&matrix_m,1,3);
	creador_matrices_dinamicas(&key,3,3);
	
	//Matrix
	key[0][0]=1;
	key[0][1]=2; 
	key[0][2]=3;
	key[1][0]=4;
	key[1][1]=5; 
	key[1][2]=6; 
	key[2][0]=11; 
	key[2][1]=9; 
	key[2][2]=8; 
	
	while((caracter=fgetc(file))!=EOF){
			matrix_m[0][0]=caracter;
			matrix_m[0][1]=fgetc(file);
			matrix_m[0][2]=fgetc(file);
			
			hillCipher(matrix_m,key);
			
			fputc(matrix_m[0][0],file_dest);
			fputc(matrix_m[0][1],file_dest);
			fputc(matrix_m[0][2],file_dest);
		}
	
	}
	
void hillCipher(int **matrix_m,int**key){
	
	int **result;
	creador_matrices_dinamicas(&result,1,3);
	
	multiplicacion_matrices(matrix_m,key,result,1,3,3);
	matrix_m[0][0]=result[0][0];
	matrix_m[0][1]=result[0][1];
	matrix_m[0][2]=result[0][2];
	
	}

void decrypt(FILE *file, FILE *file_dest){
	head_handler(file,file_dest);	
	int caracter=0;
	int **matrix_m;
	int **inv_key;
	creador_matrices_dinamicas(&matrix_m,1,3);
	creador_matrices_dinamicas(&inv_key,3,3);
	
	//Matrix
	inv_key[0][0]=90;
	inv_key[0][1]=167; 
	inv_key[0][2]=1;
	inv_key[1][0]=74;
	inv_key[1][1]=179; 
	inv_key[1][2]=254; 
	inv_key[2][0]=177; 
	inv_key[2][1]=81; 
	inv_key[2][2]=1; 
	
	while((caracter=fgetc(file))!=EOF){
			matrix_m[0][0]=(unsigned char)caracter;
			matrix_m[0][1]=(unsigned char)fgetc(file);
			matrix_m[0][2]=(unsigned char)fgetc(file);
			
			hillCipher(matrix_m,inv_key);
			
			fputc(matrix_m[0][0],file_dest);
			fputc(matrix_m[0][1],file_dest);
			fputc(matrix_m[0][2],file_dest);
		}	
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



void encrypt_CBC(FILE *file, FILE *file_dest){
	head_handler(file,file_dest);			
	
	int caracter=0;
	int **matrix_m;
	int **key;
	int **block;
	creador_matrices_dinamicas(&block,1,3);
	creador_matrices_dinamicas(&matrix_m,1,3);
	creador_matrices_dinamicas(&key,3,3);
	
	//Matrix
	key[0][0]=1;
	key[0][1]=2; 
	key[0][2]=3;
	key[1][0]=4;
	key[1][1]=5; 
	key[1][2]=6; 
	key[2][0]=11; 
	key[2][1]=9; 
	key[2][2]=8; 
	
	printf("Insert initial vector: \n");
	scanf("%d %d %d",&block[0][0],&block[0][1],&block[0][2]);
	printf("Initial vector: %d %d %d \n",block[0][0],block[0][1],block[0][2]);
	

	
	while((caracter=fgetc(file))!=EOF){
			//Read from file
			matrix_m[0][0]=caracter;
			matrix_m[0][1]=fgetc(file);
			matrix_m[0][2]=fgetc(file);
			//CBC
			xor(matrix_m,block);
			hillCipher(matrix_m,key);
			//Write
			fputc(matrix_m[0][0],file_dest);
			fputc(matrix_m[0][1],file_dest);
			fputc(matrix_m[0][2],file_dest);
			//Exchange
			block[0][0]=matrix_m[0][0];
			block[0][1]=matrix_m[0][1];
			block[0][2]=matrix_m[0][2];			
			
		}
	
	}
	
	

void encrypt_CFB(FILE *file, FILE *file_dest){
	head_handler(file,file_dest);			
	
	int caracter=0;
	int **matrix_m;
	int **key;
	int **block;
	creador_matrices_dinamicas(&block,1,3);
	creador_matrices_dinamicas(&matrix_m,1,3);
	creador_matrices_dinamicas(&key,3,3);
	
	//Matrix
	key[0][0]=1;
	key[0][1]=2; 
	key[0][2]=3;
	key[1][0]=4;
	key[1][1]=5; 
	key[1][2]=6; 
	key[2][0]=11; 
	key[2][1]=9; 
	key[2][2]=8; 
	
	printf("Insert initial vector: \n");
	scanf("%d %d %d",&block[0][0],&block[0][1],&block[0][2]);
	printf("Initial vector: %d %d %d \n",block[0][0],block[0][1],block[0][2]);
	

	
	while((caracter=fgetc(file))!=EOF){
			//Read from file
			matrix_m[0][0]=caracter;
			matrix_m[0][1]=fgetc(file);
			matrix_m[0][2]=fgetc(file);
			//CFC
			hillCipher(block,key);			
			xor(matrix_m,block);
			//Write
			fputc(matrix_m[0][0],file_dest);
			fputc(matrix_m[0][1],file_dest);
			fputc(matrix_m[0][2],file_dest);
			//Exchange
			block[0][0]=matrix_m[0][0];
			block[0][1]=matrix_m[0][1];
			block[0][2]=matrix_m[0][2];			
			
		}
	
	}	
	
	
void encrypt_OFB(FILE *file, FILE *file_dest){
	head_handler(file,file_dest);			
	
	int caracter=0;
	int **matrix_m;
	int **key;
	int **block;
	int **aux;
	creador_matrices_dinamicas(&block,1,3);
	creador_matrices_dinamicas(&matrix_m,1,3);
	creador_matrices_dinamicas(&key,3,3);
	creador_matrices_dinamicas(&aux,1,3);
	
	//Matrix
	key[0][0]=1;
	key[0][1]=2; 
	key[0][2]=3;
	key[1][0]=4;
	key[1][1]=5; 
	key[1][2]=6; 
	key[2][0]=11; 
	key[2][1]=9; 
	key[2][2]=8; 
	
	printf("Insert initial vector: \n");
	scanf("%d %d %d",&block[0][0],&block[0][1],&block[0][2]);
	printf("Initial vector: %d %d %d \n",block[0][0],block[0][1],block[0][2]);
	

	
	while((caracter=fgetc(file))!=EOF){
			//Read from file
			matrix_m[0][0]=caracter;
			matrix_m[0][1]=fgetc(file);
			matrix_m[0][2]=fgetc(file);
			//CFC
			hillCipher(block,key);
			aux[0][0]=block[0][0];
			aux[0][1]=block[0][1];
			aux[0][2]=block[0][2];
						
			xor(matrix_m,block);
			//Write
			fputc(matrix_m[0][0],file_dest);
			fputc(matrix_m[0][1],file_dest);
			fputc(matrix_m[0][2],file_dest);
			//Exchange
			block[0][0]=aux[0][0];
			block[0][1]=aux[0][1];
			block[0][2]=aux[0][2];			
			
		}
	
	}
	
	
void decrypt_CFB(FILE *file, FILE *file_dest){
	head_handler(file,file_dest);	
	int caracter=0;
	int **matrix_m;
	int **inv_key;
	int **block;
	int **aux;
	creador_matrices_dinamicas(&block,1,3);
	creador_matrices_dinamicas(&matrix_m,1,3);
	creador_matrices_dinamicas(&inv_key,3,3);
	creador_matrices_dinamicas(&aux,1,3);
	
	//Matrix
	//inv_key[0][0]=90;
	//inv_key[0][1]=167; 
	//inv_key[0][2]=1;
	//inv_key[1][0]=74;
	//inv_key[1][1]=179; 
	//inv_key[1][2]=254; 
	//inv_key[2][0]=177; 
	//inv_key[2][1]=81; 
	//inv_key[2][2]=1;
	
	
	inv_key[0][0]=1;
	inv_key[0][1]=2; 
	inv_key[0][2]=3;
	inv_key[1][0]=4;
	inv_key[1][1]=5; 
	inv_key[1][2]=6; 
	inv_key[2][0]=11; 
	inv_key[2][1]=9; 
	inv_key[2][2]=8; 
	
	//Initial vector
	printf("Insert initial vector: \n");
	scanf("%d %d %d",&block[0][0],&block[0][1],&block[0][2]);
	printf("Initial vector: %d %d %d \n",block[0][0],block[0][1],block[0][2]);
	
	while((caracter=fgetc(file))!=EOF){
		
			matrix_m[0][0]=(unsigned char)caracter;
			matrix_m[0][1]=(unsigned char)fgetc(file);
			matrix_m[0][2]=(unsigned char)fgetc(file);
			
			aux[0][0]=matrix_m[0][0];
			aux[0][1]=matrix_m[0][1];
			aux[0][2]=matrix_m[0][2];
			
			//Decrypt
			hillCipher(block,inv_key);
			//XOR
			xor(matrix_m,block);
						
			fputc(matrix_m[0][0],file_dest);
			fputc(matrix_m[0][1],file_dest);
			fputc(matrix_m[0][2],file_dest);
			//Aux
			block[0][0]=aux[0][0];
			block[0][1]=aux[0][1];
			block[0][2]=aux[0][2];	
			
					
			
		}	
	}

void decrypt_CBC(FILE *file, FILE *file_dest){
	head_handler(file,file_dest);	
	int caracter=0;
	int **matrix_m;
	int **inv_key;
	int **block;
	int **aux;
	creador_matrices_dinamicas(&block,1,3);
	creador_matrices_dinamicas(&matrix_m,1,3);
	creador_matrices_dinamicas(&inv_key,3,3);
	creador_matrices_dinamicas(&aux,1,3);
	
	//Matrix
	inv_key[0][0]=90;
	inv_key[0][1]=167; 
	inv_key[0][2]=1;
	inv_key[1][0]=74;
	inv_key[1][1]=179; 
	inv_key[1][2]=254; 
	inv_key[2][0]=177; 
	inv_key[2][1]=81; 
	inv_key[2][2]=1;
	
	//Initial vector
	printf("Insert initial vector: \n");
	scanf("%d %d %d",&block[0][0],&block[0][1],&block[0][2]);
	printf("Initial vector: %d %d %d \n",block[0][0],block[0][1],block[0][2]);
	
	while((caracter=fgetc(file))!=EOF){
		
			matrix_m[0][0]=(unsigned char)caracter;
			matrix_m[0][1]=(unsigned char)fgetc(file);
			matrix_m[0][2]=(unsigned char)fgetc(file);
			
			aux[0][0]=matrix_m[0][0];
			aux[0][1]=matrix_m[0][1];
			aux[0][2]=matrix_m[0][2];
			
			//Decrypt
			hillCipher(matrix_m,inv_key);
			//XOR
			xor(matrix_m,block);
						
			fputc(matrix_m[0][0],file_dest);
			fputc(matrix_m[0][1],file_dest);
			fputc(matrix_m[0][2],file_dest);
			//Aux
			block[0][0]=aux[0][0];
			block[0][1]=aux[0][1];
			block[0][2]=aux[0][2];	
			
					
			
		}	
	}
	
void decrypt_OFB(FILE *file, FILE *file_dest){
	head_handler(file,file_dest);	
	int caracter=0;
	int **matrix_m;
	int **inv_key;
	int **block;
	int **aux;
	creador_matrices_dinamicas(&block,1,3);
	creador_matrices_dinamicas(&matrix_m,1,3);
	creador_matrices_dinamicas(&inv_key,3,3);
	creador_matrices_dinamicas(&aux,1,3);
	
	//Matrix
	//inv_key[0][0]=90;
	//inv_key[0][1]=167; 
	//inv_key[0][2]=1;
	//inv_key[1][0]=74;
	//inv_key[1][1]=179; 
	//inv_key[1][2]=254; 
	//inv_key[2][0]=177; 
	//inv_key[2][1]=81; 
	//inv_key[2][2]=1;
	
	
	inv_key[0][0]=1;
	inv_key[0][1]=2; 
	inv_key[0][2]=3;
	inv_key[1][0]=4;
	inv_key[1][1]=5; 
	inv_key[1][2]=6; 
	inv_key[2][0]=11; 
	inv_key[2][1]=9; 
	inv_key[2][2]=8; 
	
	//Initial vector
	printf("Insert initial vector: \n");
	scanf("%d %d %d",&block[0][0],&block[0][1],&block[0][2]);
	printf("Initial vector: %d %d %d \n",block[0][0],block[0][1],block[0][2]);
	
	while((caracter=fgetc(file))!=EOF){
			//Decrypt
			hillCipher(block,inv_key);
		
			matrix_m[0][0]=(unsigned char)caracter;
			matrix_m[0][1]=(unsigned char)fgetc(file);
			matrix_m[0][2]=(unsigned char)fgetc(file);
					
			//XOR
			xor(matrix_m,block);
						
			fputc(matrix_m[0][0],file_dest);
			fputc(matrix_m[0][1],file_dest);
			fputc(matrix_m[0][2],file_dest);
						
					
			
		}	
	}


		
	
void xor(int **matrix_m,int **block){
	//printf("Block a: %d %d %d. Block b: %d %d %d.\n",matrix_m[0][0],matrix_m[0][1],matrix_m[0][2],block[0][0],block[0][1],block[0][2]);
	matrix_m[0][0]^=block[0][0];
	matrix_m[0][1]^=block[0][1];
	matrix_m[0][2]^=block[0][2];
	//printf("XORed block %d %d %d \n",matrix_m[0][0],matrix_m[0][1],matrix_m[0][2]);
}
