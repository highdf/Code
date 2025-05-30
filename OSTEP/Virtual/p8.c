#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int child_pid = fork();

	if(child_pid < 0) {
		printf("The child process is faild\n");
	} else if(child_pid == 0) {
		int pid = wait(NULL);
		printf("pid = %d\n",pid);
		printf("I'm child process (PID:%d)\n",getpid());
	} else {
		printf("I'm parent process (PID:%d) \n",getpid());
	}

	return 0;
}
