#include <stdio.h>

int main(void) {
	int calificacion;
	printf("Ingrese la calificacion: ");
	scanf(" %d",&calificacion);
	if(calificacion>=90)
		printf("Calificacion: A");
	else if(calificacion>=80)
		printf("calificacion: B");
	else if(calificacion>=70)
		printf("calificacion: C");
	else if(calificacion>=60)
		printf("calificacion: D");
	else
		printf("calificacion: F");
	return 0;
}

