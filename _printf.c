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
	while (format[i] != '\0')
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
	int count;
	size_t num_handlers, i;
	FormatSpecifier format_handlers[] = {
		{'c', handle_char},
		{'s', handle_string},
		{'d', handle_decimal},
		{'i', handle_decimal},
		{'b', handle_binary},
		{'u', handle_unsigned_int},
		{'o', handle_octal},
		{'x', handle_hexadecimal},
		{'X', handle_hexadecimal_upper},
		{'S', handle_custom_string},
		{'p', handle_pointer},
		{'r', handle_reversed_string},
		{'R', handle_rot13},
	};

	if (specifier == '%')
	{
		return (handle_percent(buffer, buffer_index));
	}

	num_handlers = sizeof(format_handlers) / sizeof(FormatSpecifier);

	for (i = 0; i < num_handlers; i++)
	{
		if (format_handlers[i].specifier == specifier)
		{
			count = format_handlers[i].handler(args, buffer, buffer_index);
			return (count);
		}
	}

	count = handle_unknown(specifier, buffer, buffer_index);
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
