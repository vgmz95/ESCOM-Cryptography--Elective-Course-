#include <stdlib.h>

int creador_matrices_dinamicas(int *** arreglo, int nfilas, int ncolumnas){
	int i;
	*arreglo = (int **)calloc(nfilas,sizeof(int *));
	if (*arreglo == NULL){
        exit(1);}

	for (i=0;i<nfilas;i++){
		(*arreglo)[i] = (int *)calloc(ncolumnas,sizeof(int));
		if ((*arreglo)[i] == NULL){
			exit(1);
		}
    	}
    return 0;
}

int escalar_matriz(int **matriz,int filas,int columnas,int escalar,int **matrizresul){
	int f,co;
	for (f=0;f<filas;f++){for (co=0;co<columnas;co++){matrizresul[f][co]=(matriz[f][co]*escalar);}}
	return 0;
}

int multiplicacion_matrices(int **matriz1,int **matriz2, int **matrizresul,int a,int b,int d){
	int c,e,k,sum=0;
	for (c=0;c<a;c++)
	{
		for (e=0;e<d;e++)
			{
				for(k=0;k<b;k++)
				{
					sum=sum+matriz1[c][k]*matriz2[k][e];
				}
				matrizresul[c][e]=sum;
				sum=0;
			}
	}
return 0;
}

int transpuesta(int **matriz,int filas,int columnas, int **matrizresul){
int f,co;
for (f=0;f<filas;f++){
	for (co=0;co<columnas;co++){
		matrizresul[co][f]=matriz[f][co];
	}
}
return 0;
}

int determinante(int **matriz,int a){
	int i,j,k,radio,det=1;
	if(a==2){return matriz[0][0]*matriz[1][1] - matriz[1][0]*matriz[0][1];}
	else if (a==3){return (matriz[0][0] * (matriz[1][1] * matriz[2][2] - matriz[2][1] * matriz[1][2])-matriz[1][0] * (matriz[0][1] * matriz[2][2] - matriz[2][1] * matriz[0][2])+matriz[2][0] * (matriz[0][1] * matriz[1][2] - matriz[1][1] * matriz[0][2])); }
	else {
		for(i = 0; i < a; i++){
			for(j = 0; j < a; j++){
			    if(j>i){
				radio = matriz[j][i]/matriz[i][i];
				for(k = 0; k < a; k++){
				    matriz[j][k] -= radio * matriz[i][k];}}}
		}
		for(i = 0; i < a; i++)
		det *= matriz[i][i];
		return det;
	}
}
