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

#define SIZE_BUFFER ( ( 5 * sizeof( int ) ) + ( 10 * sizeof( char ) ) + ( 3 * sizeof( char * ) ) )
#define SIZE_NODE ( ( 10 * sizeof( char ) ) + ( 2 * sizeof( int ) ) + ( 2 * sizeof( char * ) ) )

	// buffer
	// |count|input|test|test2|i|name[10]|*head|*dum1|*dum2|
	// 0     1     2    3     4 5							 * int        
	// 							      + 10					 * char
	//										 + 1	 2     3 * char*

	// node
	// |name[10]|age|phone|*prev|*next|
	// 0        10						  * char
	//			  + 1     2 			  * int
	//						   + 1      2 * char*

void Push( int *userCount );
void Pop( int *userCount );
void PopAll( int *userCount );
void ContactSearch( int *userCount );
void ContactList( int *userCount );


int main() {
	// buffer
	// |count|input|test|test2|i|name[10]|*head|*dum1|*dum2|*dum3|
	// 0     1     2    3     4 5							 	   * int        
	// 							      + 10					 	   * char
	//										 + 1	 2     3     4 * char*

	// node
	// |name[10]|age|phone|*prev|*next|
	// 0        10						  * char
	//			  + 1     2 			  * int
	//						   + 1    2 * char*

	void *pBuffer;
	pBuffer = malloc( SIZE_BUFFER );

	int *userCount = pBuffer, *input = userCount + 1;
	*userCount = 0;
	*input = 0;

	char **head = ( char ** ) ( userCount + 5 ), **dummy, **dummyHelper, **dummyHelper2;
	head = ( char ** ) ( ( char * ) head + 10 );
	dummy = head + 1;
	dummyHelper = dummy + 1;
	dummyHelper2 = dummyHelper + 1;

	// set pointers to null
	*head = NULL;
	*dummy = NULL;	
	*dummyHelper = NULL;
	*dummyHelper2 = NULL;
	
	while ( 1 ) {
        printf( "\nEscolha uma acao: \n1) Adicionar contato \n2) Remover contato \n3) Procurar \n4) Listar \n5) Sair \n" );
        scanf( "%d", input );
        fflush( stdin );

        switch ( *input ) {
            case 1:
                Push( userCount );
                break;

            case 2:
                Pop( userCount );
                break;

            case 3:
				ContactSearch( userCount );
                break;
                
            case 4:
                ContactList( userCount );
                break;                
            
            case 5:
				PopAll( userCount );
                free( pBuffer );
                return ( 0 );
            
            default:
                printf( "Digite uma opcao valida. \n" );
                break;

        }
    }
}

/*
====================
Push
 Adds a new contact
====================
*/
void Push( int *userCount ) {
	// buffer
	// |count|input|test|test2|i|name[10]|*head|*dum1|*dum2|
	// 0     1     2    3     4 5							 * int        
	// 							      + 10					 * char
	//										 + 1	 2     3 * char*

	// node
	// |name[10]|age|phone|*prev|*next|
	// 0        10						  * char
	//			  + 1     2 			  * int
	//						   + 1    2 * char*
	
	if ( *userCount == 10 ) {	// full case
		printf( "Lista cheia. \n" );
		return;
	}

	int *i = userCount + 4;
	char *name = ( char * ) ( i + 1 ), **head = ( char ** ) ( userCount + 5 ), *node, **dummy, **dummyHelper;
	head = ( char ** ) ( ( char * ) head + 10 );
	dummy = head + 1;
	dummyHelper = dummy + 1;

	// setup new node
	node = ( char * ) malloc( SIZE_NODE );
	*dummy = node;

	printf( "Digite o nome a ser adicionado: " );
    scanf( "%9s", name );	// swap w fgets for spaces
    fflush( stdin );

	name += 9; // char
	*name = '\0'; // just to be safe
	name -= 9; // char

	**dummy = *name;
	*dummy += 10; // char

	printf( "Digite a idade: " );
	scanf( "%d", ( int * ) *dummy );
	fflush( stdin );

	*dummy = ( char * ) ( ( int * ) *dummy + 1 );

	printf( "Digite o telefone: " );
	scanf( "%d", ( int * ) *dummy );
	fflush( stdin );

	// transfer new node to list
	if ( *userCount > 0 ) {	// middle case
		dummy = ( char ** ) *head;

		// alphabetical sorting
		for ( *i = 0; *i < *userCount; *i += 1 ) {
			if ( strcmp( name, *dummy ) > 0 ) {	// if it should be after
				dummy = ( char ** ) ( ( char * ) dummy + 10 );
				dummy = ( char ** ) ( ( int * ) dummy + 2 );
				dummy += 1;	// *next
				if ( *dummy != NULL ) {	// if there is a next node
					*dummyHelper = *dummy;
					dummy = ( char ** ) *dummyHelper;	// next is the current node
				} else {
					*dummy = node;	// else next is the new node
				}
			} else {	// if it should be before
				dummy = ( char ** ) ( ( char * ) dummy + 10 );
				dummy = ( char ** ) ( ( int * ) dummy + 2 ); // *prev
				if ( *dummy != NULL ) {
					// set prev's next as current
					dummyHelper = ( char ** ) *dummy;
					dummyHelper = ( char ** ) ( ( char * ) dummyHelper + 10 );
					dummyHelper = ( char ** ) ( ( int * ) dummyHelper + 2 );
					dummyHelper = ( char ** ) ( ( char ** ) dummyHelper + 1 );	// *next
					*dummyHelper = node;
				}

				dummy = ( char ** ) ( ( char * ) dummy + 1 );
				if ( *dummy != NULL ) {
					// set next's prev as current
					dummyHelper = ( char ** ) *dummy;
					dummyHelper = ( char ** ) ( ( char * ) dummyHelper + 10 );
					dummyHelper = ( char ** ) ( ( int * ) dummyHelper + 2 );
					*dummyHelper = node;
				}
			}
		}

	} else {	// empty case
		// set new node as head
		*head = node;

		// set prev and next to null
		dummy = ( char ** ) node;
		dummy = ( char ** ) ( ( char * ) dummy + 10 );
		dummy = ( char **) ( ( int * ) dummy + 2 );	// *prev
		*dummy = NULL;
		dummy += 1;	// *next
		*dummy = NULL;
	}

	*userCount += 1;
	return;
}

