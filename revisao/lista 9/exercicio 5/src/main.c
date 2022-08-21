/*
    Faca um programa que leia dois valores inteiros e chame uma funcao que receba estes
    2 valores de entrada e retorne o maior valor na primeira variavel e o menor valor na
    segunda variavel. Escreva o conteudo das 2 variaveis na tela.
*/

#include <stdlib.h>
#include <stdio.h>

void Comparator( int *a, int *b );

int main() {
    int a, b;

    printf( "Insira dois inteiros: " );
    scanf( "%d %d", &a, &b );

    Comparator( &a, &b );

    printf( "a = %d, b = %d\n", a, b );

    return 0;
}

/*
====================
Comparator
 Compares a and b and leaves a with the highest value
====================
*/

void Comparator( int *a, int *b ) {
    if ( *a < *b ) {
        int dummy = *a;
        *a = *b;
        *b = dummy;
    }
}