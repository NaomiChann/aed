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

#define MAX_NAME_SIZE 22

char* NameAdd( char *list );
void NameRemove();

int main() {
    int input, userCheck = 1;
    char *list;
    list = ( char * ) malloc( sizeof(char) );
    list[0] = '\0';

    while ( userCheck == 1 ) {
        printf( "1) Adicionar nome \n2) Remover nome \n3) Listar \n4) Sair \n" );
        scanf( "%d", &input );
        getc(stdin);

        switch ( input ) {
            case 1:
                NameAdd( list );
                break;

            case 2:
                NameRemove();
                break;

            case 3:
                printf( "%s", list );
                break;

            case 4:
                userCheck = 0;
                free( list );
                break;
            
            default:
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
char* NameAdd( char *list ) {
    char name[MAX_NAME_SIZE], newLine[2] = "\n";

    printf( "Digite o nome a ser adicionado: " );
    fgets( name, MAX_NAME_SIZE - 1, stdin );
    fflush( stdin );

    if ( strchr( name, '\n' ) == NULL ) {
        strcat( name, newLine );
    }

    list = ( char * ) realloc( list, ( strlen( list ) + strlen( name ) + 1 ) * sizeof( char ));

    strcat( list, name );

    return list;
}

/*
====================
NameRemove
 Removes name from the list string
====================
*/
void NameRemove() {
    printf( "Digite o nome a ser removido: " );

}