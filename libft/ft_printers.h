/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printers.h                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 11:38:11 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/18 20:27:33 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTERS_H
# define FT_PRINTERS_H

typedef struct s_flags
{
	int	alternate;
	int	zero_padded;
	int	left_adjustment;
	int	space_before_pos;
	int	plus_before_pos;
	int	precision;
	int	field_width;
}	t_flags;

int	ft_print_char(char c, t_flags flags);
int	ft_print_string(char *str, t_flags flags);
int	ft_print_int(int n, t_flags flags);
int	ft_print_uint(unsigned int n, t_flags flags);
int	ft_print_hex(unsigned long n, int uppercase, int is_pointer, t_flags flags);

int	ft_add_padding(int output_length, int field_with, char padding_char);

#endif