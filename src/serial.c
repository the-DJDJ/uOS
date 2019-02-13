/**
 * The Serial file. This is used in communicating with serial ports.
 */


#include "io.h"
#include "serial.h"


/**
 * The I/O port commands
 */

/**
 * The serial configure baud rate method. This sets the speed of the data being
 * sent. The default speed of a serial port port is 115200 bits/s. The argument
 * is a divisor of that number, hence the resulting speed becomes
 * (115200 / divisor) bits/s.
 *
 * @param com      The COM port to configure
 * @param divisor  The divisor
 */
void serial_configure_baud_rate (unsigned short com, unsigned short divisor)
{
	outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
	outb(SERIAL_DATA_PORT(com),         (divisor >> 8) & 0x00FF);
	outb(SERIAL_DATA_PORT(com),         divisor & 0x00FF);
}

/**
 * The serial configure line method. This configures the line of the given
 * serial port. The port is set to have a data length of 8 bits, no parity bits,
 * one stop bit and break control disabled.
 *
 * @param com      The serial port to configure
 */
void serial_configure_line (unsigned short com)
{
	/* 
         * Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
	 * Content: | d | b | prty  | s | dl  |
	 * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
	 */
	outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

/**
 * The serial is transmit fifo empty method. This checks whether the transmit
 * FIFO queue is empty or not for the given COM port.
 *
 * @param  com     The COM port
 * @return 0       if the transmit FIFO queue is not empty
 *         1       if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty (unsigned int com)
{
	/* 0x20 = 0010 0000 */
	return inb (SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

/**
 * The method to initialise the serial port. This prepares it by sending all of
 * The required values over the port, so that it can be written to.
 *
 * @param com The COM port
 */
void serial_init (unsigned short com)
{
	/* Configure the baud rate, etc. */
	serial_configure_baud_rate(com, BAUD_RATE_DIVISOR);

	/* Write the config */
	outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
	outb(SERIAL_LINE_COMMAND_PORT(com), 0xC7);
	outb(SERIAL_LINE_COMMAND_PORT(com), 0x0B);

}

/**
 * The write method. This writes a specific character data to the specified
 * serial port.
 * 
 * @param com The COM port
 * @param buf The buffer to write
 * @param len The number of characters to write
 */
void serial_write (unsigned short com, char* buf, unsigned int len)
{
	/* Check if we're ready to write. */
	while (!serial_is_transmit_fifo_empty(com)) {
		/* Things are obviously not ready, so we'll wait a little. */
	}

	/* Prepare the write. */
	serial_init(com);

	/* Create some variables. */
	unsigned int count;

	/* And do the writing. */
	count = 0;
	for (count = 0; count < len; count++) {
		outb(SERIAL_DATA_PORT(com), *buf);
		buf++;
	}
}
