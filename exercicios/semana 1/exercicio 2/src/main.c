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

#define MAX_NAME_SIZE 20

void NameAdd( char *list );
void NameRemove( char *list );

int main() {
    int input, userCheck = 1;
    char *list;
    list = ( char * ) calloc( 1, sizeof( char ) );    // because calloc takes out the garbage

    while ( userCheck == 1 ) {
        printf( "\nEscolha uma acao: \n1) Adicionar nome \n2) Remover nome \n3) Listar \n4) Sair \n" );
        scanf( "%d", &input );
        fflush( stdin );

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
    char name[MAX_NAME_SIZE + 2] = ">", nameTemp[MAX_NAME_SIZE + 1];

    printf( "Digite o nome a ser adicionado: " );
    scanf("%20s", nameTemp);
    fflush( stdin );
    if ( strlen( nameTemp ) == 1 ) {
        printf( "Digite um nome valido.\n" );
        return;
    }
    strcat( nameTemp, "\n" );
    strcat( name, nameTemp );

    int size = strlen( list ) + strlen( name );

    list = ( char * ) realloc( list, ( size + 1 ) * sizeof( char ) );

    strcat( list, name );

    return;
}

/*
====================
NameRemove
 Removes name from the list string
====================
*/
void NameRemove( char *list ) {
    char name[MAX_NAME_SIZE + 2] = ">", nameTemp[MAX_NAME_SIZE + 1], *namePosition, *nameEnd;

    printf( "Digite o nome a ser removido: " );
    scanf("%20s", nameTemp);
    fflush( stdin );
    if ( strlen( nameTemp ) == 1 ) {
        printf( "Digite um nome valido.\n" );
        return;
    }
    strcat( nameTemp, "\n" );
    strcat( name, nameTemp );

    namePosition = strstr( list, name );
    if ( namePosition != NULL ) {
        nameEnd = namePosition + strlen( name );

        memmove( namePosition, nameEnd, strlen( nameEnd ) + 1 );

        list = ( char * ) realloc( list, ( strlen( list ) + 1 ) * sizeof( char ) );

        return;
    } else {
        printf( "Nome nao listado.\n" );
        return;
    }
}