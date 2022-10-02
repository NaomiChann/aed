/*
	Continuar a sua implementação da agenda (exercício 3) semana 1
	dentro dos mesmo parâmetros, mas incluir o seguinte.

	Nenhuma variável pode ser declarada em todo o programa,
	somente ponteiros. Todos os dados do programa devem ser
	guardados dentro do pBuffer.
	Nem mesmo como parâmetro de função. Só ponteiros que apontam
	para dentro do pBuffer.
	Exemplo do que não pode: int c; char a; int v[10];
	void Funcao(int parametro)

	Não pode usar struct em todo o programa.

	Usar fila ordenada (heap) para armazenar as pessoas em ordem
	alfabética sempre que o usuário incluir uma nova pessoa.

	Implementar a base de dados da agenda usando lista duplamente ligada
	Somente essa base de dados pode ficar fora do buffer principal,
	ou seja, pode usar um malloc para cada nodo.

	Seguir as orientações elaborados pelo monitor para código!
	Entregar link de um vídeo explicando o código e mostrando alguns
	testes e ao final o resultado do DrMemory.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_BUFFER ( ( 3 * sizeof( int ) ) + ( sizeof( char * ) ) )
#define SIZE_NODE ( ( 10 * sizeof( char ) ) + ( 2 * sizeof( int ) ) + ( 2 * sizeof( char * ) ) )

void Push( int *userCount, char **head );
void List( int *userCount, char **head );

int main() {
	// |count|input|i|*head|
	// |name[10]|age|phone|*prev|*next|

	void *pBuffer;
	pBuffer = malloc( SIZE_BUFFER );

	int *userCount = ( int * ) pBuffer, *input = userCount + 1;
	*userCount = 0;
	*input = 0;

	char **head = ( char ** ) ( input + 2 );
	*head = NULL;

	do {
		fflush( stdin );
		Push( userCount, head );
		printf( "deseja continuar: 0 para s" );
		scanf( "%d", input );
	} while ( *input == 0 );

	List( userCount, head );

	return ( 0 );	
}

void Push ( int *userCount, char **head ) {
	// |name[10]|age|phone|*prev|*next|
	void *nodeNew;
	nodeNew = malloc( SIZE_NODE );

	int *dummyInt = ( int * ) ( ( char * ) nodeNew + 10 ), *i = userCount + 2;
	char *dummyChar = ( char * ) nodeNew, **dummyNode, **current, **dummyCurrent;
	dummyNode = ( char ** ) nodeNew;

	printf( "new name" );
	scanf( "%9s", dummyChar );

	printf( "new age" );
	scanf( "%d", dummyInt );
	dummyInt += 1;

	printf( "new phone" );
	scanf( "%d", dummyInt );
	dummyInt += 1; // *prev
	
	current = ( char ** ) dummyInt;
	*current = NULL; // *prev = NULL
	current += 1; // *next
	*current = NULL; // *next = NULL
	current -= 1; // *prev

	if ( *head == NULL ) {
		*head = nodeNew;
	} else {
		current = ( char ** ) *head; // current = head

		for ( *i = 0; *i < ( *userCount + 1 ); *i += 1 ) {
			dummyCurrent = current;
			if ( strcmp( dummyChar, ( char * ) current ) > 0 ) { // after
				dummyCurrent = ( char ** ) ( ( char * ) dummyCurrent + 10 );
				dummyCurrent = ( char ** ) ( ( int * ) dummyCurrent + 2 );
				dummyCurrent += 1; // *next
				if ( *dummyCurrent == NULL ) { // if current's *next = NULL
					*dummyCurrent = ( char * ) nodeNew;
					dummyNode = ( char ** ) ( ( char * ) dummyNode + 10 );
					dummyNode = ( char ** ) ( ( int * ) dummyNode + 2 ); // *prev

					*dummyNode = ( char * ) current; // node's *prev = current
					*userCount += 1;
					return; // last position case
				} else {
					current = ( char ** ) *dummyCurrent; // current = current's *next
				}

			} else if ( strcmp( dummyChar, ( char * ) current ) < 0 ) { // before
				dummyCurrent = ( char ** ) ( ( char * ) dummyCurrent + 10 );
				dummyCurrent = ( char ** ) ( ( int * ) dummyCurrent + 2 ); // *prev
				if ( *dummyCurrent == NULL ) { // if current's *prev = NULL
					*dummyCurrent = ( char * ) nodeNew;
					dummyNode = ( char ** ) ( ( char * ) dummyNode + 10 );
					dummyNode = ( char ** ) ( ( int * ) dummyNode + 2 );
					dummyNode += 1; // *next

					*dummyNode = ( char * ) current; // node's *next = current
					*head = ( char * ) nodeNew; // updates head
					*userCount += 1;
					return; // first position case
				} else {
					dummyNode = ( char ** ) ( ( char * ) dummyNode + 10 );
					dummyNode = ( char ** ) ( ( int * ) dummyNode + 2 );
					dummyNode += 1; // *next
					*dummyNode = ( char * ) current; // node's next = current

					dummyNode -= 1; // *prev
					*dummyNode = *dummyCurrent; // node's *prev = current's *prev
					*dummyCurrent = ( char * ) nodeNew; // current's *prev = node
					
					dummyCurrent = ( char ** ) *dummyNode; // node's *prev
					dummyCurrent = ( char ** ) ( ( char * ) dummyCurrent + 10 );
					dummyCurrent = ( char ** ) ( ( int * ) dummyCurrent + 2 );
					dummyCurrent += 1; // *next
					*dummyCurrent = ( char * ) nodeNew; // prev's *next = node
					*userCount += 1;
					return; // middle case
				}
			} else { // already exists
				printf( "already exists" );
				free( nodeNew );
				return;
			}
		}
	}
}

void List( int *userCount, char **head ) {
	int *dummyInt, *i = userCount + 2;
	char **current, **dummyNode;

	if ( *head == NULL ) {
		printf( "empy" );
		return;
	} else {
		current = ( char ** ) *head;
		for ( *i = 0; *i < ( *userCount + 1 ); *i += 1 ) {
			printf( "%s", ( char * ) current );
			current = ( char ** ) ( ( char * ) current + 10 );
			dummyInt = ( int * ) current;
			printf( "%d", *dummyInt );
			dummyInt += 1;
			printf( "%d", *dummyInt );
			dummyInt += 1; // *prev
			dummyNode = ( char ** ) dummyInt;
			dummyNode += 1; // *next
			current = ( char ** ) *dummyNode;
		}
	}
}