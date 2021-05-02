#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
//we declare a variable of type integer to hold the positive integer
//and initalize the value to zero
    int i=0;
    int status;
    //declaring the parent id
    pid_t pid;
    /* the size (in bytes) of shared memory object */
    const int SIZE=4096;
    /* name of the shared memory object */
    const char *name = "keti_ex22";
    /* shared memory file descriptor */
    int shm_fd;
    /* base address of shared memory */
    int *shm_base;
    /* pointer to shared memory object*/
    int *ptr;
    /* create the shared memory object */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    /* configure the size of the shared memory object */
    ftruncate(shm_fd, SIZE);
    /* memory map the shared memory object */
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
//the exercise asks to perform necessary error checking to ensure that a positive
//integer is passed on the command line so we will implement a so while loop
//the statement inside the do segment will be repeated until the number entered is positive
    do {
        //the C library function int printf(const char *format, ...) sends formatted output to stdout
        printf("Enter a positive integer: ");
        //the C library function int scanf(const char *format, ...) reads formatted input from stdin
        scanf("%d", &i);

    } while (i<=0);
    //forking the oarent function

    pid = fork();
    //fork returns a positive value to the parent

    if (pid>0) {
        /* map the shared memory segment to the address space of the process*/
        shm_base = mmap(0, SIZE, PROT_READ , MAP_SHARED, shm_fd, 0);
        if (shm_base == MAP_FAILED) {
            printf("Error. Mapping the shared memory segment ot the adress space of the parent failed.");
            exit(1);
        }
        pid=wait(&status);
        //If mapping is correctly done we will read and display the numbers
        ptr=shm_base;
        //we will first get the contents of the pointer
		// we will start at the base address  
        i=*ptr; 
        //we will read the shared memory until we read 1 since this number 
        //displays the last generated value
        while(i!=1) 
        {
           //print number
		    printf("%d",i);
		    //move pointer to next location in shared memory
            ptr++; 
            //next value of i ( the number) is the contents of the adress space pointer is pointing at
            i=*ptr; 
        }
        // last number ( the 1 value) needs to be printed since we stop looing before 1 is reached
        printf("%d",i); 

    } else {
        //mapping the shared memory segment to the address space of the child process
        shm_base = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,shm_fd, 0);
         if (shm_base == MAP_FAILED) {
            printf("Error. Mapping the shared memory segment ot the adress space of the child failed.");
            exit(1);
        }
        //start at shared memory base address
        int *ptr=shm_base; 
        // we loop until we reach 1 (the final value)
        while(i>1)
        {
        	//store the value at the adress
            *ptr=i;/*store the number at the address*/
            //if i is even or odd apply the correspoding algorithms
            if(i%2==1) {
            	  i=3*i+1;
			}else{
            	i=i/2;
			}
            //move the pointer
            ptr++;
        }
        //since we stop looping before 1 we must also add the 1 which is the last value of the sequence
        *ptr=i; 
    }
    
    //unmap the shared memory 
    shm_unlink(name);
    return 0;

}
