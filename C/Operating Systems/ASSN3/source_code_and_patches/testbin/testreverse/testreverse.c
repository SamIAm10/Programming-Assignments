#include <unistd.h>
#include <stdio.h>

int main() {
	int ret;
	ret = reversestring("HelloWorld", 10);
	printint(ret);
	_exit(0);
	return 0;
}
