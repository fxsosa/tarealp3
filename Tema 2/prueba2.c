
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

int main(void){
    pid_t child1 = fork();
    if( child1 ){
       printf("child1 PID: %d\n", getpid());
       sleep
    }
    return 0;
}
