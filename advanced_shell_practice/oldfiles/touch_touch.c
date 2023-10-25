#include "gosh.h"

/**
 * touch_touch - a custom touch function that creates new files
 * @agv: cmd entered by user to create new file
 * Return: 0 on success, -1 on failure.
 */

int touch_touch(char **agv)
	/* Handle the touch command */
{
	int fd = open(agv[1], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);

	if (fd == -1)
	{
		perror(agv[1]);
		return (-1);
	}
	close(fd);
	return (0);
}
