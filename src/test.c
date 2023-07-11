#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*line;

	line = strdup("heythere");
	printf("%s\n", line);
	memmove(line + 3, "ya", strlen("ya") + 1);
	printf("%s\n", line);
	return (0);
}
