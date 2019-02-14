/**
 * The Kernel main file. This control's the kernel, and defines all default
 * actions.
 */

#include "util.h"
#include "fb.h"
#include "serial.h"


/**
 * The main method. This is the entry point into the operating system, and is
 * called by the assembly code.
 */
void kmain ()
{
	/* Clear debug info from the output. */
	fb_clear();

	/* Write something. */
	print(FB, "Hello.\n\nWelcome to uOS.", 23);
	print(SERIAL_COM1_BASE, "uOS serial output okay.\n", 24);
}
