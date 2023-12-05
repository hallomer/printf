#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

typedef int (*FormatHandler)(va_list, char*, int*);

/**
 * struct FormatSpecifier - Format specifier and handler function
 * @specifier: character specifier
 * @handler: handler function for the specifier
 *
 * This structure associates a specifier with its handler function.
*/
typedef struct FormatSpecifier
{
	char specifier;
	FormatHandler handler;
} FormatSpecifier;

void write_buffer(char *buffer, int *buffer_index);
int _printf(const char *format, ...);
int handle_format(char specifier, va_list args,
		char *buffer, int *buffer_index);
int handle_unknown(char specifier, char *buffer, int *buffer_index);

int handle_char(va_list args, char *buffer, int *buffer_index);
int handle_string(va_list args, char *buffer, int *buffer_index);
int handle_percent(char *buffer, int *buffer_index);
int handle_pointer(va_list args, char *buffer, int *buffer_index);

int handle_decimal(va_list args, char *buffer, int *buffer_index);
int write_number(int is_negative, unsigned int num, int base,
		int uppercase, char *buffer, int *buffer_index);
char *convert_number(unsigned int num, int base, int uppercase);
int add_to_buffer(char *str, char *buffer, int *buffer_index);

int handle_binary(va_list args, char *buffer, int *buffer_index);
int handle_unsigned_int(va_list args, char *buffer, int *buffer_index);
int handle_octal(va_list args, char *buffer, int *buffer_index);
int handle_hexadecimal(va_list args, char *buffer, int *buffer_index);
int handle_hexadecimal_upper(va_list args, char *buffer, int *buffer_index);

int handle_custom_string(va_list args, char *buffer, int *buffer_index);
int handle_reversed_string(va_list args, char *buffer, int *buffer_index);
int handle_rot13(va_list args, char *buffer, int *buffer_index);

#endif
