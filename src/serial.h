#ifndef INCLUDE_SERIAL_H
#define INCLUDE_SERIAL_H

/**
 * The I/O ports
 */

/**
 * All the I/O ports are calculated relative to the data port. This is because
 * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
 * order, but they start at different values.
 */

#define FB                              0          /* For printing to FB */
#define SERIAL_COM1_BASE                0x3F8      /* COM1 base port */
#define SERIAL_COM2_BASE                0x2F8      /* COM2 base port */

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

/**
 * The I/O port commands
 */

/**
 * SERIAL_LINE_ENABLE_DLAB:
 *
 * Tells the serial port to expect first the highest 8 bits on the data port,
 * then the lowest 8 bits will follow
 */
#define SERIAL_LINE_ENABLE_DLAB         0x80

/**
 * BAUD_RATE_DIVISOR:
 *
 * The divisor used in setting a baud rate. This will give a baud rate of
 * 115 200 / 3 = 38400
 *
 */
#define BAUD_RATE_DIVISOR               0x02

/**
 * The serial configure baud rate method. This sets the speed of the data being
 * sent. The default speed of a serial port port is 115200 bits/s. The argument
 * is a divisor of that number, hence the resulting speed becomes
 * (115200 / divisor) bits/s.
 *
 * @param com      The COM port to configure
 * @param divisor  The divisor
 */
void serial_configure_baud_rate (unsigned short com, unsigned short divisor);

/**
 * The serial configure line method. This configures the line of the given
 * serial port. The port is set to have a data length of 8 bits, no parity bits,
 * one stop bit and break control disabled.
 *
 * Name     | Description
 * ---------+------------
 * d        | Enables (d = 1) or disables (d = 0) DLAB
 * b        | If break control is enabled (b = 1) or disabled (b = 0)
 * prty     | The number of parity bits to use
 * s        | The number of stop bits to use (s = 0 equals 1, s = 1 equals 1.5 or 2)
 * dl       | Describes the length of the data
 *
 * Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
 * Content: | d | b | prty  | s | dl  |
 * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
 *
 * @param com      The serial port to configure
 */
void serial_configure_line (unsigned short com);

/**
 * The serial configure buffer method. This makes sure enables FIFO, clears
 * both receiver and transmission FIFO queues, and uses 14 bytes as the size of
 * the queue.
 *
 * Name     | Description
 * ---------+------------
 * lvl      | How many bytes should be stored in the FIFO buffers
 * bs       | If the buffers should be 16 or 64 bytes large
 * r        | Reserved for future use
 * dma      | How the serial port data should be accessed
 * clt      | Clear the transmission FIFO buffer
 * clr      | Clear the receiver FIFO buffer
 * e        | If the FIFO buffer should be enabled or not
 *
 * Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
 * Content: | lvl | bs | r | dma | clt | clr | e |
 * Value:   | 1 1 | 0  | 0 | 0   | 1   | 1   | 1 | = 0xC7
 *
 * @param com The COM port
 */
void serial_configure_buffer (unsigned short com);

/**
 * The serial configure modem method. This is used for very simple hardware
 * flow and indicate that we are ready to send data.
 *
 * Name     | Description
 * ---------+--------------------------------------------------
 * r        | Reserved
 * af       | Autoflow control enabled
 * lb       | Loopback mode (used for debugging serial ports)
 * ao2      | Auxiliary output 2, used for receiving interrupts
 * ao1      | Auxiliary output 1
 * rts      | Ready To Transmit
 * dtr      | Data Terminal Ready
 *
 * Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
 * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
 * Value:   | 0 | 0 | 0  | 0  | 0   | 0   | 1   | 1   | = 0x03
 *
 * @param com The COM port
 */
void serial_configure_modem (unsigned short com);

/**
 * The serial is transmit fifo empty method. This checks whether the transmit
 * FIFO queue is empty or not for the given COM port.
 *
 * @param  com     The COM port
 * @return 0       if the transmit FIFO queue is not empty
 *         1       if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty (unsigned int com);

/**
 * The method to initialise the serial port. This prepares it by sending all of
 * The required values over the port, so that it can be written to.
 *
 * @param com The COM port
 */
void serial_init (unsigned short com);

/**
 * The write method. This writes a specific character data to the specified
 * serial port.
 *
 * @param com    The COM port
 * @param buffer The buffer to write
 */
void serial_write (unsigned short com, char* buffer);

#endif /* INCLUDE_SERIAL_H */
