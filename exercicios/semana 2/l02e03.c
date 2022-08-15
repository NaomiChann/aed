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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME_SIZE 20

void ContactAdd( void *pBuffer, int currentSize );
void ContactRemove( void *pBuffer, int currentSize );

int main() {
    void *pBuffer;
    int input, userCheck = 1, currentSize = 0;

    pBuffer = malloc( 10 * sizeof( char ) );
    
    while ( userCheck == 1 ) {
        printf( "\nEscolha uma acao: \n1) Adicionar contato \n2) Remover contato \n3) Procurar \n4) Listar \n5) Sair \n" );
        scanf( "%d", &input );
        fflush( stdin );

        switch ( input ) {
            case 1:
                ContactAdd( pBuffer, currentSize );
                break;

            case 2:
                ContactRemove( pBuffer, currentSize );
                break;

            case 3:
                break;
                
            case 4:
                printf( "%s", ( char * ) pBuffer );
                break;                
            
            case 5:
                userCheck = 0;
                free( pBuffer );
                break;
            
            default:
                printf( "Digite uma opcao valida.\n" );
                break;

        }
    }

    return 0;
}

/*5553912345678
====================
NameAdd
 Adds name to the list string
====================
*/
//   9char  int   int
// |nome|, |id|, |tel|\n|nome|
void ContactAdd( void *pBuffer, int currentSize ) {
/*
    void *pNome, *pIdade, *pTelefone;
    char nome[10];
    int idade, telefone;
    pNome = realloc( pBuffer, currentSize * ( ( 10 * sizeof( char ) ) + ( 2 * sizeof( int ) ) ) );
    pBuffer = pNome;
    pIdade = pNome + ( 10 * sizeof( char ) );
    pTelefone = pIdade + sizeof( int );

    printf( "Digite o nome do novo contato: " );
    scanf("%10s", nome);
    fflush( stdin );
    printf( "Digite a idade: " );
    scanf("%d", &idade);
    fflush( stdin );
    printf( "Digite o telefone: " );
    scanf("%d", &telefone);
    fflush( stdin );

    pNome = nome;
    pIdade = idade;
    pTelefone = telefone;
*/
}

/*
====================
NameRemove
 Removes name from the list string
====================
*/
void ContactRemove( void *pBuffer, int currentSize ) {
}

/*
====================
ContactList
 Lists all contacts
====================
*/

void ContactList( void *pBuffer, int currentSize ) {
}
