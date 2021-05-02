#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>   
#include <sys/types.h>
#include <sys/wait.h>

int main() {
//we declare a variable of type integer to hold the positive integer 
//and initalize the value to zero 
     int i=0;
     int status;
     //declaring the parent id
     pid_t pid;
//the exercise asks to perform necessary error checking to ensure that a positive
//integer is passed on the command line so we will implement a so while loop
//the statement inside the do segment will be repeated until the number entered is positive
     do{
     //the C library function int printf(const char *format, ...) sends formatted output to stdout
          printf("Enter a positive integer: ");
     //the C library function int scanf(const char *format, ...) reads formatted input from stdin
          scanf("%d", &i);

     }while (i<=0);
    //forking the oarent function
     
     pid = fork();
     //fork returns a positive value to the parent
     //
     if (pid>0){
         //we don't want a zombie child
         //so we call the wait() function at the parent
        wait(&status);
     }
     //fork returns 0 to the newly created child 
     // we want to generate the sequence in the child function
     else  if (pid== 0) {
        //when the algorithm is continually applied all positive integers will eventually reach 1
        //so we want to print all values until they reach 1
        // we will use a while loop
        // we will loop until the value inputed will reach 1
          while (i!=1){
		 //if inputed number is even the division with 2 will return a remainder of 0
		 //so if remainder is 0 number is even, if it's 1 number is odd
              if (i%2 == 0){
			  // if number is even divide it by 2
                   i = i/2;
              }
              else if (i%2 == 1){
               // if number is odd then caculate (3*number)+1
                   i = 3 * (i) + 1;
              }   
              //finally print the number
              printf("%d\n",i);
          }
          //when 1 is reached break the loop
     }

return 0;
  
}
