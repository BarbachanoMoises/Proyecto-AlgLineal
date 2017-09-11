#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
	FILE * archivo = fopen("input2.txt", "rb");
	FILE* output = fopen("output2.txt", "w");
	if(archivo == NULL){
		printf("Error en la apertura del archivo");
	}
	char caracter;
	float **matriz;
	float **matriz_aux;
	int nMatrices=0;
	int nMatricessegundo=0;
	int nMatricestercero=0;
	int i=0,m=0,n=0;
	int signo=0,numero=0;
	int numeroaux=0;
	int nFilas=0, nColumnas=0;
	int contadorMatriz=0;
	int ultimo=0;
	int aux=0;
	float ayud=0;
	int k=0;
	float auxi=0;
	float x=0;
	int bandera=0;
	int m_aux=0;
	
	while (feof(archivo) == 0){
		caracter = fgetc(archivo);
		//Aqui entran para conocer numero de matrices.
		if(i==0){
			nMatrices = caracter;
			i=1;
			nMatrices = nMatrices - 48;
			caracter = fgetc(archivo);
			if(caracter!='\r'){
				nMatricessegundo=caracter;
				nMatricessegundo=nMatricessegundo-48;
				nMatrices=nMatrices * 10;
				nMatrices=nMatrices+nMatricessegundo;
				caracter = fgetc(archivo);
				if(caracter!='\r'){
					nMatricestercero=caracter;
					nMatricestercero=nMatricestercero-48;
					nMatrices=nMatrices*10;
					nMatrices=nMatrices+nMatricestercero;
					caracter= fgetc(archivo);
				}
			}
		}
		//Termina numero de matrices
		if(caracter==' ' || caracter=='\r' || caracter=='\n'){
			do{
				caracter=fgetc(archivo);
			} while(caracter==' ' || caracter=='\r' || caracter=='\n');
		}
		//Se cuentan los caracteres para filas y columnas
		if(caracter!='\r' && caracter!='\n' && nFilas==0){
			nFilas=caracter;
			nFilas=nFilas-48;
			caracter= fgetc(archivo);
			caracter=fgetc(archivo);
			nColumnas=caracter;
			nColumnas=nColumnas-48;
			nColumnas=nColumnas+1;
			caracter = fgetc(archivo);
		}
		//Termina numero de filas y columnas;
		if(caracter!='\r' || caracter!='\n'){
			//Aqui es donde se crea la matriz dinamica
			matriz = (float **) calloc(nFilas, sizeof(float *));
			for (m= 0; m< nFilas; m++){
				matriz[m] = (float *) calloc(nColumnas, sizeof(float));
			}
			m=0;
			n=0;
			//Termina matriz dinamica
			while(nFilas-m>0){
				while(nColumnas-n>0){
					if(caracter==' ' || caracter=='\r'){
						do{
							caracter=fgetc(archivo);
						} while(caracter==' ' || caracter=='\r');
					}
					if(caracter!=' ' && caracter!='\r'){
						if(caracter=='-'){
							signo=-1;
							caracter=fgetc(archivo);
						}
						else{
							signo=1;
						}
						if(caracter=='\n' || caracter=='\r'){
							caracter=fgetc(archivo);
						}
						if(caracter=='-'){
							signo=-1;
							caracter=fgetc(archivo);
						}
						
						numero=caracter;
						numero=numero-48;
						caracter=fgetc(archivo);
						if(contadorMatriz+1==nMatrices){
							ultimo=1;
						}
						if(caracter!=' ' && caracter!='\r' && ultimo!=1 ){
							do{
								printf(".");
								numero=numero*10;
								numeroaux=caracter;
								numeroaux=numeroaux-48;
								numero=numero+numeroaux;
								caracter=fgetc(archivo);
							}while(caracter!=' ' && caracter!='\r' );
						}
						if(ultimo==1 && caracter!=' ' && caracter!='\r'){
							aux=caracter;
							aux=aux-48;
							while(aux==1 || aux==2 || aux==3 || aux==4 || aux==5 || aux==6 || aux==7 || aux==8 || aux==9 || aux==0){
								numero=numero*10;
								numeroaux=caracter;
								numeroaux=numeroaux-48;
								numero=numero+numeroaux;
								caracter=fgetc(archivo);
								aux=caracter;
								aux=aux-48;
							}
						}
						
						if(caracter==' ' || caracter=='\r' || ultimo==1){
							numero=numero*signo;
							matriz[m][n] = numero;
							numero=0;
						}
					}
					n++;
				}
				if(n==nColumnas){
					n=0;
				}
				m++;
			}
		}
		
		/**AQUI DEBE IR LA OPERACION DE GAUUSS */
		m=0;
		n=0;
		matriz_aux = (float **) calloc(nFilas, sizeof(float *));
		for (m= 0; m< nFilas; m++){
			matriz_aux[m] = (float *) calloc(nColumnas, sizeof(float));
		}
		
		while(bandera==0){
			while(k<nFilas){
				//empieza a comprobar
				if(matriz[k][k]==0){
					for(m=0;m<nFilas;m++){
						if(m==(nFilas-1)){
							for(n=0;n<nColumnas;n++){
								matriz_aux[0][n]=matriz[m][n];
							}
						}
						else{
							for(n=0;n<nColumnas;n++){
								matriz_aux[m+1][n]=matriz[m][n];
							}
						}
					}
					
					for( m = 0; m < nFilas; m++){
						for(n = 0; n < nColumnas; n++){
							matriz[m][n]=matriz_aux[m][n];
						}
					}
					
					k=0;
				}
				else{
					k++;
				}
			}
			
			bandera=1;
		}
		
		k=0;
		bandera=0;
		
		/**EMPEZAMOS A TRANSFORMAR */
		while(k<nFilas){
			ayud=matriz[k][k];
			
			if(matriz[k][k]!=0){
				matriz[k][k]=(matriz[k][k])/(ayud);
				for(n = 0; n < nColumnas; n++){
					if(k==n){
						//nada
					}
					else{
						matriz[k][n]=(matriz[k][n])/(ayud);
						if(matriz[k][n]==-0){
							matriz[k][n]=0;
						}
					}
				}
				/**for(n=0; n<nColumnas;n++){
				}
				*/
				for(m=0;m<nFilas;m++){
					if(m==k){
						//no hacer nada
					}
					else{
						if(matriz[m][k]<0){
							x=-1;
						}
						else{
							x=-1;
						}
						
						if(matriz[m][k]!=0){
							//matriz[m][k]=((x)*(matriz[m][k]))+matriz[m][k];
							//printf("1,0:%f\n",matriz[1][0]);
							auxi=matriz[m][k];
							matriz[m][k]=(x*(matriz[m][k]))+matriz[m][k];
							for(n = k; n < nColumnas; n++){
								if(k!=n){
									matriz[m][n]=(x*(matriz[k][n])*(auxi))+matriz[m][n];
								}
							}
						}
						else{
							//si es igual nada.
						}
						m_aux=m;
						m=m_aux;
					}
				}
				
				k++;
			}
			else{
				break;
			}
		}
		k=0;
		
		for (m=0; m< nFilas; m++)
			free(matriz_aux[m]);
		free(matriz_aux);
		
		/** AQUI DEBE TERMINAR LA OPERACION DE GAUSS */
		
		/** AQUI EMPIEZA EL GUARDADO EN OUTPUT */
		for( m = 0; m < nFilas; m++){
			for(n = 0; n < nColumnas; n++){
				fprintf(output,"%f ",matriz[m][n]);
			}
			fprintf(output,"\n");
		}
		fprintf(output,"\n");
		/** AQUI TERMINA EL GUARDADO EN OUTPUT*/
		
		//REINICIANDO MATRIZ DINAMICA
		nFilas=0;
		nColumnas=0;
		/**Liberacion*/
		for (m=0; m< nFilas; m++)
			free(matriz[m]);
		free(matriz);
		
		//REINICIANDO MATRIZ DINAMICA
		
		/**Fin liberacion*/
		contadorMatriz++;
		if(contadorMatriz==nMatrices){
			break;
		}
		
	}
	fclose(archivo);
	return 0;
}

