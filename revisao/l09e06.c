/*
    Elaborar um programa que leia dois valores inteiros (A e B). Em seguida fac¸a uma funcao
    que retorne a soma do dobro dos dois numeros lidos. A funcao devera armazenar o dobro
    de A na propria variavel A e o dobro de B na propria variavel B
*/

#include <stdlib.h>
#include <stdio.h>

int Doubler( int *a, int *b );

int main() {
    int a, b;

    printf( "Insira dois inteiros: " );
    scanf( "%d %d", &a, &b );

    printf( "2a = %d, 2b = %d, 2a+2b = %d\n", a, b, Doubler( &a, &b ) );

    return 0;
}

/*
====================
Doubler
 Doubles both inputs and returns their sum
====================
*/

int Doubler( int *a, int *b ) {
    *a = *a * 2;
    *b = *b * 2;

    return ( *a + *b );
}