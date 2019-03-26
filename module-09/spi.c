#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int fd;
	struct spi_ioc_transfer spi;
	int speed = 100000;
	int mode = 2;
	int size = 8;
	int delay = 0;
	unsigned char rx_buffer;
	unsigned char tx_buffer = 0xaa;
	
	// initialize spi struct
	memset(&spi, 0, sizeof(spi));

	// try to open spi device
	fd = open("/dev/spidev0.0", O_RDWR);
	
	// check for any errors
	if (fd < 0)
	{
		printf("Error while trying to open spi device.\n");
		return -1;
	}

	// set spi parameters
	if (ioctl(fd, SPI_IOC_WR_MODE, &mode) < 0)	// mode
	{
		printf("Error while trying to change spi mode.\n");
		return -1;
	}

	if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &size) < 0)	// size
	{
		printf("Error while trying to change spi word size.\n");
		return -1;
	}

	if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0)	// speed
	{
		printf("Error while trying to change spi speed.\n");
		return -1;
	}

	// exchange data forever
	for (;;)
	{
		spi.tx_buf = (unsigned long)(&tx_buffer);
		spi.rx_buf = (unsigned long)(&rx_buffer);
		spi.len = 1;
		spi.delay_usecs = delay;
		spi.speed_hz = speed;
		spi.bits_per_word = size;

		ioctl(fd, SPI_IOC_MESSAGE(1), &spi);
		
		printf("Received data is %x.\n", rx_buffer);
	}
	
	return 0;
}
