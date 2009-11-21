//
//	debug.c
//	Quick-and-dirty debug library for AVR-based micro-controllers.
//
//	Michael Jean <michael.jean@shaw.ca>
//

#include <stdio.h>
#include <avr/io.h>

#include "debug.h"

static debug_level_t min_level;
static FILE mystdout = FDEV_SETUP_STREAM (debug_putchar, NULL, _FDEV_SETUP_WRITE);

void
debug_init
(
	debug_level_t	level
)
{
	min_level = level;

	stdout = &mystdout;

	UBRR0 = (uint16_t)(F_CPU / 16 / BAUD_RATE) - 1;
	UCSR0B |= _BV (TXEN0);
}

//
//	1.	This maps the printf functions to use our own debug_putchar function to
//		do character writes. See the AVR libc documentation on stdio.h for more
//		information as to how this works.
//

int
debug_putchar
(
	char c,
	FILE *stream
)
{
	if (c == '\n')
		debug_putchar ('\r', stream);

	loop_until_bit_is_set (UCSR0A, UDRE0); /* 1 */
	UDR0 = c;

	return 0;
}

//
//	1. 	The libc printf functions are all blocking, so we don't use interrupts
//		and buffering like the USART library does.
//

void
debug_print
(
	debug_level_t	level,
	char 			*fmt,
	...
)
{
	va_list	argptr;

	if (level >= min_level)
	{
		va_start (argptr, fmt);
		vfprintf(stdout, fmt, argptr);
		va_end (argptr);
	}
}

