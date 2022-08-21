/*
    Faça uma agenda capaz de incluir, apagar, buscar e listar
    quantas pessoas o usuário desejar, porém, toda a informação
    incluída na agenda deve ficar num único lugar chamado: “void
    *pBuffer”.
    Não pergunte para o usuário quantas pessoas ele vai incluir.
    Não pode alocar espaço para mais pessoas do que o
    necessário.
    Cada pessoa tem nome[10], idade e telefone.
    O trabalho que vale nota será uma continuação deste.
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE_NAME ( 10 * sizeof( char ) )
#define SIZE_CONTACT ( SIZE_NAME + ( 2 * sizeof( int ) ) )

void *ContactAdd( void *pBuffer, int *userCount );
void *ContactRemove( void *pBuffer, int *userCount );
void ContactSearch( void *pBuffer, int *userCount );
void ContactList( void *pBuffer, int *userCount );

int main() {
	void *pBuffer = NULL;
	int input, userCheck = 1, userCount = 0;
	pBuffer = malloc( 1 );

	while ( userCheck == 1 ) {
        printf( "\nEscolha uma acao: \n1) Adicionar contato \n2) Remover contato \n3) Procurar \n4) Listar \n5) Sair \n" );
        scanf( "%d", &input );
        fflush( stdin );

        switch ( input ) {
            case 1:
                pBuffer = ContactAdd( pBuffer, &userCount );
                break;

            case 2:
                pBuffer = ContactRemove( pBuffer, &userCount );
                break;

            case 3:
				ContactSearch( pBuffer, &userCount );
                break;
                
            case 4:
                ContactList( pBuffer, &userCount );
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
void *ContactAdd( void *pBuffer, int *userCount ) {
	char nome[10], *pNome = NULL;
	int *idade = NULL, *telefone = NULL, teste = 0;
	void *dummy = NULL;

	pBuffer = realloc( pBuffer, ( *userCount + 1 ) * SIZE_CONTACT );
	dummy = pBuffer;

	pBuffer += *userCount * SIZE_CONTACT;
	pNome = pBuffer;
	idade = pBuffer + SIZE_NAME;
	telefone = pBuffer + SIZE_NAME + sizeof( int );
	pBuffer = dummy;

	printf( "Digite o nome a ser adicionado: " );
    scanf( "%9s", nome );
    fflush( stdin );

	for ( int i = 0; i < 10; i++ ) {
		*pNome = nome[i];
		if ( nome[i] == '\0' ) {
			break;
		}
		pNome++;
	}

	do {
		printf( "Digite a idade: " );
		scanf( "%d", idade );
		fflush( stdin );
	
		if ( *idade > 999 ) { 
			printf( "Numero invalido.\n" );
			teste = 1;
		} else {
			teste = 0;
		}
	} while ( teste == 1 );
	teste = 0;

	do {
		printf( "Digite o telefone: " );
		scanf( "%d", telefone );
		fflush( stdin );
		
		if ( *telefone > 999999999 ) { 
			printf( "Numero invalido.\n" );
			teste = 1;
		} else {
			teste = 0;
		}
	} while ( teste == 1 );

	*userCount += 1;
	return ( pBuffer );
}

/*
====================
ContactRemove
 Removes name from the list string
====================
*/
void *ContactRemove( void *pBuffer, int *userCount ) {
	if ( *userCount == 0 ) {
		printf( "Nenhum contato no sistema.\n" );
		return pBuffer;
	}

	char nome[10], *pNome = NULL, *nomeTemp = NULL;
	int *idade = NULL, *telefone = NULL, *idadeTemp = NULL, *telefoneTemp = NULL, test = 0;
	void *dummy = NULL;

	dummy = pBuffer;

	printf( "Digite o nome a ser removido: " );
    scanf( "%9s", nome );
    fflush( stdin );

	for ( int i = 0; i < *userCount; i++ ) {
		pNome = pBuffer + ( i * SIZE_CONTACT );

		for ( int j = 0; j < 10; j++ ) {
			if ( *pNome != nome[j] ) {
				break;
			} else if ( nome[j] == '\0' ) {
				test = 1;
				break;
			}
			pNome++;
		}

		if ( test == 1 ) {
			if ( i != *userCount - 1 ) {
				pBuffer += ( i * SIZE_CONTACT );

				for ( int j = 0; j < *userCount - i - 1; j++ ) {
					pNome = pBuffer;
					idade = pBuffer + SIZE_NAME;
					telefone = idade + 1;

					pBuffer += SIZE_CONTACT;

					for ( int k = 0; k < 10; k++ ) {
						nomeTemp = pBuffer + ( k * sizeof( char ) );
						*pNome = *nomeTemp;
						pNome++;
					}

					idadeTemp = pBuffer + SIZE_NAME;
					*idade = *idadeTemp;
					telefoneTemp = idadeTemp + 1;
					*telefone = *telefoneTemp;
				}
			}

			pBuffer = dummy;
			pBuffer = realloc( pBuffer, ( *userCount * SIZE_CONTACT ) - SIZE_CONTACT );
			*userCount -= 1;
			return ( pBuffer );
		}
	}

	printf( "Contato nao encontrado.\n" );
	return ( pBuffer );
}

/*
====================
ContactSearch
 Searches for a specific contact
====================
*/
void ContactSearch( void *pBuffer, int *userCount ) {
	if ( *userCount == 0 ) {
		printf( "Nenhum contato no sistema.\n" );
		return;
	}

	char nome[10], *pNome = NULL;
	int *idade = NULL, *telefone = NULL, test = 0;

	printf( "Digite sua busca: " );
    scanf( "%9s", nome );
    fflush( stdin );

	for ( int i = 0; i < *userCount; i++ ) {
		pNome = pBuffer + ( i * SIZE_CONTACT );

		for ( int j = 0; j < 10; j++ ) {
			if ( *pNome != nome[j] ) {
				break;
			} else if ( nome[j] == '\0' ) {
				test = 1;
				break;
			}
			pNome++;
		}

		if ( test == 1 ) {
			pNome = pBuffer + ( i * SIZE_CONTACT );
			printf( "%s, ", pNome );

			idade = pBuffer + ( i * SIZE_CONTACT ) + SIZE_NAME;
			printf( "%d anos ", *idade );

			telefone = idade + 1;
			printf( "- telefone: %d\n", *telefone );

			return;
		}
	}

	printf( "Contato nao encontrado.\n" );
	return;
}

/*
====================
ContactList
 Lists all contacts
====================
*/
void ContactList( void *pBuffer, int *userCount ) {
	if ( *userCount == 0 ) {
		printf( "Nenhum contato no sistema.\n" );
		return;
	}

	char *pNome = NULL;
	int *idade = NULL, *telefone = NULL;

	for ( int i = 0; i < *userCount; i++ ) {
		pNome = pBuffer + ( i * SIZE_CONTACT );
		printf( "<%d> %s, ", i + 1, pNome );

		idade = pBuffer + ( i * SIZE_CONTACT ) + SIZE_NAME;
		printf( "%d anos ", *idade );

		telefone = idade + 1;
		printf( "- telefone: %d\n", *telefone );
	}
	return;
}