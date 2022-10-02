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

#define SIZE_BUFFER ( ( 3 * sizeof( int ) ) + ( sizeof( char * ) ) + ( 10 * sizeof( char ) ) )
#define SIZE_NODE ( ( 10 * sizeof( char ) ) + ( 2 * sizeof( int ) ) + ( 2 * sizeof( char * ) ) )

void PrintContact( char **current );
void List( int *userCount, char **head );
char **Search( int *userCount, char **head, char *nameSearch );
void Push( int *userCount, char **head );
void Pop( int *userCount, char **head, char *nameSearch );
void Clear( int *userCount, char **head );

int main() {
	// buffer
	// |count|input|i|*head|nameSearch[10]|
	// node
	// |name[10]|age|phone|*prev|*next|

	void *pBuffer;
	pBuffer = malloc( SIZE_BUFFER );

	int *userCount = ( int * ) pBuffer, *input = userCount + 1;
	*userCount = 0;
	*input = 0;

	char **head = ( char ** ) ( input + 2 ), *nameSearch = ( char * ) ( head + 1 );
	*head = NULL;

	do {
		printf( "1)Adicionar contato \n2)Remover contato \n3)Listar \n4)Procurar \n0)Sair \n" );
		scanf( "%d", input );
		fflush( stdin );

		switch ( *input ) {
		case 1:
			Push( userCount, head );
			break;

		case 2:
			printf( "Digite o nome a ser removido: " );
			scanf( "%9s", nameSearch );
			fflush( stdin );
			Pop( userCount, head, nameSearch );
			break;

		case 3:
			List( userCount, head );
			break;

		case 4:
			printf( "Digite sua busca: " );
			scanf( "%9s", nameSearch );
			fflush( stdin );
			PrintContact( Search( userCount, head, nameSearch ) );
			break;

		case 0:
			Clear( userCount, head );
			free( pBuffer );
			return ( 0 );

		default:
			printf( "Digite uma opcao valida. \n" );
			break;
		}
	} while ( 1 );
}

void PrintContact( char **current ) {
	int *dummyInt;

	if ( current == NULL ) {
		return;
	}

	printf( "%s, ", ( char * ) current );

	current = ( char ** ) ( ( char * ) current + 10 );
	dummyInt = ( int * ) current;
	printf( "%d anos - ", *dummyInt );

	dummyInt += 1;
	printf( "telefone: %d \n", *dummyInt );
}

void List( int *userCount, char **head ) {
	int *i = userCount + 2;
	char **current;

	if ( *head == NULL ) {
		printf( "A lista esta vazia. \n" );
		return;
	} else {
		current = ( char ** ) *head;

		for ( *i = 0; *i < *userCount; *i += 1 ) {
			printf( "<%d> ", *i + 1 );
			PrintContact( current );

			current = ( char ** ) ( ( char * ) current + 10 );
			current = ( char ** ) ( ( int * ) current + 2 );
			current += 1; // *next
			current = ( char ** ) *current; // current = *next
		}
	}
}

char **Search( int *userCount, char **head, char *nameSearch ) {
	int *i = userCount + 2;
	char **current;

	if ( *head == NULL ) {
		printf( "A lista esta vazia. \n" );
		return ( NULL );
	} else {
		current = ( char ** ) *head;

		for ( *i = 0; *i < *userCount; *i += 1 ) {
			if ( strcmp( nameSearch, ( char * ) current ) == 0 ) {
				return ( current );
			} else {
				current = ( char ** ) ( ( char * ) current + 10 );
				current = ( char ** ) ( ( int * ) current + 2 );
				current += 1; // *next
				current = ( char ** ) *current; // current = *next
			}
		}
		
		printf( "Usario nao encontrado. \n" );
		return ( NULL );
	}
}

