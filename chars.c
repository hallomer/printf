#include "main.h"

/**
 * handle_char - Handles c specifier
 * @args: arguments list
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
*/
int handle_char(va_list args, char *buffer, int *buffer_index)
{
	char c = (char)va_arg(args, int);

	buffer[(*buffer_index)++] = c;
	if (*buffer_index == 1024)
		write_buffer(buffer, buffer_index);

	return (1);
}

/**
 * handle_string - Handles s specifier
 * @args: arguments list
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
*/
int handle_string(va_list args, char *buffer, int *buffer_index)
{
	int count = 0, i;
	char *str = va_arg(args, char *);

	if (str == NULL)
		str = "(null)";

	for (i = 0; str[i] != '\0'; i++)
	{
		buffer[(*buffer_index)++] = str[i];
		if (*buffer_index == 1024)
			write_buffer(buffer, buffer_index);

		count++;
	}
	return (count);
}

/**
 * handle_precent - Handles % specifier
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
*/
int handle_precent(char *buffer, int *buffer_index)
{
	buffer[(*buffer_index)++] = '%';
	if (*buffer_index == 1024)
		write_buffer(buffer, buffer_index);

	return (1);
}
