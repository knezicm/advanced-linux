#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdio.h>

int main()
{
	int fd;
	int addr = 0x40;
	unsigned char reg = 0x10;
	unsigned char rx_buffer[10];
	unsigned char tx_buffer[10];

	// try to open i2c device
	fd = open("/dev/i2c-0", O_RDWR);
	
	// check for any errors
	if (fd < 0)
	{
		printf("Error while trying to open i2c device.\n");
		return -1;
	}

	// set the address of i2c device
	if (ioctl(fd, I2C_SLAVE, addr) < 0)
	{
		printf("Error while trying to set the address of i2c device.\n");
		return -1;
	}

	// data exchange forever
	for (;;)
	{
		// fill the tx buffer
		tx_buffer[0] = reg;

		// write the data (reg address)
		if (write(fd, tx_buffer, 1) != 1)
			printf("Failed to write data.\n");
			
		// read data from addressed register
		if (read(fd, rx_buffer, 1) != 1)
			printf("Failed to read data.\n");
		else
			printf("Data read from reg 0x%x is 0x%x.\n", reg, rx_buffer[0]);
	}
	
	return 0;
}
