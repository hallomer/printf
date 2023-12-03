#include "main.h"

/**
 * handle_binary - Handles b specifier
 * @args: arguments list
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
*/
int handle_binary(va_list args, char *buffer, int *buffer_index)
{
	unsigned int num = va_arg(args, unsigned int);
	int count = write_number(0, num, 2, 0, buffer, buffer_index);

	if (*buffer_index == 1024)
		write_buffer(buffer, buffer_index);

	return (count);
}

/**
 * handle_unsigned_int - Handles u specifier
 * @args: arguments list
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
*/
int handle_unsigned_int(va_list args, char *buffer, int *buffer_index)
{
	unsigned int num = va_arg(args, unsigned int);
	int count = write_number(0, num, 10, 0, buffer, buffer_index);

	if (*buffer_index == 1024)
		write_buffer(buffer, buffer_index);

	return (count);
}

/**
 * handle_octal - Handles o specifier
 * @args: arguments list
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
*/
int handle_octal(va_list args, char *buffer, int *buffer_index)
{
	unsigned int num = va_arg(args, unsigned int);
	int count = write_number(0, num, 8, 0, buffer, buffer_index);

	if (*buffer_index == 1024)
		write_buffer(buffer, buffer_index);

	return (count);
}

/**
 * handle_hexadecimal - Handles x specifier
 * @args: arguments list
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
*/
int handle_hexadecimal(va_list args, char *buffer, int *buffer_index)
{
	unsigned int num = va_arg(args, unsigned int);
	int count = write_number(0, num, 16, 0, buffer, buffer_index);

	if (*buffer_index == 1024)
		write_buffer(buffer, buffer_index);

	return (count);
}

/**
 * handle_hexadecimal_upper - Handles X specifier
 * @args: arguments list
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
*/
int handle_hexadecimal_upper(va_list args, char *buffer, int *buffer_index)
{
	unsigned int num = va_arg(args, unsigned int);
	int count = write_number(0, num, 16, 1, buffer, buffer_index);

	if (*buffer_index == 1024)
		write_buffer(buffer, buffer_index);

	return (count);
}
