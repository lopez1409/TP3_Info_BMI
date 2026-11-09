#include <stdio.h>
#include <stdlib.h>

#define TAM_NOMBRE_ESTUDIANTE 20
#define TAM_NOMBRE_MATERIA 20

//---------------------Tipos de datos

typedef struct {
	char nombre[TAM_NOMBRE_MATERIA];
	int cantidad_parciales;
	int *parcial;
	float promedio;
} materia_t;

struct estudiante {
	int legajo;
	char nombre[TAM_NOMBRE_ESTUDIANTE];
	int cantidad_materias;
	materia_t *materia;
}; 

//Los miembros que son punteros se usan para apuntar a arreglos dinámicos.

//--------------------------Prototipos

struct estudiante cargar_estudiante(void);
materia_t* reservar_materias(int);
void cargar_materia(materia_t *);
int* reserva_parciales(int);
void cargar_parciales(materia_t *);
void liberar_parciales(int *);
void liberar_materias(materia_t *);
void imprimir_estudiante(struct estudiante);

//-------------------------------------

int main(void){
	struct estudiante est1;
	est1 = cargar_estudiante();
	cargar_materia(est1.materia);
	imprimir_estudiante(est1);
	liberar_parciales(est1.materia->parcial);
	liberar_materias(est1.materia);
	return 0;
} 
	
//---------------------------------------

struct estudiante cargar_estudiante(void) {
	struct estudiante e;
	printf("Ingrese legajo del estudiante: ");
	scanf("%d", &e.legajo);
	printf("Ingrese nombre del estudiante: ");
	scanf(" %80[^\n]s", e.nombre);
	e.cantidad_materias = 1;
	e.materia = reservar_materias(e.cantidad_materias);
	return e;
} 

materia_t* reservar_materias(int n) {
	materia_t *p = NULL;
	p = malloc(n * sizeof(materia_t));
	if (p == NULL) {
		printf("No se pudo reservar memoria. Fin del programa.\n");
		exit(1);
	}
	return p;
} 

void cargar_materia(materia_t *p) {
	printf("Ingrese el nombre de la materia: ");
	scanf(" %80[^\n]s", p->nombre);
	printf("¿Cuántos parciales tiene %s? ", p->nombre);
	scanf("%d", &p->cantidad_parciales);
	p->parcial = reserva_parciales(p->cantidad_parciales);
	cargar_parciales(p);
}
int* reserva_parciales(int n) {
	int *p = NULL;
	p = malloc(n * sizeof(int));
	if (p == NULL) {
		printf("No se pudo reservar memoria. Fin del programa.\n");
		exit(1);
	}
	return p;
}
void cargar_parciales(materia_t *p) {
	for (int i = 0; i < p->cantidad_parciales; i++) {
		do{
			printf("Ingrese calificación del %d° parcial: ", i + 1);
			scanf("%d", p->parcial+i);
			if(p->parcial[i]<1||p->parcial[i]>10)
				printf("Esa no es una nota de parcial valida\n");
		} while(p->parcial[i]<1||p->parcial[i]>10);
	}
} 
void liberar_parciales(int *p) {
	if (p != NULL)
		free(p);
}
void liberar_materias(materia_t *p) {
	if (p != NULL)
		free(p);
}
//no paso el modelo de esta funcion asi que la hice segun lo que devuelve en el apartado b de la actividad pero sin el promedio
void imprimir_estudiante(struct estudiante est1){
	printf("%d	%s	",est1.legajo,est1.nombre);
	materia_t *materia_estudiante=est1.materia;
	for(int a=0;a<materia_estudiante->cantidad_parciales;a++){
		printf("%d	",*(materia_estudiante->parcial+a));
	}
}
	
	
