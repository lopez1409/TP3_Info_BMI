#include <stdio.h>

#define TAM 5

int main(void) {
	int barra[TAM];
	float precio[TAM];
	int indiceCaro=0,indiceBarato=0;
	printf("Ingrese %d productos, se solicitara el codigo y precio: ",(int)TAM);
	for(int i=0;i<TAM;i++){
		do{
			printf("Ingrese el codigo de barras (1-999999999): ");
			scanf(" %d",&barra[i]);
			if(barra[i]<0||barra[i]>999999999)
				printf("Error. El codigo de barras debe estar entre 1 y 999999999\n");
		} while(barra[i]<0||barra[i]>999999999);
		do{
			printf("Ingrese el precio: ");
			scanf(" %f",&precio[i]);
			if(precio[i]<0)
				printf("Error. El precio no puede ser negativo\n");
		} while(precio[i]<0);
		if(precio[i]>precio[indiceCaro])
			indiceCaro=i;
		if(precio[i]<precio[indiceBarato])
			indiceBarato=i;
	}
	printf("Codigo Precio\n");
	for(int i=0;i<TAM;i++)
		printf("%d	%.2f\n",barra[i],precio[i]);
	printf("Mas Caro: [%d] %.2f\nMas barato: [%d] %.2f",
		   barra[indiceCaro],precio[indiceCaro],
		   barra[indiceBarato],precio[indiceBarato]);
	return 0;
}

//repositorio: https://github.com/lopez1409/TP3_Info_BMI

