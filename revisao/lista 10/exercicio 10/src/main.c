/*
	Faca um programa que pergunte ao usuario quantos valores ele deseja armazenar em
	um vetor de double, depois use a funcao MALLOC para reservar (alocar) o espaco de
	memoria de acordo com o especificado pelo usuario. Esse vetor deve ter um tamanho
	maior ou igual a 10 elementos. Use este vetor dinamico como um vetor comum, atri-
	buindo aos 10 primeiros elementos do vetor valores aleatorios (usando a funcao rand)
	entre 0 e 100. Exiba na tela os valores armazenados nos 10 primeiros elementos do
	vetor.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
	int qty;
	double *vector, *i, value;

	printf( "digite quantos valores deseja armazenar: ");
	scanf( "%d", &qty );
	fflush( stdin );

	if ( qty < 10 ) {
		qty = 10;
	}

	vector = ( double * ) malloc( qty * sizeof( double ) );

	i = vector;

	for ( int j = 0; j < 10; j++ ) {
		value = rand() % 100;
		*i = value;
		printf( "%d> %f\n", j + 1, *i );
		i++;
	}

	free( vector );

	return ( 0 );
}