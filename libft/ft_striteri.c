/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_striteri.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tsteur <tsteur@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:23:34 by tsteur        #+#    #+#                 */
/*   Updated: 2023/10/05 23:26:28 by tsteur        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char const *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, (char *) &s[i]);
		i++;
	}
}
