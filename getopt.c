#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void start_child(int id);
void wait_as_parent();
static void print_child_info(pid_t pid, int status);

int main(int argc, const char **argv)
{
	int id;
	pid_t pid;

	for (id = 0; id < 4; id++) {
		pid = fork();
		if (pid == 0) {
			/* child */
			start_child(id);
		} else if (pid > 0) {
			/* parent */
			printf("[%d] child pid = %d\n", id, pid);
		} else {
			/* error */
			perror("fork");
			break;
		}
	}

	wait_as_parent();
	return 0;
}

void start_child(int id)
{
	while(1) {
		printf("I am child. id = %d\n", id);
		sleep(3);
	}
}

void wait_as_parent()
{
	pid_t pid;
	int status;

	printf("I am a parent\n");
	while (1) {
		pid = waitpid(-1, &status, WNOHANG);
		if (pid == 0) {
			/* do nothing */
		} else if (pid > 0) {
			/* a child chages its status */
			print_child_info(pid, status);
		} else {
			/* error */
			perror("waitpid");
		}
		sleep(1);
	}
}

static void print_child_info(pid_t pid, int status)
{
	printf("child %d chages status\n", pid);
	printf("WIFEXITED:    %d\n", WIFEXITED(status));
	printf("WEXITSTATUS:  %d\n", WEXITSTATUS(status));
	printf("WIFSIGNALED:  %d\n", WIFSIGNALED(status));
	printf("WTERMSIG:     %d\n", WTERMSIG(status));
	printf("WCOREDUMP:    %d\n", WCOREDUMP(status));
	printf("WIFSTOPPED:   %d\n", WIFSTOPPED(status));
	printf("WSTOPSIG:     %d\n", WSTOPSIG(status));
	printf("WIFCONTINUED: %d\n", WIFCONTINUED(status));
 }
