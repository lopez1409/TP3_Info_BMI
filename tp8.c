#include <stdio.h>
#include <stdlib.h>
#define TAM 20
//-------------------------------------

//link repositorio: https://github.com/lopez1409/TP3_Info_BMI

//-------------------------------------Prototipos

int cuantas_piezas(int);
int rectificable(float, float);
int rechazada(float, float);
void cargar_piezas(float *, int);
int contar(int (*)(float, float), float, float *, int);
float* reservar_memoria(int);
void segregar(int (*)(float, float), float, float *, int, float *);
void mostrar_piezas(char *, float *, int);
void liberar_memoria(float *);//la agrege para liberar la memoria utilizada

//------------------------------------


int main (void) {
	float diametros[TAM] = {0};
	int n;
	float max = 12;
	float min = 10;
	n = cuantas_piezas(TAM);
	
	cargar_piezas(diametros, n);
	
	int n_rectificar = contar(rectificable, max, diametros, n);
	
	float *p_rectificables = reservar_memoria(n_rectificar);
	
	segregar(rectificable, max, diametros, n, p_rectificables);
	
	int n_rechazar = contar(rechazada, min, diametros, n);
	float *p_rechazadas = reservar_memoria(n_rechazar);
	
	segregar(rechazada, min, diametros, n, p_rechazadas);
	
	mostrar_piezas("rectificables", p_rectificables, n_rectificar);
	
	mostrar_piezas("rechazadas", p_rechazadas, n_rechazar);
	
	//libero la memoria dinamica de estos arreglos
	liberar_memoria(p_rectificables);
	liberar_memoria(p_rechazadas);
	
	return 0;
}

//-------------------------------------

int cuantas_piezas(int max) {
	int n;
	do {
		printf("Cuántas piezas ingresará? ");
		scanf("%d", &n);
	} while (n < 0 || n > max);
	return n;
}
int rectificable(float diametro, float valor) {
	if (diametro > valor)
		return 1;
	else
		return 0;
}
int rechazada(float diametro, float valor) {
	if (diametro < valor)
		return 1;
	else
		return 0;
}

void cargar_piezas(float *p, int n){
	for(int a=0;a<n;a++){
		do{
			printf("Ingrese el diametro de la pieza %d: ",a+1);
			scanf(" %f",(p+a));
			if((*(p+a))<0)
				printf("No se puede ingresar numeros negativos\n");
		} while((*(p+a))<0);
	}
	
}

int contar(int (*criterio)(float, float), float valor, float *p, int n){
	int n_elementos=0;
	for(int a=0;a<n;a++){
		n_elementos+=(*criterio)(*(p+a),valor);
	}
	
	return n_elementos;
}
	
float* reservar_memoria(int n){
	float *p=malloc(n*sizeof(float));
	if(p==NULL)
		return NULL; 
	return p;
}
	
void segregar(int (*criterio)(float, float), float valor, float *p, int n, float *q){
	int indice=0;
	for(int a=0;a<n;a++){
		if((*criterio)(*(p+a),valor)){
			*(q+indice)=*(p+a);
			indice+=1;
		}
	}	
}

void mostrar_piezas(char *mensaje, float *p, int n){
	printf("Piezas %s: \n",mensaje);
	for(int a=0;a<n;a++){
		printf("Diametro: %.2f\n",*(p+a));
	}
}

void liberar_memoria(float *p){
	free(p);
}
