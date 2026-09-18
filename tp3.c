#include <stdio.h>

//Codigo de calculo de indice me masa corporal
//Modificado para validar versiones

int main(void) {
	float pesoUsuario,alturaUsuario;
	do{
		printf("Ingrese su peso en kg: ");
		scanf(" %f",&pesoUsuario);
		if(pesoUsuario<0.0)
			printf("Ingreso un peso invalido\n");
	} while(pesoUsuario<0.0);
	do{
		printf("Ingrese su altura en m: ");
		scanf(" %f",&alturaUsuario);
		if(alturaUsuario<0.0)
			printf("Ingreso una altura invalida\n");
	} while(alturaUsuario<0.0);
	printf("Su indice de masa corporal es de %.2f",pesoUsuario/(alturaUsuario*alturaUsuario));
	printf("\nIndice		| Condicion\n----------------------------");
	printf("\n<18.5		| Bajo peso\n18.5 a 24.9	| Normal");
	printf("\n25.0 a 29.9	| Sobrepeso\n>=30		| Obesidad");
	
	return 0;
}

//Link repositorio: https://github.com/lopez1409/TP3_Info_BMI/tree/modificacion-bmi

