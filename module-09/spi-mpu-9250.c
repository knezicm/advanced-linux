#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <string.h>

#define I2C_IF_DIS	4
#define USER_CTRL	0x6a
#define WHO_AM_I	0x75
#define RW_BIT_POS	7

int main()
{
	int fd;
	int speed = 100000;
	int mode = 0;
	int size = 8;
	unsigned char rx_buffer[] = {0x00, 0x00};
	unsigned char tx_buffer[] = {USER_CTRL & ~(1 << RW_BIT_POS), (1 << I2C_IF_DIS), WHO_AM_I | (1 << RW_BIT_POS), 0x00};
	struct spi_ioc_transfer spi[] = {
		[0] = {
			.tx_buf = (unsigned long)&tx_buffer[0],
			.rx_buf = (unsigned long)rx_buffer,
			.len = 2,
			.delay_usecs = 0,
			.speed_hz = speed,
			.bits_per_word = size
			},
		[1] = {
			.tx_buf = (unsigned long)&tx_buffer[2],
			.rx_buf = (unsigned long)rx_buffer,
			.len = 2,
			.delay_usecs = 0,
			.speed_hz = speed,
			.bits_per_word = size
			},
	};
	
	// initialize spi struct
	memset(spi, 0, 2*sizeof(struct spi_ioc_transfer));

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

	// wait for 100ms before disabling i2c
	usleep(100000);
	
	ioctl(fd, SPI_IOC_MESSAGE(1), &spi[0]);
	ioctl(fd, SPI_IOC_MESSAGE(1), &spi[1]);
		
	printf("My ID is %x.\n", rx_buffer[1]);
		
	close(fd);
	
	return 0;
}
