#include "main.h"

/**
 * write_buffer - Writes chars to stdo
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: nothing
*/
void write_buffer(char *buffer, int *buffer_index)
{
	write(1, buffer, *buffer_index);
	*buffer_index = 0;
}

/**
 * _printf - Produces output according to a format
 * @format: format string
 *
 * Return: number of chars printed
 */
int _printf(const char *format, ...)
{
	char buffer[1024];
	int buffer_index = 0;
	va_list args;
	int count = 0, i = 0;

	if (format == NULL)
		return (-1);

	va_start(args, format);
	while (format && format[i] != '\0')
	{
		if (format[i] != '%')
		{
			buffer[buffer_index++] = format[i];
			if (buffer_index == 1024)
				write_buffer(buffer, &buffer_index);
			count++;
		}
		else if (format[i + 1] == '\0')
		{
			break;
		}
		else
		{
			i++;
			count += handle_format(format[i], args, buffer, &buffer_index);
		}
		i++;
	}
	va_end(args);

	write_buffer(buffer, &buffer_index);
	return (count);
}

/**
 * handle_format - Handles specifiers
 * @specifier: specifier
 * @args: arguments list
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
*/
int handle_format(char specifier, va_list args,
		char *buffer, int *buffer_index)
{
	int count = 0;

	switch (specifier)
	{
		case 'c':
			count += handle_char(args, buffer, buffer_index);
			break;
		case 's':
			count += handle_string(args, buffer, buffer_index);
			break;
		case '%':
			count += handle_precent(buffer, buffer_index);
			break;
		case 'd':
		case 'i':
			count += handle_decimal(args, buffer, buffer_index);
			break;
		case 'b':
			count += handle_binary(args, buffer, buffer_index);
			break;
		case 'u':
			count += handle_unsigned_int(args, buffer, buffer_index);
			break;
		case 'o':
			count += handle_octal(args, buffer, buffer_index);
			break;
		case 'x':
			count += handle_hexadecimal(args, buffer, buffer_index);
			break;
		case 'X':
			count += handle_hexadecimal_upper(args, buffer, buffer_index);
			break;
		default:
			count += handle_unknown(specifier, buffer, buffer_index);
			break;
	}

	return (count);
}

/**
 * handle_unknown - Handles unknown specifier
 * @specifier: specifier
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
*/
int handle_unknown(char specifier, char *buffer, int *buffer_index)
{
	buffer[(*buffer_index)++] = '%';
	buffer[(*buffer_index)++] = specifier;
	if (*buffer_index == 1024)
		write_buffer(buffer, buffer_index);
	return (2);
}
