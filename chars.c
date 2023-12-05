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

/**
 * handle_pointer - Handles p specifier
 * @args: arguments list
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
*/
int handle_pointer(va_list args, char *buffer, int *buffer_index)
{
	void *ptr = va_arg(args, void*);
	unsigned long address = (unsigned long)ptr, temp, digit_value;
	int count = 0, num_digits, i;
	char hex_digits[] = "0123456789abcdef";

	buffer[(*buffer_index)++] = '0';
	buffer[(*buffer_index)++] = 'x';
	count += 2;

	num_digits = 0;
	temp = address;
	while (temp != 0)
	{
		temp /= 16;
		num_digits++;
	}

	for (i = num_digits - 1; i >= 0; i--)
	{
		digit_value = (address >> (i * 4)) & 0xf;
		buffer[(*buffer_index)++] = hex_digits[digit_value];
		count++;
	}

	return (count);
}
