#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>

int x = 1; // El caballo inica en la casilla superior
int y = 1; // izquierda
const int TAMANO = 8; 
int contador = 1; // Esta variable lleva la cuenta de las casillas recorridas
int ciclos = 0; // Esta variable cuenta los ciclos que se intentan antes de terminar que ya no haya lugares a los cuales ir
int intentos_fallidos = 0; // Esta variable cuenta cuantos ciclos se intentan antes de obtener el que pidio el usuario.

void Imprime( int a[TAMANO + 1][TAMANO + 1]);

int main()
{

	int Arreglo[TAMANO + 1][TAMANO + 1];
	Arreglo[y][x] = 1;
	int dado1;
	int dado2;
	int casillas_requeridas =60;
	printf("\nCargando...\n");
	while ( contador < casillas_requeridas )
	{ // Abre while
		intentos_fallidos++; // Se incrementa cada que inica un intento de
		// completar las casillas pedidas por el usuario
		contador = 1; // Dado que ya se ha colocado al caballo en (y,X), se
		// inicia el contador en 1
		int ciclos = 0; // Se inicia con 0 ciclos o lanzamientos de dados infructuosos
		// Cada vez que se aborta un intento han de limpiarse las casillas, con
		// el siguiente par de ciclos se establecen a 0 nuevamente.
		int s;
		int t;
		for ( s = 0; s <= TAMANO; s++ )
		{ 
			for ( t = 0; t <= TAMANO; t++ )
			Arreglo[s][t] = 0;
		} 

		// Se ha de colocar el caballo en la esquina superior izquierda cada vez
		// Desde luego se puede poner en cualquier parte
		x = 1;	
		y = 1;
		Arreglo[y][x] = 1;

		// Mientras no se encuentre un lugar para el caballo
		while ( 1000 != ciclos )
		{ // Abre while
			ciclos++;
			dado1 = 1 + rand() % 8;
			dado2 = 1 + rand() % 8;
			if ( 2 == fabs(x - dado1))
			{
				if ( 1 == fabs(y - dado2))
				if ( 0 == Arreglo[dado1][dado2] )
				{ 
					Arreglo[dado1][dado2] = ++contador;
					x = dado1;
					y = dado2;
					ciclos = 0;
				} 
			} 

			if ( fabs(fabs(x) - fabs(dado1)) == 1)
			{ 
				if ( fabs(fabs(y) - fabs(dado2)) == 2 )
				if ( 0 == Arreglo[dado1][dado2] )
				{ 
					Arreglo[dado1][dado2] = ++contador;
					x = dado1;
					y = dado2;
					ciclos = 0;
				} 
			}	 

		} 
	} 

	system("clear");
	printf("\nLISTO!\n");
	printf("\nSe recorrieron %d casillas\n", contador);
	printf("\nSe intentaron %d circuitos antes de obtener", intentos_fallidos);
	printf(" el requerido.\n");

	Imprime( Arreglo);


} // Cierra main


/*La funcion siguiente despliega el tablero de ajedrez */

//////////////////////////////////////////
// Imprime
///////////////////////////////////////////

void Imprime( int Matriz[TAMANO + 1][TAMANO + 1])
{ // Abre la funcion Imprimir
	int i;
	int j;
	printf("\n\nEste es el tablero:\n\n ");
	for ( i = 1; i <= TAMANO; i++ )
	{ 
		for ( j = 1; j <= TAMANO; j++)
		{ 
  			printf(" %d\t", Matriz[i][j]);
		} 
		printf("\n\n\n");
	} 
	printf("\n\n\n");
} // Cierra la funcion Imprimir
