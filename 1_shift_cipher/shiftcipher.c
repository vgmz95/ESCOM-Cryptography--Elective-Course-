#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int isnValid(int shift_num);
void io(int shift_num,char filename[256],char output_filename[256],char opt);
void encrypt(FILE *file, FILE *file_dest,int shift_num);
void decrypt(FILE *file, FILE *file_dest,int shift_num);
int mod(int a, int b);

int main(int argc, char *argv[]){
	char opt;
	printf("Shift Cipher\n");
	printf("a)Encrypt\nb)Decript\n");
	printf("Select an operation:");
	scanf("%c",&opt);
	
	char filename[256],output_filename[256];
	int shift_num;
	printf("Filename: ");	
	scanf("%s",filename);
	do{
		printf("\nInsert shift: ");
		scanf("%d",&shift_num);
	}while(!isnValid(shift_num));
	
	printf("Output Filename: ");	
	scanf("%s",output_filename);
	
	io(shift_num,filename,output_filename,opt);
	
	return 0;
	
	}

void io(int shift_num,char filename[256],char output_filename[256],char opt){
	FILE *file,*file_dest;		
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
	
	if(opt=='a')
		encrypt(file,file_dest,shift_num%26);
	else if (opt=='b')
		decrypt(file,file_dest,shift_num%26);
	else
		printf("Invalid option");
		
	fclose(file);
	fclose(file_dest);

	
	
}

void encrypt(FILE *file, FILE *file_dest,int shift_num){
	int caracter,aux;
	while((caracter=fgetc(file))!=EOF){
			if(!isblank(caracter)&&!isspace(caracter)){
				aux=caracter-97;
				aux=mod((aux+shift_num),26);
				aux+=65;				
				fputc(aux,file_dest);
				}
		}	
	
	}

void decrypt(FILE *file, FILE *file_dest,int shift_num){
	int caracter,aux;
	while((caracter=fgetc(file))!=EOF){
			if(!isblank(caracter)&&!isspace(caracter)){
				aux=caracter-65;
				aux=mod((aux-shift_num),26);
				aux+=97;
				fputc(aux,file_dest);
				}
		}	
	}
	


int isnValid(int shift_num){
	if (shift_num==0){
		printf("Number can't be 0");
		return 0;}
	else if ((shift_num%26)==0){
		printf("Number can't be a multiple of 26");
		return 0;}
	else
		return 1;

}


int mod(int a, int b){
    int r = a % b;
    return r < 0 ? r + b : r;
}
