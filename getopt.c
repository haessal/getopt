#include <stdio.h>

int main(int argc, const char **argv)
{
	return 0;
}

static void handle_builtin(int argc, const char **argv)
{
	const char *cmd;
	struct cmd_struct *builtin;

	cmd = argv[0];
	builtin = get_builtin(cmd);
	if (builtin)
		exit(run_builtin(builtin, argc, argv));
}
