/**
 * The Framebuffer file. This is responsible for displaying a buffer of memory
 * on the screen.
 */


#include "fb.h"
#include "io.h"


/**
 * The framebuffer variable. This sits at address 0x000B8000, and is treated as
 * a char pointer such that we can write to it.
 */
char *fb = (char *) 0x000B8000;


/**
 * The write_cell method. This writes a character with the given foreground and
 * background to position i in the framebuffer.
 *
 * @param i  The location in the framebuffer
 * @param c  The character
 * @param fg The foreground colour
 * @param bg The background colour
 */
void fb_write_cell (unsigned int i, char c, unsigned char fg, unsigned char bg)
{
	fb[i] = c;
	fb[i + 1] = ((bg & 0x0f) << 4) | (fg & 0x0f);
}

/**
 * The move_cursor method. This moves the cursor of the framebuffer to the
 * given position.
 *
 * @param pos The new position of the cursor
 */
void fb_move_cursor (unsigned short pos)
{
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT,    pos & 0x00FF);
}

/**
 * The write method. This writes the contents of the buffer buf of length len
 * to the screen, and automatically advances the cursor after a character has
 * been written. The screen is also scrolled if necessary.
 * 
 * @param buf The buffer to write
 * @param len The number of characters to write
 */
void fb_write (char *buf, unsigned int len)
{
	/* The variable for seeing how far into the write we are. */
	unsigned int pos, count;

	/* Write every character to the framebuffer. */
	count = 0;
	for (count = 0; count < len; count++) {
		if (*buf == '\n') {
			pos += FB_WIDTH - (pos % FB_WIDTH) - 1;
		} else {
			fb_write_cell(pos * 2, *buf, FB_WHITE, FB_BLACK);
		}

		buf++;
		pos++;
	}

	/* And put the cursor in the right place */
	fb_move_cursor(pos);
}

/**
 * The clear method. This clears the entire screen by emptying out the
 * framebuffer variable.
 *
 */
void fb_clear (void)
{
	/* The variables to keep track of where we are on the screen. */
	int pos;

	/* Empty every element in the frame buffer. */
	for (pos = 0; pos < FB_WIDTH * FB_HEIGHT; pos++) {
		fb_write_cell(pos * 2, 0, FB_WHITE, FB_BLACK);
	}

	/* And put the cursor in the right place */
	fb_move_cursor(0);
}
