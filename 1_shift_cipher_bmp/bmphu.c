#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
int isnValid(int shift_num);
void io(char filename[255],char output_filename[255],char opt,unsigned char RGB[3]);
void encrypt(FILE *file, FILE *file_dest,unsigned char RGB[3]);
void decrypt(FILE *file, FILE *file_dest,unsigned char  RGB[3]);
void head_handler(FILE *file,FILE *file_dest);
void skip(FILE *file,FILE *file_dest,int n);
void creador_matrices_dinamicas(char *** arreglo, int nfilas, int ncolumnas);

int file_size_w;
int file_size_h;






int main(int argc, char *argv[]){
	char opt;
	printf("Shift Cipher BMP\n");
	printf("a)Encrypt\nb)Decript\n");
	printf("Select an operation:");
	scanf("%c",&opt);
	
	char filename[256],output_filename[256];
	unsigned char RGB[3];
	printf("Filename: ");	
	scanf("%s",filename);
	
		printf("\nInsert shifts: ");
		scanf("%hhu %hhu %hhu",&RGB[2],&RGB[1],&RGB[0]);
	
	
	printf("Output Filename: ");	
	scanf("%s",output_filename);
	
	io(filename,output_filename,opt,RGB);
	
	return 0;
	
	}

void io(char filename[256],char output_filename[256],char opt,unsigned char RGB[3]){
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
		encrypt(file,file_dest,RGB);
	else if (opt=='b')
		decrypt(file,file_dest,RGB);
	else
		printf("Invalid option");
		
	fclose(file);
	fclose(file_dest);

	
	
}

void encrypt(FILE *file, FILE *file_dest,unsigned char RGB[3]){
	head_handler(file,file_dest);			
	
	int caracter=0;
	unsigned char aux=0;
	printf("Trying to allocate memory \n");
	printf("Total of pixels: %d\n",(file_size_h*file_size_w)/3);
	unsigned char **array_input;
	creador_matrices_dinamicas((char***)&array_input,(file_size_h*file_size_w)/3,3);
	printf("Memory allocated\n");	
	int i=0,j=0;
	while((caracter=fgetc(file))!=EOF){
			aux=(unsigned char)caracter;
			array_input[i][j]=aux;
			j++;
			if(j==2){
				j=0;
				i++;
			}
		}
	
	
	
		
		
	
}

void decrypt(FILE *file, FILE *file_dest,unsigned char RGB[3]){
	head_handler(file,file_dest);			
	
    int caracter=0;
	unsigned char aux=0;
	int num=0;

	while((caracter=fgetc(file))!=EOF){
			aux=(unsigned char)caracter;
			fputc(aux-RGB[num%3],file_dest);
			++num;
		}	



	
	}
	


int isnValid(int shift_num){
	if (shift_num==0){
		printf("Number can't be 0");
		return 0;}
	else
		return 1;

}

void head_handler(FILE *file,FILE *file_dest){
	int offset;	
	skip(file,file_dest,10);	
	fread(&offset,sizeof(int),1,file );
	fwrite(&offset,sizeof(int),1,file_dest);
	skip(file,file_dest,4);
	
	fread(&file_size_w,sizeof(int),1,file );
	fwrite(&file_size_w,sizeof(int),1,file_dest);
	
	fread(&file_size_h,sizeof(int),1,file );
	fwrite(&file_size_h,sizeof(int),1,file_dest);
	
	skip(file,file_dest,offset-22);	
	}

void skip(FILE *file,FILE *file_dest,int n){
	unsigned char caracter;
	int i;
	for(i=0;i<n;i++){
			caracter=getc(file);
			fputc(caracter,file_dest);
			}
	
}



void creador_matrices_dinamicas(char *** arreglo, int nfilas, int ncolumnas){
	int i;
	*arreglo = (char **)calloc(nfilas,sizeof(char *));
	if (*arreglo == NULL){
		perror("Error allocate");
        exit(1);}

	for (i=0;i<nfilas;i++){
		(*arreglo)[i] = (char *)calloc(ncolumnas,sizeof(char));
		if ((*arreglo)[i] == NULL){
			exit(1);
		}
    }
}