/*
====================
Pop
 Removes a given contact
====================
*/
void Pop( int *userCount ) {
	// buffer
	// |count|input|test|test2|i|name[10]|*head|*dum1|*dum2|
	// 0     1     2    3     4 5							 * int        
	// 							      + 10					 * char
	//										 + 1	 2     3 * char*

	// node
	// |name[10]|age|phone|*prev|*next|
	// 0        10						  * char
	//			  + 1     2 			  * int
	//						   + 1    2 * char*

	if ( *userCount == 0 ) {	// empty case
		printf( "Nenhum contato no sistema. \n" );
		return;
	}

	int *test = userCount + 2, *holder = test + 1, *i = test + 2;
	*test = 1;

	char *name = ( char * ) ( i + 1 ), **head = ( char ** ) ( userCount + 5 ), *node, **dummy, **dummyHelper, **dummyHelper2;
	head = ( char ** ) ( ( char * ) head + 10 );
	dummy = head + 1;
	dummyHelper = dummy + 1;
	dummyHelper2 = dummyHelper + 1;

	printf( "Digite o nome a ser removido: " );
    scanf( "%9s", name );	// swap w fgets for spaces
    fflush( stdin );

	name += 9;
	*name = '\0'; // just to be safe
	name -= 9;

	dummy = ( char ** ) *head;

	// removal
	for ( *i = 0; *i < *userCount; *i += 1 ) {
		if ( strcmp( name, *dummy ) == 0 ) {	// if current node = input
			node = ( char * ) dummy;
			*test = 0;
			break;
		}	// else try next node
		dummy = ( char ** ) ( ( char * ) dummy + 10 );
		dummy = ( char ** ) ( ( int * ) dummy + 2 );
		dummy += 1;	// *next
		if ( *dummy != NULL ) {	// just to be safe
			dummyHelper = ( char ** ) *dummy; // maybe there's no need for the helper?
			dummy = dummyHelper;
		}
	}

	if ( *test == 0 ) { // if successful in finding name
		dummy = ( char ** ) ( ( char * ) dummy + 10 );
		dummy = ( char ** ) ( ( int * ) dummy + 2 ); // *prev

		dummyHelper = dummy + 1; // *next
		if ( *dummy != NULL && *dummyHelper != NULL ) { // middle case
			// set prev's next as next
			dummyHelper2 = ( char ** ) *dummy; // 2 to prev
			dummy = dummyHelper2;
			dummy = ( char ** ) ( ( char * ) dummy + 10 );
			dummy = ( char ** ) ( ( int * ) dummy + 2 );
			dummy += 1; // *next
			*dummy = *dummyHelper;
			
			// set next's prev as prev
			dummy = ( char ** ) *dummyHelper; // 0 to next
			dummy = ( char ** ) ( ( char * ) dummy + 10 );
			dummy = ( char ** ) ( ( int * ) dummy + 2 ); // *prev
			*dummy = dummyHelper2;
		} else if ( *dummy == NULL && *dummyHelper != NULL ) { // first case
			// set next as head
			dummy = *dummyHelper;
			*head = dummy;

			// set next's prev as NULL
			dummy = ( char ** ) ( ( char * ) dummy + 10 );
			dummy = ( char ** ) ( ( int * ) dummy + 2 ); // *prev
			*dummy = NULL;
		} else if ( *dummy != NULL && *dummyHelper == NULL ) { // last case
			// set prev's next as NULL
			dummyHelper = *dummy; // 1 to prev
			dummyHelper = ( char ** ) ( ( char * ) dummyHelper + 10 );
			dummyHelper = ( char ** ) ( ( int * ) dummyHelper + 2 );
			dummyHelper += 1; // *next
			*dummyHelper = NULL;
		} else if ( *dummy == NULL && *dummyHelper == NULL ) { // single case
			*head = NULL;
		}
		free( node );
		*userCount -= 1;
	} else {
		printf( "Usuario nao encontrado. \n" );
	}
	return;
}

