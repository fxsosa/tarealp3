#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
void manejador_ctrl_c(int signo);
int capturar_ctrl_c();
int ignorar_ctrl_c();
char msg[]="Pulsado Ctrl-C\n";
struct sigaction act;
int main(void) {
    double y;
    int i;
    capturar_ctrl_c();
    fprintf (stdout, "Capturado CRTL-Cdurante 10 seg\n");
    pause();
    ignorar_ctrl_c();
    fprintf (stdout, "Ignorado CTRL-Cdurante 10 seg\n");
    for (i=0; i<100000000; i++)
        y= sin((double)i);
    fprintf (stdout, "Fin programa\n");
}
void manejador_ctrl_c(int signo) {
    fprintf(stdout, "%s", msg);
    fflush(stdout);
}
int capturar_ctrl_c() {
    act.sa_handler= manejador_ctrl_c;
    sigemptyset(&act.sa_mask);
    act.sa_flags= 0;
    return sigaction(1, &act, NULL);
}
int ignorar_ctrl_c() {
    if (sigaction(SIGINT, NULL, &act)==-1){
        perror("No se puede recuperar manejador anterior SIGINT");
        return -1;
    } else if (act.sa_handler==manejador_ctrl_c) {
        act.sa_handler= SIG_IGN;
        return sigaction(SIGINT, &act, NULL);
    }
}
