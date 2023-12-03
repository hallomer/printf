#include "main.h"

/**
 * handle_decimal - Handles d and i specifiers
 * @args: arguments list
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
*/
int handle_decimal(va_list args, char *buffer, int *buffer_index)
{
	int d = va_arg(args, int);
	int count = 0;

	if (d < 0)
	{
		buffer[(*buffer_index)++] = '-';
		if (*buffer_index == 1024)
			write_buffer(buffer, buffer_index);
		count++;
		d *= -1;
	}

	count += write_number(0, d, 10, 0, buffer, buffer_index);

	if (*buffer_index == 1024)
		write_buffer(buffer, buffer_index);

	return (count);
}

/**
 * write_number - Writes numbers
 * @is_negative: flag
 * @num: number to write
 * @base: base of the number
 * @uppercase: flag for uppercase hexadecimal
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
 */
int write_number(int is_negative, unsigned int num, int base,
		int uppercase, char *buffer, int *buffer_index)
{
	int count = 0;
	char *num_str;

	if (is_negative)
	{
		write(1, "-", 1);
		count++;
	}
	if (num == 0)
	{
		write(1, "0", 1);
		count++;
	}
	else
	{
		num_str = convert_number(num, base, uppercase);
		count += add_to_buffer(num_str, buffer, buffer_index);
		free(num_str);
	}

	return (count);
}

/**
 * convert_number - Converts number to string representation
 * @num: number to convert
 * @base: base of the number
 * @uppercase: flag for uppercase hexadecimal
 *
 * Return: string representation of the number
 */
char *convert_number(unsigned int num, int base, int uppercase)
{
	int digits = 0, i;
	unsigned int temp = num, digit;
	char digit_char;
	char *num_str;

	while (temp != 0)
	{
		temp /= base;
		digits++;
	}

	num_str = malloc((digits + 1) * sizeof(char));

	for (i = digits - 1; i >= 0; i--)
	{
		digit = num % base;
		digit_char = (digit < 10) ? ('0' + digit) :
			(uppercase ? 'A' + digit - 10 : 'a' + digit - 10);
		num_str[i] = digit_char;
		num /= base;
	}

	return (num_str);
}

/**
 * add_to_buffer - Writes string to buffer
 * @str: string to write
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
 */
int add_to_buffer(char *str, char *buffer, int *buffer_index)
{
	int count = 0;
	int i = 0;

	while (str[i] != '\0')
	{
		buffer[(*buffer_index)++] = str[i++];
		if (*buffer_index == 1024)
			write_buffer(buffer, buffer_index);
		count++;
	}

	return (count);
}
