#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

#define FB   0
#define COM1 1
#define COM2 2

/**
 * The outb method. This sends the given data to the given I/O port. Defined in
 * io.s
 *
 * @param  port The I/O port to send the data to
 * @param  data The data to send to the I/O port
 */
void outb (unsigned short port, unsigned char data);

/**
 * The inb method. This reads a byte from the I/O port. Defined in io.s
 *
 * @param  port The address of the I/O port
 * @return      The read byte
 */
unsigned char inb (unsigned short port);

#endif /* INCLUDE_IO_H */
