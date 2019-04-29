#ifndef INCLUDE_UTIL_H
#define INCLUDE_UTIL_H


/**
 * The print method. This prints the contents of the buffer to the the specified
 * output, and automatically advances the cursor after a character has been
 * written, if the output is the screen. The screen is also scrolled if
 * necessary.
 *
 * @param com    The COM port
 * @param buffer The buffer to write
 */
void print (unsigned int com, char* buffer);

#endif /* INCLUDE_UTIL_H */
