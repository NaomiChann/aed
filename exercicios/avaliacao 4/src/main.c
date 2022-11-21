/*
	Dado um vetor nums contendo n número inteiros positivos e únicos encontre o número
	faltante na sequência. Assuma que somente um número está faltando para completar a
	sequência numérica.
*/

#include <stdio.h>
#include <stdlib.h>

int MissingNumber( int *nums, int numsSize );

int main( int argc, char *argv[] ) {
	int n, *nums;
	if ( argc >= 2 ) { // ensures at least one element for the array
		n = ( argc - 1 );
	} else {
		printf( "Pelo menos 1 elemento no vetor \n" );
		return( EXIT_FAILURE );
	}

	nums = ( int * ) malloc( n * sizeof( int ) ); // allocates

	for ( int i = 0; i < n; i++ ) { // properly transfers all arguments into array
		nums[i] = atoi( argv[i + 1] );
	}

	n = MissingNumber( nums, n ); // calls function
	printf( "%d \n", n ); // prints result

	free( nums ); // frees array
	return ( 0 );
}

/*
====================
MissingNumber()
 Checks an int array for its missing number
====================
*/
int MissingNumber( int *nums, int n ) {
	int sum = 0, value = 0;
	if ( n % 2 == 0 ) { // checks if even
		value = ( n + 1 ) * ( n / 2 ); // math shenanigans
	} else { // treats odd case
		value =  ( n * ( ( n - 1 ) / 2 ) ) + n; // more math shenanigans
	}

	for ( int i = 0; i < n; i++ ) { // sums all elements
		sum += nums[i];
	}

/*
	the difference between the sum of all consecutive numbers from 1 to n and
	the sum off all numbers in the given array is exaclty the missing number
*/

	return ( value - sum );
}