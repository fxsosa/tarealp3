#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
int main(void){
    int status = 0;
    sigset_t mySet;

    printf("%d\n", getpid());
    sigfillset(&mySet);
    sigprocmask(SIG_BLOCK, &mySet, NULL);
    int signalNbr;
    sigwait(&mySet, &signalNbr);
    if (signalNbr == -1)
    {
        perror("Failed to wait using sigwait");
        return 1;
    } // End if
    else
        fprintf(stderr, "se recibio la signal #%d\n", signalNbr);


    return 0;
}
