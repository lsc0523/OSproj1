#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"

static void syscall_handler (struct intr_frame *);

	void
syscall_init (void) 
{
	intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}
	void
check_vaddr(void* esp)
{
	if(is_kernel_vaddr(esp))
		exit(-1);
}

	static void
syscall_handler (struct intr_frame *f UNUSED) 
{
	/*printf("syscall : %d\n",*(uint32_t *)(f->esp));
	printf("address : %10X\n\n",f->esp);
	printf("f->esp+4 is %d\n\n",*(uint32_t*)(f->esp +4));
	printf("f->esp+8 is %d\n\n",*(uint32_t*)(f->esp+8));
	printf("f->esp+12 is %d\n\n",*(uint32_t*)(f->esp+12));
	printf("f->esp+12 is %d\n\n",*(uint32_t*)(f->esp+16));
	printf("f->esp+12 is %d\n\n",*(uint32_t*)(f->esp+20));

	if(is_kernel_vaddr(f->esp))
		exit(-1);
	hex_dump(f->esp,f->esp,100,1);*/
	switch(*(uint32_t *)(f->esp))
	{
		case SYS_HALT:
			halt();
			break;
		case SYS_EXIT:
			check_vaddr(f->esp+4);
			exit(*(uint32_t *)(f->esp +4));
			break;
		case SYS_EXEC://2
			check_vaddr(f->esp+4);
			f->eax=exec((const char*)*(uint32_t*)(f->esp +4));
			break;
		case SYS_WAIT:
			check_vaddr(f->esp+4);
			f->eax=wait( (pid_t)*(uint32_t *)(f->esp + 4));
			break;
		case SYS_CREATE:
			break;
		case SYS_REMOVE:
			break;
		case SYS_OPEN:
			break;
		case SYS_FILESIZE:
			break;
		case SYS_READ:
			check_vaddr(f->esp+20);
			check_vaddr(f->esp+24);
			check_vaddr(f->esp+28);
			f->eax=read((int)*(uint32_t *)(f->esp + 20), (void *)*(uint32_t *)(f->esp + 24), (unsigned)*((uint32_t *)(f->esp + 28)));
			break;
		case SYS_WRITE://9
			check_vaddr(f->esp+4);
			check_vaddr(f->esp+8);
			check_vaddr(f->esp+12);
			f->eax=write((int)*(uint32_t *)(f->esp+4), (void *)*(uint32_t *)(f->esp + 8 ), (unsigned)*((uint32_t *)(f->esp +12)));
			break;
		case SYS_SEEK:
			break;
		case SYS_TELL:
			break;
		case SYS_CLOSE:
			break;

	}
	//printf ("system call!\n");
	//thread_exit ();
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
	process_wait(pid);
	return pid;
}

int read(int fd, void* buffer, unsigned size)
{
	int i=0;
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

