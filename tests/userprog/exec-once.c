/* Executes and waits for a single child process. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
	printf("*****************check**************\n");
  wait (exec ("child-simple"));
}
