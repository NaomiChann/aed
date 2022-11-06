/*
	Receber numeros como input e armazena-los em uma arvore de busca binaria
	e apos verificar se a arvore resultante eh uma AVL ou nao
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node *Pointer;

typedef struct Node {
	int number;
	Pointer left, right;
} Node;

void Insert( Pointer *currentNode, int input );
int Height( Pointer *currentNode );
void Check( Pointer *currentNode, int *flag );
void FreeAll( Pointer *currentNode );

int main() {
	Pointer root = NULL;
	int input, userCheck = 1, failureFlag = 0;

	while ( userCheck == 1 ) {
		printf( "Digite um numero a ser adicionado: " );
		scanf( "%d", &input );
		fflush( stdin );

		Insert( &root, input );
		
		printf( "Deseja continuar? \n1) Sim \n0) Nao \n" );
        scanf( "%d", &userCheck );
		fflush( stdin );
	}

	Check( &root, &failureFlag );

	if ( failureFlag != 0 ) {
		printf( "Nao eh AVL" );
	} else {
		printf( "Eh AVL" );
	}

	FreeAll( &root );

	return ( 0 );
}

/*
====================
Insert()
 Inserts a new node into the binary search tree
====================
*/
void Insert( Pointer *currentNode, int input ) {
	if ( *currentNode == NULL ) { // if empty slot then allocate a new node
		*currentNode = ( Pointer ) malloc( sizeof( Node ) );
		( *currentNode )->number = input;
		( *currentNode )->left = NULL;
		( *currentNode )->right = NULL;
		return;
	}
    // searches for proper placement
    if ( input > ( *currentNode )->number ) {
		Insert( &( *currentNode )->right, input );
		return;
	}
    
    if ( input < ( *currentNode )->number ) {
		Insert( &( *currentNode )->left, input );
		return;
	}

    printf( "Numero ja existe" );
	return;
}

/*
====================
Height()
 Calculates the current node's height
 ( leaves have height = 1 )
====================
*/
int Height( Pointer *currentNode ) {
	int heightL, heightR;

	if ( *currentNode == NULL ) {
		return ( 0 );
	}
	
	heightL = Height( &( *currentNode )->left );
	heightR = Height( &( *currentNode )->right );
	
	if ( heightL > heightR ) {
		return ( heightL + 1 );
	} else {
		return ( heightR + 1 );
	}
}

/*
====================
Check()
 Traverses the whole tree in postorder
 and checks if the balance factor of every node is
 out of the stipulated range ( -1 <= bf <= 1 )
 and, if so, sets a global failure flag
====================
*/
void Check( Pointer *currentNode, int *flag ) {
	int heightL, heightR, bf;

	if ( *currentNode == NULL ) { // just for safety, should never return true
		return;
	}
	
	if ( ( *currentNode )->left != NULL ) {
		Check( &( *currentNode )->left, flag );
	}
	
	if ( ( *currentNode )->right != NULL ) {
		Check( &( *currentNode )->right, flag );
	}

	heightL = Height( &( *currentNode )->left );
	heightR = Height( &( *currentNode )->right );
	
	bf = heightL - heightR;

	if ( bf < -1 || bf > 1 ) {
        *flag = 1; // invalidates the whole tree as an AVL
    }
	return;
}

/*
====================
FreeAll()
 Traverses the whole tree in postorder
 and frees all allocated nodes
====================
*/
void FreeAll( Pointer *currentNode ) {
	if ( *currentNode == NULL ) {
		return;
	}
	
	if ( ( *currentNode )->left != NULL ) {
		FreeAll( &( *currentNode )->left );
	}
	
	if ( ( *currentNode )->right != NULL ) {
		FreeAll( &( *currentNode )->right );
	}
	
	free( *currentNode );
	return;
}