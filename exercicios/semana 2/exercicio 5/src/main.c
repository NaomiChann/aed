/*
	Faça um programa que armazene a informação de várias
	pessoas.
	O programa só deve sair quando o usuário disser que não
	deseja mais entrar com os dados de outra pessoa.
	Antes de sair o programa deve apresentar, de forma
	organizada, os dados de todas as pessoas.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char nome[30];
	int idade;
	int altura;
} Pessoa;

int Test ( int num );

int main()
{
	Pessoa *personP;
	void *person;
	int userCheck = -1, userCount = 0, check = 0;

	person = malloc( 1 );

	do {
		userCount++;
		person = realloc( person, userCount * sizeof( Pessoa ) );
		personP = ( Pessoa * ) person + ( userCount - 1 );

		printf( "Digite o nome a ser adicionado: " );
		scanf( "%29s", personP->nome );
		fflush( stdin );

		do {
			printf( "Digite a idade: " );
			scanf( "%d", &personP->idade );
			fflush( stdin );
		} while ( Test( personP->idade ) == 1 );
		
		do {
			printf( "Digite a altura (em cm): " );
			scanf( "%d", &personP->altura );
			fflush( stdin );
		} while ( Test( personP->altura ) == 1 );
	
		do {
			printf( "Deseja adicionar mais alguem? \n1) Sim \n0) Nao\n" );
			scanf( "%d", &userCheck );
			fflush( stdin );

			if ( userCheck != 0 && userCheck != 1 ) {
				printf( "Selecao invalida.\n" );
				check = 0;
			} else {
				check = 1;
			}
		} while ( check == 0 );

	} while ( userCheck == 1 );

	personP = person;

	for ( int i = 0; i < userCount; i++ ) {
		printf( "<%d> %s, ", i, personP->nome );
		printf( "%d anos, ", personP->idade );
		printf( "%d cm\n", personP->altura );
		personP++;
	}
	free( person );

	return (0);
}

int Test ( int num ) {
	if ( num > 999 || num < 0 ) { 
		printf( "Numero invalido.\n" );
		return ( 1 );
	} else {
		return ( 0 );
	}
}