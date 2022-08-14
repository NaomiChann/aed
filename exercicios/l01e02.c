/*
    Faça um programa que armazena nomes.
    O programa deve armazenar todos os nomes na mesma string
    O tamanho da string deve crescer e diminuir conforme nomes forem colocados ou removidos.
    Não pode ter desperdício de memória.
    Faça o seguinte menu:
    1) Adicionar nome
    2) Remover nome
    3) Listar
    4) Sair
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME_SIZE 21

void NameAdd( char *list );
void NameRemove( char *list );

int main() {
    int input, userCheck = 1;
    char *list = ( char * ) calloc( 1, sizeof( char ) );    // because calloc takes out the garbage

    while ( userCheck == 1 ) {
        printf( "\nEscolha uma acao: \n1) Adicionar nome \n2) Remover nome \n3) Listar \n4) Sair \n" );
        scanf( "%d", &input );
        getc( stdin );

        switch ( input ) {
            case 1:
                NameAdd( list );
                break;

            case 2:
                NameRemove( list );
                break;

            case 3:
                printf( "%s", list );
                break;

            case 4:
                userCheck = 0;
                free( list );
                break;
            
            default:
                printf( "Digite uma opcao valida.\n" );
                break;
        }
    }

    return 0;
}

/*
====================
NameAdd
 Adds name to the list string
====================
*/
void NameAdd( char *list ) {
    char name[MAX_NAME_SIZE], *newLine;

    printf( "Digite o nome a ser adicionado: " );
    fgets( name, MAX_NAME_SIZE, stdin );
    newLine = strchr( name, '\n' );

    if ( newLine == NULL ) {
        while ( getc( stdin ) != '\n' ) {
            // nothing
        }
        strcat( name, "\n" );
    } else if ( strlen( name ) < 2 ) {
        printf( "Digite um nome valido.\n" );
        return;
    }

    list = ( char * ) realloc( list, ( strlen( list ) + strlen( name ) + 1 ) * sizeof( char ));

    strcat( list, name );
}

/*
====================
NameRemove
 Removes name from the list string
====================
*/
void NameRemove( char *list ) {
    char name[MAX_NAME_SIZE], *newLine, *namePosition, *nameEnd;

    printf( "Digite o nome a ser removido: " );
    fgets( name, MAX_NAME_SIZE, stdin );
    newLine = strchr( name, '\n' );

    if ( newLine == NULL ) {
        while ( getc( stdin ) != '\n' ) {
            // nothing
        }
        strcat( name, "\n" );
    } else if ( strlen( name ) < 2 ) {
        printf( "Digite um nome valido.\n" );
        return;
    }

    namePosition = strstr( list, name );
    nameEnd = namePosition + strlen( name );

    for (int i = 0; i < ( ( list + strlen( list ) ) - ( nameEnd + strlen( nameEnd ) ) ); i++) {
        namePosition[i] = nameEnd[i];
    }

    list = ( char * ) realloc( list, ( strlen( list ) + 1 ) * sizeof( char ) );
}