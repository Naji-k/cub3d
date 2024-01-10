/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/13 13:54:07 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/19 09:54:22 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "libft.h"

#include "ft_printers.h"

static int	read_and_skip_number(const char *format, int *i, va_list *ap)
{
	int	number;

	if (format[*i] == '*')
	{
		(*i)++;
		return (va_arg(*ap, int));
	}
	number = ft_atoi(&format[*i]);
	while (ft_isdigit(format[*i]))
		(*i)++;
	return (number);
}

static t_flags	handle_flags(const char *format, int *i, va_list *ap)
{
	t_flags	flags;

	flags = (t_flags){0, 0, 0, 0, 0, -1, 0};
	while (ft_strchr("# +0-", format[*i]))
	{
		if (format[*i] == '#')
			flags.alternate = 1;
		else if (format[*i] == ' ')
			flags.space_before_pos = 1;
		else if (format[*i] == '+')
			flags.plus_before_pos = 1;
		else if (format[*i] == '0')
			flags.zero_padded = 1;
		else if (format[*i] == '-')
			flags.left_adjustment = 1;
		(*i)++;
	}
	flags.field_width = read_and_skip_number(format, i, ap);
	if (format[*i] == '.')
	{
		(*i)++;
		flags.precision = read_and_skip_number(format, i, ap);
	}
	return (flags);
}

static int	do_convertion(char format_chr, va_list *ap, t_flags flags)
{
	if (format_chr == '%')
		return (ft_print_char('%', flags));
	if (format_chr == 'c')
		return (ft_print_char(va_arg(*ap, int), flags));
	if (format_chr == 's')
		return (ft_print_string(va_arg(*ap, char *), flags));
	if (format_chr == 'd' || format_chr == 'i')
		return (ft_print_int(va_arg(*ap, int), flags));
	if (format_chr == 'u')
		return (ft_print_uint(va_arg(*ap, unsigned int), flags));
	if (format_chr == 'x')
		return (ft_print_hex(va_arg(*ap, unsigned int), 0, 0, flags));
	if (format_chr == 'X')
		return (ft_print_hex(va_arg(*ap, unsigned int), 1, 0, flags));
	if (format_chr == 'p')
		return (ft_print_hex(va_arg(*ap, unsigned long), 0, 1, flags));
	return (0);
}

static int	print_intermediate(const char *format, int *i)
{
	int	intermediate_length;

	if (ft_strchr(&format[*i], '%'))
		intermediate_length = ft_strchr(&format[*i], '%') - &format[*i];
	else
		intermediate_length = ft_strlen(&format[*i]);
	write(STDOUT_FILENO, &format[*i], intermediate_length);
	(*i) += intermediate_length;
	return (intermediate_length);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		out_length;
	int		conversion_length;
	t_flags	flags;
	int		i;

	va_start(ap, format);
	out_length = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			flags = handle_flags(format, &i, &ap);
			conversion_length = do_convertion(format[i++], &ap, flags);
			if (conversion_length < 0)
				return (-1);
			out_length += conversion_length;
		}
		else
			out_length += print_intermediate(format, &i);
	}
	va_end(ap);
	return (out_length);
}
