#ifndef INCLUDE_FB_H
#define INCLUDE_FB_H

/** Define the framebuffer size. */
#define FB_WIDTH                80
#define FB_HEIGHT               25

/** The framebuffer colour constants. */
#define FB_BLACK                 0
#define FB_BLUE                  1
#define FB_GREEN                 2
#define FB_CYAN                  3
#define FB_RED                   4
#define FB_MAGENTA               5
#define FB_BROWN                 6
#define FB_LIGHT_GREY            7
#define FB_DARK_GREY             8
#define FB_LIGHT_BLUE            9
#define FB_LIGHT_GREEN          10
#define FB_LIGHT_CYAN           11
#define FB_LIGHT_RED            12
#define FB_LIGHT_MAGENTA        13
#define FB_LIGHT_BROWN          14
#define FB_WHITE                15

/** The I/O ports */
#define FB_COMMAND_PORT      0x3D4
#define FB_DATA_PORT         0x3D5

/** The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15


/**
 * The framebuffer variable. This sits at address 0x000B8000, and is treated as
 * a char pointer such that we can write to it.
 */
char *framebuffer;

/**
 * The position variable tracking where we are on the screen.
 */
unsigned int position;


/**
 * The write_cell method. This writes a character with the given foreground and
 * background to position i in the framebuffer.
 *
 * @param i  The location in the framebuffer
 * @param c  The character
 * @param fg The foreground colour
 * @param bg The background colour
 */
void fb_write_cell (unsigned int i, char c, unsigned char fg, unsigned char bg);

/**
 * The move_cursor method. This moves the cursor of the framebuffer to the
 * given position.
 *
 * @param pos The new position of the cursor
 */
void fb_move_cursor (unsigned short pos);

/**
 * The write method. This writes the contents of the buffer to the screen, and
 * automatically advances the cursor after a character has been written. The
 * screen is also scrolled if necessary.
 *
 * @param buf The buffer to write
 */
void fb_write (char *buffer);

/**
 * The clear method. This clears the entire screen by emptying out the
 * framebuffer variable.
 *
 */
void fb_clear (void);

#endif /* INCLUDE_FB_H */
