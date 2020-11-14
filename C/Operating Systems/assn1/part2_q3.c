#include <stdio.h>

int main () {
	int i = 150; //declare i as int equal to 150
	int *tp; //declare tp as int pointer
	tp = &i; //set tp to point to address of i
	printf("Address of variable i: %x\n", &i); //print address of i in hexadecimal (%x)
	printf("Value of *tp variable: %d\n", *tp ); //print value at address of i in decimal (%d)
	return 0;
}

/*
Output:
Address of variable i: c6b8f68c
Value of *tp variable: 150

Explanation:
The variable "i" is declared as an "int", and the
variable "tp" is declared as an "int" pointer. In C, a
pointer is a variable that stores the address of
another variable. "tp" stores the address of "i".
The "&" operator returns the address
of a variable, so "&i" returns the address where "i"
is stored (in this case it's "c6b8f68c" in hex).
The "*" operator dereferences the pointer and returns
the value stored at that address (in this case, it is
the value of "i", which is "150").
*/