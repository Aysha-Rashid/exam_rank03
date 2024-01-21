#include<stdarg.h>
#include<unistd.h>
#include<stdlib.h>
#include <stdio.h>

int	ft_string(char *str)
{
	int i = 0;

	if (!str)
		return(write(1, "(null)", 6));
	else
	{
		while (str[i])
		{

			write(1, &str[i], 1);
			i++;
		}
	}
	return (i);
}

int ft_putchar(char nb)
{
	return (write(1, &nb, 1));
}

int	ft_putnbr(int nb)
{
	int count = 0;

	if (nb == -2147483648)
	{
		count += write(1, "-2147483648", 11);
		return (count);
	}
	if (nb < 0)
	{
		count += write(1, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
		count += ft_putnbr(nb / 10);
	count += ft_putchar (nb % 10 + '0');
	return (count);
}

unsigned int	ft_hexa(unsigned int nb)
{
	int count = 0;

	if (nb >= 16)
	{
		count += ft_hexa(nb / 16);
		count += ft_hexa(nb % 16);
	}
	else if (nb < 16 && nb > 9)
		count += ft_putchar(nb - 10 + 'a');
	else
		count += ft_putchar(nb % 10 + '0');
	return (count);
}

int	ft_format(int specifier, va_list arg)
{
	int length = 0;

	if (specifier == 's')
		length = ft_string(va_arg(arg, char *));
	else if (specifier == 'd')
		length = ft_putnbr(va_arg(arg, int));
	else if (specifier == 'x')
		length = ft_hexa(va_arg(arg, unsigned int));
	return (length);
}

int ft_printf(const char *format, ...)
{
	int i = 0;
	int count = 0;
	va_list arg;

	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += ft_format(format[i + 1], arg);
			i++;
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(arg);
	return (count);
}

// int main()
// {
// 	// ft_printf("%x\n", (int)0xFFFFFFFF);
// 	// printf("%x\n", (int)0xFFFFFFFF);
// 	ft_printf("%x\n", 2147483647);
// 	printf("%x\n", 2147483647);

// }