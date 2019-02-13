/**
 * The Util file. This holds all of the useful low-level functions in use in
 * the operating system.
 */


#include "fb.h"
#include "serial.h"
#include "util.h"


/**
 * The print method. This prints the contents of the buffer buf of length len
 * to the the specified output, and automatically advances the cursor after a
 * character has been written, if the output is the screen. The screen is also
 * scrolled if necessary.
 * 
 * @param com The COM port
 * @param buf The buffer to write
 * @param len The number of characters to write
 */
void print (unsigned int com, char* buf, unsigned int len)
{
	switch (com) {

		case FB:
			fb_write(buf, len);
			break;

		default:
			serial_write(com, buf, len);
			break;

	}
}
