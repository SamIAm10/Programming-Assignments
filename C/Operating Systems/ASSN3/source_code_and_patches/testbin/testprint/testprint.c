#include <unistd.h>
#include <stdio.h>

int main() {
	int i;
	int ret;
	for (i = -1; i <= 3; i++) {
		ret = printint(i);
		printint(ret);
	}
	_exit(0);
	return 0;
}
