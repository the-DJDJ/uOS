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
char *framebuffer = (char *) 0x000B8000;

/**
 * The position variable tracking where we are on the screen.
 */
unsigned int position = 0;


/**
 * The write_cell method. This writes a character with the given foreground and
 * background to position i in the framebuffer.
 *
 * @param index      The location in the framebuffer
 * @param character  The character to write
 * @param foreground The foreground colour
 * @param background The background colour
 */
void fb_write_cell (unsigned int index, char character,
    unsigned char foreground, unsigned char background)
{
	framebuffer[index] = character;
	framebuffer[index + 1] = ((background & 0x0f) << 4) | (foreground & 0x0f);
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

    position = pos;
}

/**
 * The write method. This writes the contents of the buffer buf of length len
 * to the screen, and automatically advances the cursor after a character has
 * been written. The screen is also scrolled if necessary.
 *
 * @param buffer The buffer to write
 * @param length The number of characters to write
 */
void fb_write (char *buffer)
{
	/* Write every character to the framebuffer. */
	while (*buffer != '\0') {
		if (*buffer == '\n') {
			position += FB_WIDTH - (position % FB_WIDTH) - 1;
		} else {
			fb_write_cell(position * 2, *buffer, FB_WHITE, FB_BLACK);
		}

		buffer++;
		position++;
	}

	/* And put the cursor in the right place */
	fb_move_cursor(position);
}

/**
 * The clear method. This clears the entire screen by emptying out the
 * framebuffer variable.
 */
void fb_clear (void)
{
	/* Empty every element in the frame buffer. */
	for (position = 0; position < FB_WIDTH * FB_HEIGHT; position++) {
		fb_write_cell(position * 2, 0, FB_WHITE, FB_BLACK);
	}

	/* And put the cursor in the right place */
	fb_move_cursor(0);
}
