#include <types.h>
#include <kern/errno.h>
#include <kern/unistd.h>
#include <lib.h>
#include <machine/spl.h>
#include <test.h>
#include <synch.h>
#include <thread.h>
#include <scheduler.h>
#include <dev.h>
#include <vfs.h>
#include <vm.h>
#include <syscall.h>
#include <version.h>

void sys__exit(int exitCode) {
	kprintf("%d\n", exitCode);
	thread_exit();
}

int sys_printint(int c) {
	kprintf("%d\n", c);
	int retval = c % 2;
	if (retval < 0)
		retval *= -1;
	return retval;
}

int sys_reversestring(const char *str, int len) {
	char *ptr1, *ptr2;
	if (!str || !*str) {
		kprintf("%s\n", (char*)str);
		return len % 2;
	}
	for (ptr1 = (char*)str, ptr2 = (char*)str + len - 1; ptr2 > ptr1; ptr1++, ptr2--) {
		*ptr1 ^= *ptr2;
		*ptr2 ^= *ptr1;
		*ptr1 ^= *ptr2;
	}
	kprintf("%s\n", (char*)str);
	int retval = len % 2;
	if (retval < 0)
		retval *= -1;
	return retval;
}

