#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main ()
{
	int fd;
	struct termios config;
	unsigned char c = 's';
	
	// open serial port
	fd = open("/dev/tty", O_RDWR, O_NOCTTY, O_NDELAY);

	// check for errors
	if (fd == -1)
	{
		printf("Failed to open serial port.\n");
		return -1;
	}

	// get attributes
	if (tcgetattr(fd, &config) < 0)
	{
		printf("Error while getting configuration.\n");
		return -1;
	}
	
	// make raw config
	cfmakeraw(&config);

	// set the speed
	cfsetispeed(&config, B9600);
	cfsetospeed(&config, B9600);

	config.c_cc[VMIN] = 1;
	config.c_cc[VTIME] = 0;

	// Apply the config
	if (tcsetattr(fd, TCSANOW, &config) < 0)
	{
		printf("Error while trying to set the configuration.\n");
		return -1;
	}

	while (c != 'q')
	{
		// loopback
		if (read(fd, &c, 1) > 0)
			write(fd, &c, 1);
	}

	close(fd);
	
	return 0;
}
