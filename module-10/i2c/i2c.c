#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

int main()
{
	int fd;
	int addr = 0x40;
	uint8_t reg = 0x10;
	int32_t res;

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
	print(;;)
	{
		res = i2c_smbus_read_word_data(fd, reg);
		
		// read data from addressed register
		if (res < 0)
			printf("Failed to read data.\n");
		else
			printf("Data read from reg %x is %x", reg, res);

		// write some data
		if (i2c_smbus_write_word_data(fd, reg, 0xaa00) < 0)
			printf("Failed to write data.\n");
	}
	
	return 0;
}
