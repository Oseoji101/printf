#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a char
 * @types: List of the arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates the active flags
 * @width: Width
 * @precision: Precision-specification
 * @size: Size-specifier
 * Return: Number of chars the printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, l;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (l = width - length; l > 0; l--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (l = width - length; l > 0; l--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Print the percent sign
 * @types: List num of arguments
 * @buffer: Buffer array to handle the print
 * @flags:  Calculates the active flags
 * @width: get a width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print an int
 * @types: List of the arguments
 * @buffer: Buffer array to handle a print
 * @flags:  Calculates the active flags
 * @width: get a width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of the chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int l = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[l--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[l--] = (num % 10) + '0';
		num /= 10;
	}

	l++;

	return (write_number(is_negative, l, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: List of the arguments
 * @buffer: Buffer array to handle the print
 * @flags:  Calculates the active flags
 * @width: get a width.
 * @precision: Precision of specification
 * @size: Size specifier
 * Return: Numbers of the char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int o, e, l, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	o = va_arg(types, unsigned int);
	e = 2147483648; /* (2 ^ 31) */
	a[0] = o / e;
	for (l = 1; l < 32; l++)
	{
		e /= 2;
		a[l] = (o / e) % 2;
	}
	for (l = 0, sum = 0, count = 0; l < 32; l++)
	{
		sum += a[l];
		if (sum || l == 31)
		{
			char z = '0' + a[l];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
