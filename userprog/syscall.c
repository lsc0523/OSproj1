#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

	void
syscall_init (void) 
{
	intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

	static void
syscall_handler (struct intr_frame *f UNUSED) 
{
	printf("syscall : %d\n",*(uint32_t *)(f->esp));
	
	switch(*(uint32_t *)(f->esp))
	{
		case SYS_HALT:
			halt();
			break;
		case SYS_EXIT:
			exit(*(uint32_t *)(f->esp +4));
			break;
		case SYS_EXEC:
			exec((const char*)*(uint32_t*)(f->esp +4));
			break;
		case SYS_WAIT:
			wait( (pid_t)*(uint32_t *)(f->esp + 4));
			break;
		case SYS_CREATE:
			break;
		case SYS_REMOVE:
			break;
		case SYS_FILESIZE:
			break;
		case SYS_READ:
			read((int)*(uint32_t *)(f->esp + 20), (void *)*(uint32_t *)(f->esp + 24), (unsigned)*((uint32_t *)(f->esp + 28)));
			break;
		case SYS_WRITE:
			write((int)*(uint32_t *)(f->esp+4), (void *)*(uint32_t *)(f->esp + 8 ), (unsigned)*((uint32_t *)(f->esp +12)));
			break;
		case SYS_SEEK:
			break;
		case SYS_TELL:
			break;
		case SYS_CLOSE:
			break;

	}
	printf ("system call!\n");
	thread_exit ();
}

void halt(void)
{
	shutdown_power_off();
}

void exit(int status)
{
	printf("%s: exit(%d)\n", thread_name(),status);
	thread_exit();
}

pid_t exec(const char *cmd)
{
	return process_execute(cmd);
}

int wait(pid_t pid)
{
	return process_wait(pid);
}

int read(int fd, void* buffer, unsigned size)
{
	int i;
	if(fd==0){
		for (i=0;i<size;i++){
			if(*(uint8_t *)(buffer+i) = input_getc()){
					break;
			}		
		}
		if(i!=size)
			return -1;
	}
	return i;
}

int write(int fd,const void *buffer, unsigned size)
{
	if(fd==1){
		putbuf(buffer,size);
		return size;
	}
	return -1;
}

