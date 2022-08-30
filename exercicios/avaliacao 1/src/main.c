/*

Faça um programa que solicita do usuário uma série de números, cada número pode ser um
int, float ou double. Antes de solicitar o número pergunte qual tipo de dado o usuário vai entrar.
Todos os números entrados devem ser armazenados num buffer único. Esse buffer deve ter tamanho
dinâmico e não deve desperdiçar memória, por exemplo, alocar sempre espaço para um double
quando o usuário inserir um int ou float.
Você não deve solicitar para o usuário quantos números ele deseja entrar, na escolha do tipo
de dados coloque uma opção para parar a entrada da série de números. Após isso você deve imprimir
todos os números do buffer, primeiro toda a série em sequência depois novamente, mas primeiro os
ints seguido dos floats e doubles.

*/

#include <stdio.h>
#include <stdlib.h>

void *StoreInt( void *buffer, int *intAmount, int fullSizeValue );
void *StoreFloat( void *buffer, float *floatAmount, int fullSizeValue  );
void StoreDouble( void *buffer, double *doubleAmount );

int main() {

    int input, userCheck = 1, intAmount = 0, floatAmount = 0, doubleAmount = 0, fullSizeValue = intAmount + floatAmount + doubleAmount;
    long long int fullSize = ( intAmount * sizeof( int ) ) + ( floatAmount * sizeof( float ) ) + ( doubleAmount * sizeof( double ) );
    void *buffer;

    buffer = malloc( 1 );
    int *intP = buffer;
    float *floatP = buffer;
    double *doubleP = buffer;

    do {
        printf( "qual tipo deseja armazenar? \n1) inteiro \n2)float \n3) double \n0) parar\n" );
        scanf( "%d", &input );
        fflush( stdin );
    
        switch ( input ) {
            case 1:
            buffer = realloc( buffer, fullSize + sizeof( int ) );
            floatP = StoreInt( intP, &intAmount, fullSizeValue );
            doubleP = ( double * ) floatP + floatAmount ;
            break;

            case 2:
            buffer = realloc( buffer, fullSize + sizeof( float ) );
            doubleP = StoreFloat( floatP, &floatAmount, fullSizeValue - intAmount );
            break;

            case 3:
            buffer = realloc( buffer, fullSize + sizeof( double ) );
            StoreDouble( doubleP, &doubleAmount );
            break;

            case 0:
            break;
        }

    } while ( userCheck != 0 );

    free( buffer );
    return ( 0 );
}

void *StoreInt( void *buffer, int *intAmount, int fullSizeValue ) {
    int *dummy = ( int * ) buffer + sizeof( int );

    printf( "digite o numero: " );
    scanf( "%d", dummy );
    fflush( stdin );

    *intAmount += 1;
    return ( dummy + 1 );
}

void *StoreFloat( void *buffer, float *floatAmount, int fullSizeValue ) {
    float *dummy = ( float * ) buffer + sizeof( float );

    printf( "digite o numero: " );
    scanf( "%d", dummy );
    fflush( stdin );

    *floatAmount += 1;
    return ( dummy + 1 );

}

void StoreDouble( void *buffer, double *doubleAmount) {
    double *dummy = ( double * ) buffer + sizeof( double );

    printf( "digite o numero: " );
    scanf( "%d", dummy );
    fflush( stdin );

    *doubleAmount += 1;
}