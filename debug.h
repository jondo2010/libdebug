//
//	debug.h
//	Quick-and-dirty debug library for AVR-based micro-controllers.
//
//	Michael Jean <michael.jean@shaw.ca>
//

//
//	The debug library makes use of the USART on the ATMEGA168 (USART0).
//	Future implementations for the AT90CAN128 will allow selection of the
//	desired USART for debugging output.
//

#ifndef _DEBUG_H
#define _DEBUG_H

#include <stdio.h>

//
//	By default, we output at 9600 baud, 8N1.
//

#define BAUD_RATE 9600

//
//	Debug levels. When set to level `n', all messages less than `n'
//	are suppressed.
//

typedef enum debug_level_t
{
	notice,
	warning,
	error,
	fatal
}
debug_level_t;

//
//	Initialize the debug system.
//

void
debug_init
(
	debug_level_t level
);

//
//	Write a character to the serial console. Used by the internal printf
//	functions as an fdev.
//

int
debug_putchar
(
	char c,
	FILE *stream
);

//
//	Print a debug message to the serial console.
//

void
debug_print
(
	debug_level_t	level,
	char 			*fmt,
	...
);

#endif /* _DEBUG_H */
