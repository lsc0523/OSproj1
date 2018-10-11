/* Executes and waits for multiple child processes. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
	printf("*******check1*******\n");
  wait (exec ("child-simple"));
	printf("*******check2*******\n");
  wait (exec ("child-simple"));
	printf("*******check3*******\n");
  wait (exec ("child-simple"));
	printf("*******check4*******\n");
  wait (exec ("child-simple"));
}