/*
====================
PopAll
 Removes all contacts; serves as a full free()
====================
*/
void PopAll( int *userCount ) {
	// |count|input|test|test2|i|name[10]|*head|
	// 0     1     2    3     4 5					* int        
	// 							      + 10 	  11	* char 

	// |name[10]|age|phone|*prev|*next|
	// 0        10						* char
	//			  + 1     2 			* int
	//						  + 1     2 * char

	if ( *userCount == 0 ) {	// empty case
		return;
	}

	int *i = userCount + 4;
	char *head = userCount, *node, *dummy, *dummyHelper;
	( int * ) head += 5;
	head += 10; // char
	dummy = *head;

	for ( *i = 0; *i < *userCount; *i += 1 ) {
		node = dummy;
		dummy += 11; // char
		( int * ) dummy += 2;
		if ( *dummy != NULL ) {	// if there are more nodes
			dummyHelper = *dummy;
			dummy = dummyHelper;
		}
		free( node );
	}
}

/*
====================
ContactSearch
 Searches for a specific contact
====================
*/
void ContactSearch( int *userCount ) {
	// |count|input|test|test2|i|name[10]|*head|
	// 0     1     2    3     4 5					* int        
	// 							      + 10 	  11	* char 

	// |name[10]|age|phone|*prev|*next|
	// 0        10						* char
	//			  + 1     2 			* int
	//						  + 1     2 * char


	if ( *userCount == 0 ) {
		printf( "Nenhum contato no sistema. \n" );
		return;
	}

	int *test = userCount + 2, *test2 = test + 1, *i = test + 2;
	*test = 0;
	*test2 = 1;

	char *name = ( char * ) i + sizeof( int ), *head = userCount, *node, *dummy;
	( int * ) head += 5;
	head += 10; // char
	node = *head;
	dummy = node;

	printf( "Digite a sua busca: " );
    scanf( "%9s", name );	// swap w fgets for spaces
    fflush( stdin );

	name += 9;
	*name = '\0'; // just to be safe
	name -= 9;

	for ( *i = 0; *i < *userCount; *i += 1 ) {
		if ( strcmp( name, *node ) == 0 ) {
				*test = 1;
				*test2 = 0;
			}

		if ( *test == 1 ) {
			printf( "<%d> %s, ", *i + 1, *dummy );
			dummy += 10; // char
			printf( "%d anos ", *dummy );
			( int * ) dummy += 1;
			printf( "- telefone: %d \n", *dummy );
			( int * ) dummy += 1;
			dummy += 1; // char
			if ( *dummy != NULL ) {
				node = *dummy;
				dummy = node;
			}
			*test = 0;
		}
	}

	if ( *test2 == 1 ) {
		printf( "Contato nao encontrado. \n" );
	}

	return;
}

/*
====================
ContactList
 Lists all contacts
====================
*/
void ContactList( int *userCount ) {
	// |count|input|test|test2|i|name[10]|*head|
	// 0     1     2    3     4 5					* int        
	// 							      + 10 	  11	* char 

	// |name[10]|age|phone|*prev|*next|
	// 0        10						* char
	//			  + 1     2 			* int
	//						  + 1     2 * char

	if ( *userCount == 0 ) {
		printf( "Nenhum contato no sistema. \n" );
		return;
	}

	int *i = userCount + 5;
	char *head = userCount, *node, *dummy;
	( int * ) head += 5;
	head += 10; // char
	node = *head;
	dummy = node;

	for ( *i = 0; *i < *userCount; *i += 1 ) {
		printf( "<%d> %s, ", *i + 1, *dummy );
		dummy += 10; // char
		printf( "%d anos ", *dummy );
		( int * ) dummy += 1;
		printf( "- telefone: %d \n", *dummy );
		( int * ) dummy += 1;
		dummy += 1; // char
		if ( *dummy != NULL ) {
			node = *dummy;
			dummy = node;
		}
	}

	return;
}