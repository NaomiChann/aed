/*
fazer um programa que testa se uma sequencia de caracteres fornecida pelo usuario é
um palindromo, ou seja, é uma palavra cuja primeira metade é simetrica à segunda metade
exemplo - aabccbaa
o usuario digita uma letra e a tecla enter a´te que ele digite x e enter para terminar a sequencia
implemente a função pop e push de pilha e resolva o problema com elas
no video 4 casos de s e n
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int size;
	char *top;
	char *bot;
} StackInfo;

StackInfo Push( char input, char *stack, StackInfo info );
StackInfo Pop( char *stack, StackInfo info );

int main() {
	StackInfo info, infoCheck;
	info.size = 0;
	infoCheck.size = 0;

	char input, *stack, *stackCheck;
	stack = ( char * ) malloc( 1 );
	stackCheck = ( char * ) malloc( 1 );

	printf( "\nDigite os caracteres ( ou digite x para sair )\n" );
	while ( input != 'x' ) {
		scanf( "%c", &input );
		fflush( stdin );
		if ( input != 'x' ) {
			info = Push( input, stack, info );
		}
	}

	if ( info.size == 1 ) {
		printf( "sim \n" );
		return ( 0 );
	} else if ( info.size == 0 ) {
		printf( "Nenhum caractere digitado. \n" );
		return ( 0 );
	}

	if ( ( info.size % 2 ) != 0 ) {
        for ( int i = ( info.size - 1 ) / 2; i > 0; i-- ) {
            infoCheck = Push( *info.top, stackCheck, infoCheck );
            info = Pop( stack, info );
        }
        info = Pop( stack, info );
    } else {
        for ( int i = info.size / 2; i > 0; i-- ) {
            infoCheck = Push( *info.top, stackCheck, infoCheck );
            info = Pop( stack, info );
        }
    }

	while ( *info.top == *infoCheck.top && !( info.size == 0 || infoCheck.size == 0 ) ) {
        info = Pop( stack, info );
        infoCheck = Pop( stackCheck, infoCheck );
    }
    
    if ( info.size == 0 && infoCheck.size == 0 ) {
        printf( "sim \n" );
    } else {
        printf( "nao \n" );
    }

	free( stack );
	free( stackCheck );
	return ( 0 );
}

StackInfo Push( char input, char *stack, StackInfo info ) {
	info.size += 1;
	stack = realloc( stack, info.size * sizeof( char ) );
	info.bot = stack;
	info.top = info.bot + ( info.size - 1 );

	*info.top = input;
	return ( info );
}

StackInfo Pop( char *stack, StackInfo info ) {
	if ( info.size == 0 ) {
        printf( "erro" );
        return ( info );
    }

	info.size -= 1;
	if ( info.size != 0 ) {
		stack = realloc( stack, info.size * sizeof( char ) );
	}
	info.top = info.bot + ( info.size - 1 );

	return ( info );
}