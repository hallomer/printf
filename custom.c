#include "main.h"

/**
 * handle_custom_string - Handles S specifier
 * @args: arguments list
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
*/
int handle_custom_string(va_list args, char *buffer, int *buffer_index)
{
	int count = 0, i;
	char *str = va_arg(args, char *);

	if (str == NULL)
	{
		str = "(null)";
	}
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < 32 || str[i] >= 127)
		{
			buffer[(*buffer_index)++] = '\\';
			buffer[(*buffer_index)++] = 'x';
			sprintf(&buffer[*buffer_index], "%02X", (unsigned char)str[i]);
			*buffer_index += 2;
			count += 4;
			}
			else
			{
				buffer[(*buffer_index)++] = str[i];
				count++;
			}

			if (*buffer_index == 1024)
			{
				write_buffer(buffer, buffer_index);
			}
	}

	return (count);
}

/**
 * handle_custom_string - Handles S specifier
 * @args: arguments list
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
*/
int handle_custom_string(va_list args, char *buffer, int *buffer_index)
{
	int count = 0, i;
	char *str = va_arg(args, char *), hex[3];
	unsigned char c;

	if (str == NULL)
	{
		str = "(null)";
	}

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < 32 || str[i] >= 127)
		{
			buffer[(*buffer_index)++] = '\\';
			buffer[(*buffer_index)++] = 'x';
			c = (unsigned char)str[i];

			hex[0] = (c >> 4) < 10 ? (c >> 4) + '0' : (c >> 4) - 10 + 'A';
			hex[1] = (c & 0x0F) < 10 ? (c & 0x0F) + '0' : (c & 0x0F) - 10 + 'A';
			hex[2] = '\0';

			buffer[(*buffer_index)++] = hex[0];
			buffer[(*buffer_index)++] = hex[1];
			count += 4;
		}
		else
		{
			buffer[(*buffer_index)++] = str[i];
			count++;
		}

		if (*buffer_index == 1024)
		{
			write_buffer(buffer, buffer_index);
		}
	}

	return (count);
}

/**
 * handle_rot13 - Handles R specifier
 * @args: arguments list
 * @buffer: buffer
 * @buffer_index: current index
 *
 * Return: count
*/
int handle_rot13(va_list args, char *buffer, int *buffer_index)
{
	char *str = va_arg(args, char *), c;
	int count = 0;

	if (str == NULL)
		str = "(null)";

	while (*str != '\0')
	{
		c = *str;

		if (c >= 'a' && c <= 'z')
		{
			c = ((c - 'a' + 13) % 26) + 'a';
		}
		else if (c >= 'A' && c <= 'Z')
		{
			c = ((c - 'A' + 13) % 26) + 'A';
		}

		buffer[(*buffer_index)++] = c;
		if (*buffer_index == 1024)
			write_buffer(buffer, buffer_index);
		count++;

		str++;
	}
	return (count);
}
