#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void catch_sigalrm(int sig) {
	printf("Caught SIGARLM\n");
}

void catch_sigsegv(int sig) {
	printf("Caught SIGSEGV\n");
}
void catch_sigint(int sig) {
	printf("Caught SIGINT\n");
}
void catch_sigterm(int sig) {
	printf("Caught SIGTERM\n");
}
void catch_sigkill(int sig) {
	printf("Caught SIGKILL\n");
}
void catch_sigill(int sig) {
	printf("Caught SIGILL\n");
}
void catch_sigpipe(int sig) {
	printf("Caught SIGPIPE\n");
}
void catch_sigio(int sig) {
	printf("Caught SIGIO\n");
}
void catch_sigemt(int sig) {
	printf("Caught SIGEMT\n");
}
int main() {

	signal(SIGALRM, catch_sigalrm);	
	signal(SIGINT, catch_sigint);
	signal(SIGTERM, catch_sigterm);
	while (1) {
		;
	}
	return 0;
}
