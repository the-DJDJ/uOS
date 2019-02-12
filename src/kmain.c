/**
 * The Kernel main file. This control's the kernel, and defines all default
 * actions.
 */

#include "fb.h"


/**
 * The main method. This is the entry point into the operating system, and is
 * called by the assembly code.
 */
void kmain ()
{
	/* Clear debug info from the output. */
	fb_clear();

	/* Write something. */
	fb_write("Hello.\n\nWelcome to uOS.", 23);
}