void Push ( int *userCount, char **head ) {
	void *nodeNew;
	nodeNew = malloc( SIZE_NODE );

	int *dummyInt = ( int * ) ( ( char * ) nodeNew + 10 ), *i = userCount + 2;
	char *dummyChar = ( char * ) nodeNew, **dummyNode, **current, **dummyCurrent;
	dummyNode = ( char ** ) nodeNew;

	printf( "Digite o nome a ser adicionado: " );
	scanf( "%9s", dummyChar );
	fflush( stdin );

	printf( "Digite a idade: " );
	scanf( "%d", dummyInt );
	fflush( stdin );
	dummyInt += 1;

	printf( "Digite o numero de telefone: " );
	scanf( "%d", dummyInt );
	fflush( stdin );
	dummyInt += 1; // *prev
	
	current = ( char ** ) dummyInt;
	*current = NULL; // *prev = NULL
	current += 1; // *next
	*current = NULL; // *next = NULL
	current -= 1; // *prev

	if ( *head == NULL ) {
		*head = nodeNew;
	} else {
		current = ( char ** ) *head;

		for ( *i = 0; *i < *userCount; *i += 1 ) {
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
					break; // last position case
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
					break; // first position case
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
					break; // middle case
				}

			} else { // already exists
				printf( "Este nome ja existe. \n" );
				free( nodeNew );
				return;
			}
		}
	}
	*userCount += 1;
}

void Pop( int *userCount, char **head, char *nameSearch ) {
	char **current = Search( userCount, head, nameSearch ), **dummyCurrent = current, **prev, **next;

	if ( current != NULL ) {
		dummyCurrent = ( char ** ) ( ( char * ) dummyCurrent + 10 );
		dummyCurrent = ( char ** ) ( ( int * ) dummyCurrent + 2 ); // *prev

		if ( *dummyCurrent == NULL ) {
			prev = NULL;
		} else {
			prev = ( char ** ) *dummyCurrent;
		}
		dummyCurrent += 1; // *next

		if ( *dummyCurrent == NULL ) {
			next = NULL;
		} else {
			next = ( char ** ) *dummyCurrent;
		}

		if ( prev != NULL && next != NULL ) {
			prev = ( char ** ) ( ( char * ) prev + 10 );
			prev = ( char ** ) ( ( int * ) prev + 2 );
			prev += 1; // *next
			*prev = ( char * ) next;

			prev = ( char ** ) ( ( char * ) prev - 10 );
			prev = ( char ** ) ( ( int * ) prev - 2 );
			prev -= 1; // sets back to its starting position

			next = ( char ** ) ( ( char * ) next + 10 );
			next = ( char ** ) ( ( int * ) next + 2 ); // *prev
			*next = ( char * ) prev;

		} else if ( prev != NULL && next == NULL ) {
			prev = ( char ** ) ( ( char * ) prev + 10 );
			prev = ( char ** ) ( ( int * ) prev + 2 );
			prev += 1; // *next
			*prev = NULL;

		} else if ( prev == NULL && next != NULL ) {
			next = ( char ** ) ( ( char * ) next + 10 );
			next = ( char ** ) ( ( int * ) next + 2 ); // *prev
			*next = NULL;

			next = ( char ** ) ( ( char * ) next - 10 );
			next = ( char ** ) ( ( int * ) next - 2 );
			*head = ( char * ) next; // sets back to its starting position

		} else {
			*head = NULL;
		}
		free( current );
		*userCount -= 1;

	} else {
		return;
	}
}

void Clear( int *userCount, char **head ) {
	char **current, **dummyCurrent;
	int *i = userCount + 2;

	if ( *head == NULL ) {
		return;
	} else {
		current = ( char ** ) *head;
		dummyCurrent = current;

		for ( *i = 0; *i < ( *userCount - 1 ); *i += 1 ) {
			dummyCurrent = ( char ** ) ( ( char * ) dummyCurrent + 10 );
			dummyCurrent = ( char ** ) ( ( int * ) dummyCurrent + 2 );
			dummyCurrent += 1; // *next

			dummyCurrent = ( char ** ) *dummyCurrent;
			free( current );
			current = dummyCurrent;
		}
		free( current );
	}
}