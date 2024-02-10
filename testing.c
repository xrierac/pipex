
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

extern char **environ;
int main(int argc, char *argv[])
{
	int	i;

	i = -1;
	while (environ[++i] != NULL)
		printf("%s\n", environ[i]);
	argc = 2;
	if (execve("ls", argv, environ) == -1)
		printf("bye\n");
    printf("hello\n");
    return 0;
}

