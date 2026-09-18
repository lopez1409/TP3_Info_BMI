#include <stdio.h>

float calcularAreaRectangulo(float recLong,float recAlt);
float calcularPerimetroRectangulo(float recLong,float recAlt);
float calcularAreaCirculo(float radio);
float calcularPerimetroCirculo(float radio);
void imprimirResultados(float area,float perimetro);

#define PI 3.1416
int eleccion=0;

int main(void) {
	do{
		printf("Ingrese la figura que desea calcular (1: rectangulo, 2:circulo): ");
		scanf(" %d",&eleccion);
	} while(eleccion!=1&&eleccion!=2);
	if(eleccion==1){
		float recLong,recAlt;
		printf("Opcion de rectangulo seleccionada\n");
		printf("Ingrese la longitud del rectangulo: ");
		scanf(" %f",&recLong);
		printf("Ingrese la altura del rectangulo: ");
		scanf(" %f",&recAlt);
		imprimirResultados(calcularAreaRectangulo(recLong,recAlt),
						   calcularPerimetroRectangulo(recLong,recAlt));
	}else{
		float radio;
		printf("Opcion de circulo seleccionada\n");
		printf("Ingrese el radio del circulo: ");
		scanf(" %f",&radio);
		imprimirResultados(calcularAreaCirculo(radio),
						   calcularPerimetroCirculo(radio));
	}
	return 0;
}

float calcularAreaRectangulo(float recLong,float recAlt){
	return recLong*recAlt;
}
float calcularPerimetroRectangulo(float recLong,float recAlt){
	return recLong*2+recAlt*2;
}
float calcularAreaCirculo(float radio){
	return radio*radio*PI;	
}
float calcularPerimetroCirculo(float radio){
	return 2*PI*radio;
}
void imprimirResultados(float area,float perimetro){
	char* cadena=(eleccion==1)?"rectangulo":"circulo";
	printf("El area del %s es: %.2f\nEl perimetro del %s es: %.2f",cadena,area,cadena,perimetro);
}

