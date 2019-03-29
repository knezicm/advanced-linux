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
	
	struct i2c_msg iomsgs[] = {
		[0] = {
			.addr = addr,		/* slave address */
			.flags = 0,		/* write access */
			.buf = &reg,
			.len = 1
		},
		[1] = {
			.addr = addr,		/* slave address */
			.flags = I2C_M_RD,	/* read access */
			.buf = rx_buffer,
			.len = 1		
		},
	};
	
	struct i2c_rdwr_ioctl_data msgset = {
		.msgs = iomsgs,
		.nmsgs = 2
	};

	// try to open i2c device
	fd = open("/dev/i2c-0", O_RDWR);
	
	// check for any errors
	if (fd < 0)
	{
		printf("Error while trying to open i2c device.\n");
		return -1;
	}

	// data exchange forever
	for (;;)
	{
		// read data from addressed register
		if (ioctl(fd, I2C_RDWR, &msgset) < 0)
			printf("Failed to read data.\n");
		else
			printf("Data read from reg 0x%x is 0x%x.\n", reg, rx_buffer[0]);
	}
	
	return 0;
}
