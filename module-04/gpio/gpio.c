#define BCM_2708_PERI_BASE	0x20000000
// define GPIO controller base address
#define GPIO_BASE		(BCM_2708_PERI_BASE + 0x200000)

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int mem_fd;
void *gpio_map;
volatile unsigned *gpio;

void setup_io();

int main()
{
	// set up the gpio to have direct access to registers of gpio controller
	setup_io();

	// TODO: set BCM17 to output mode
	
	// loop forever
	for (;;)
	{
		// TODO: set pin to high
		
		// wait for 1 sec
		sleep(1);

		// TODO: set pin to low
		
		// wait for 1 sec
		sleep(1);
	}
	
	return 0;
}

void setup_io()
{
	// open /dev/mem
	if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC)) < 0)
	{
		printf("Failed to open /dev/mem. Please run program as admin.\n");
		exit(-1);
	}

	// mmap gpio
	gpio_map = mmap(
		NULL,			// any address within virtual space is ok
		BLOCK_SIZE,		// map length
		PROT_READ|PROT_WRITE,	// enable both reading and writing
		MAP_SHARED,		// share the map with other processes
		mem_fd,			// file descriptor of the device
		GPIO_BASE		// offset to gpio peripheral
	);

	// it is not needed anymore
	close(mem_fd);
	
	if (gpio_map == MAP_FAILED)
	{
		printf("Error while trying to map gpio peripheral on %d.\n", (int)gpio_map);
		exit(-1);
	}

	gpio = (volatile unsigned *)gpio_map;
}
