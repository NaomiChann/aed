/*
	1.O programa deve armazenar no máximo 10 pessoas

	2.Todas as variáveis que forem usadas no programa deve ser ponteiros. A única exceção é o
	item 1 que deve ser uma variável global
	Pessoa pessoas[10].

	1.Os ponteiros devem apontar para um buffer chamado
	pBuffer onde os dados devem ser armazenados. Por exemplo,
	um contador para um for deve ser um ponteiro para int
	e o int vai ficar armazenado dentro de pBuffer

	2.Não pode usar struct dentro do pBuffer

	3.Como sempre, entregar o código e o vídeo explicando o código, mostrando casos de
	teste e o resultado do DrMemory
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char nome[10];
	int idade;
	int telefone;
} Pessoa;

Pessoa pessoas[10];

void ContactAdd( int *userCount );
void ContactRemove( int *userCount );
void ContactSearch( int *userCount );
void ContactList( int *userCount );


int main() {
	void *pBuffer;

	// |count|input|test|test2|i|name[10]|
	pBuffer = malloc( ( 5 * sizeof( int ) ) + ( 10 * sizeof( char ) ) );

	int *userCount = pBuffer, *input = userCount + 1;

	*userCount = 0;
	*input = 0;

	while ( 1 ) {
        printf( "\nEscolha uma acao: \n1) Adicionar contato \n2) Remover contato \n3) Procurar \n4) Listar \n5) Sair \n" );
        scanf( "%d", input );
        fflush( stdin );

        switch ( *input ) {
            case 1:
                ContactAdd( userCount );
                break;

            case 2:
                ContactRemove( userCount );
                break;

            case 3:
				ContactSearch( userCount );
                break;
                
            case 4:
                ContactList( userCount );
                break;                
            
            case 5:
                free( pBuffer );
                return ( 0 );
            
            default:
                printf( "Digite uma opcao valida.\n" );
                break;

        }
    }
}

/*
====================
ContactAdd
 Adds name to the list string
====================
*/
void ContactAdd( int *userCount ) {
	if ( *userCount == 10 ) {
		printf( "Lista cheia.\n" );
		return;
	}
	
	int *test = userCount + 2;
	printf( "Digite o nome a ser adicionado: " );
    scanf( "%9s", pessoas[*userCount].nome );
    fflush( stdin );

	do {
		printf( "Digite a idade: " );
		scanf( "%d", &pessoas[*userCount].idade );
		fflush( stdin );
	
		if ( pessoas[*userCount].idade > 999 ) { 
			printf( "Numero invalido.\n" );
			*test = 1;
		} else {
			*test = 0;
		}
	} while ( *test == 1 );

	do {
		printf( "Digite o telefone: " );
		scanf( "%d", &pessoas[*userCount].telefone );
		fflush( stdin );
		
		if ( pessoas[*userCount].telefone > 999999999 ) { 
			printf( "Numero invalido.\n" );
			*test = 1;
		} else {
			*test = 0;
		}
	} while ( *test == 1 );

	*userCount += 1;
	return;
}

/*
====================
ContactRemove
 Removes name from the list string
====================
*/
void ContactRemove( int *userCount ) {
	if ( *userCount == 0 ) {
		printf( "Nenhum contato no sistema.\n" );
		return;
	}

	int *test = userCount + 2, *holder = test + 1, *i = test + 2;
	char *name = ( char * ) i + sizeof( int );
	*test = 1;

	printf( "Digite o nome a ser removido: " );
    scanf( "%9s", name );
    fflush( stdin );

	name += 9;
	*name = '\0'; // just to be safe
	name -= 9;

	for ( *i = 0; *i < *userCount; *i += 1 ) {
		if ( strcmp( name, pessoas[*i].nome ) == 0 ) {
			*test = 0;
			break;
		}
	}

	for ( *i = *i; *i < *userCount; *i += 1 ) {
		if ( *test == 0 ) {
			if ( *i < *userCount - 1 ) {
				name = pessoas[*i].nome;
				*name = *pessoas[*i + 1].nome;
				holder = &pessoas[*i].idade;
				*holder = pessoas[*i + 1].idade;
				holder = &pessoas[*i].telefone;
				*holder = pessoas[*i + 1].telefone;
			} else {
				name = pessoas[*i].nome;
				*name = '\0';
				holder = &pessoas[*i].idade;
				*holder = 0;
				holder = &pessoas[*i].telefone;
				*holder = 0;
			}
		}
	}
	if ( *test == 1 ) {
		printf( "Usuario nao encontrado\n" );	
		return;
	} else {
		*userCount -= 1;
		return;
	}
}

/*
====================
ContactSearch
 Searches for a specific contact
====================
*/
void ContactSearch( int *userCount ) {
	if ( *userCount == 0 ) {
		printf( "Nenhum contato no sistema.\n" );
		return;
	}

	int *test = userCount + 2, *test2 = test + 1, *i = test + 2;
	char *name = ( char * ) i + sizeof( int );
	*test = 0;
	*test2 = 1;

	printf( "Digite a sua busca: " );
    scanf( "%9s", name );
    fflush( stdin );

	name += 9;
	*name = '\0'; // just to be safe
	name -= 9;


	for ( *i = 0; *i < *userCount; *i += 1 ) {
		if ( strcmp( name, pessoas[*i].nome ) == 0 ) {
				*test = 1;
				*test2 = 0;
			}

		if ( *test == 1 ) {
			printf( "<%d> %s, ", *i + 1, pessoas[*i].nome );
			printf( "%d anos ", pessoas[*i].idade );
			printf( "- telefone: %d\n", pessoas[*i].telefone );
			*test = 0;
		}
	}

	if ( *test2 == 1 ) {
		printf( "Contato nao encontrado.\n" );
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
	if ( *userCount == 0 ) {
		printf( "Nenhum contato no sistema.\n" );
		return;
	}

	int *i = userCount + 5;

	for ( *i = 0; *i < *userCount; *i += 1 ) {
		printf( "<%d> %s, ", *i + 1, pessoas[*i].nome );
		printf( "%d anos ", pessoas[*i].idade );
		printf( "- telefone: %d\n", pessoas[*i].telefone );
	}

	return;
}