#include <stdio.h>
#include <stdlib.h>  //Libreria que contiene a funcion rand() y srand()
#include <time.h> //Hora y fecha del sistema

/*
Funcion para encontrar la longitud de la linea mas larga de 1s en una matriz
cuadrada de tamano size.
Params
− int ∗∗matrix : Puntero a la matriz cuadrada de enteros.
− int size: Tamano de la matriz (numero de filas y columnas).
− int ∗result: Puntero donde se almacenara la longitud de la secuencia mas
larga de 1s.

Retorno:
− No retorna un valor, pero modifica el valor en result.
*/
void findLargestLine (int **matrix, int size, int *result) {
	int largestLine = 0; //Para almacenar linea de 1s mas larga
  int **ptr = matrix;  // puntero al primer elemento
  int line_sequence_count = 0; //contador de 1s
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        // ptr + i: fila, *(ptr + i) + j: elemento de la fila
        // uno encontrado
        if (*(*(ptr + i) + j) == 1) {
          line_sequence_count++;
          if (line_sequence_count > largestLine) { //si el contador encuentra una linea de 1s mas larga que la anterior esa sera la nueva linea de 1s consecutivos mas larga
            largestLine = line_sequence_count;
            *result = largestLine;
          }
        }
        else {
          line_sequence_count = 0;
        }
      }
      
    }
}

/*
Funcion para reservar la matriz en memoria dinamica.
Params:
− int ∗∗∗ matrix: Doble puntero para la matriz que sera creada.
− int size: Tamano de la matriz (numero de filas y columnas).
Retorno:
− No retorna un valor. Reserva memoria para la matriz.
*/
void allocateMatrix (int ***matrix, int size) {
	// reservar arreglo de filas (matriz) en memoria
	*matrix = (int**) malloc(size*sizeof(int *));   //Malloc recibiendo en bytes el bloque donde queremos reservar en el heap
	for (int i = 0; i < size; i++) {  // recorre filas
		// reservar fila en memoria
		*(*(matrix) + i) = (int *) malloc(size * sizeof(int));
	}
}

/*
Funcion para llenar la matriz con numeros aleatorios ( 0s y 1s).
Parametros:
− int ∗∗matrix: Puntero a la matriz a llenar.
− int size: tamano de la matriz (numero de filas y columnas).
Retorno:
− No retorna un valor . Llena la matriz con valores aleatorios.
*/
void fillMatrix (int **matrix, int size) {
	srand(time(NULL));  //srand() permite indicar la semilla con la que quiero iniciar, time(NULL) semilla aleatoria cada tiempo
	int* row_ptr = NULL;
	for (int i = 0; i < size; i++){
		// {fila0, fila1, fila2}
		row_ptr = *(matrix + i);  // obtener puntero a fila (array)
		for (int j = 0; j < size; j++) {
			*(row_ptr + j) = rand() % 2; //Generar numeros aleatorios y % para generar numeros pequenos que vayan entre 0s y n-1s por eso se escribe 2s (0s y 1s)
		}
	}
}

/*
Funcion para imprimir la matriz.
Parametros:
− int ∗∗matrix: Puntero a la matriz que se va a imprimir.
− int size: tamano de la matriz (numero de filas y columnas).
Retorno :
− No retorna un valor. Imprime la matriz en la salida estandar.
*/

void printMatrix(int **matrix, int size) {
	printf("Matrix (%dx%d ) : \n", size, size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d ", *(*(matrix + i) + j));
		}
		printf("\n");
	}
}

/*
Funcion para liberar la memoria asignada a la matriz.
Params:
− int ∗∗matrix: Puntero a la matriz que se va a liberar.
− int size: tamano de la matriz (numero de filas y columnas).
Retorno :
− No retorna un valor. Liberala memoria utilizada por la matriz.
*/
void freeMatrix(int **matrix, int size){
	for (int i = 0; i < size ; i++){
		free(*(matrix + i)); //Liberar cada fila
	}
	free (matrix); //Liberar la matriz (arreglo de filas)
}

int main() {
	int size = 0, largestLine = 0; //
	printf("Ingrese el tamaño de la matriz cuadrada: ");
 	scanf("%d", &size);

	int **matrix = NULL; //Condicion en que inicializa el puntero 
	allocateMatrix(&matrix, size);
	fillMatrix(matrix, size);
	printMatrix(matrix, size);
	
	findLargestLine(matrix, size, &largestLine);

	printf ("El tamano de la secuencia de 1s mas grande es : %d\n", largestLine);
	freeMatrix(matrix, size);
	return 0;
}
