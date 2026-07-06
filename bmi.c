#include <stdio.h>

//Codigo de calculo de indice me masa corporal

int main(void) {
	float pesoUsuario,alturaUsuario;
	printf("Ingrese su peso en kg ");
	scanf(" %f",&pesoUsuario);
	printf("Ingrese su altura en m ");
	scanf(" %f",&alturaUsuario);
	printf("Su indice de masa corporal es de %.2f",pesoUsuario/(alturaUsuario*alturaUsuario));
	printf("\nIndice		| Condicion\n----------------------------");
	printf("\n<18.5		| Bajo peso\n18.5 a 24.9	| Normal");
	printf("\n25.0 a 29.9	| Sobrepeso\n>=30		| Obesidad\n");
	
	//Modificacion de codigo para TP4
	float bmi=pesoUsuario/(alturaUsuario*alturaUsuario);
	if(bmi>=30.0)
		printf("Su condicion es: Obesidad");
	else if(bmi>=25.0)
		printf("Su condicion es: Sobrepeso");
	else if(bmi>=18.5)
		printf("Su condicion es: Normal");
	else
		printf("Su condicion es: Bajo peso");
	return 0;
}

