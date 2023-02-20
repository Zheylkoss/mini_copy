/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chekc_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakariyahamdouchi <zakariyahamdouchi@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:49:47 by zakariyaham       #+#    #+#             */
/*   Updated: 2023/02/16 18:50:13 by zakariyaham      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error_2_space(char *line, char c, char c_bis, int i)
{
	if (line[i] == c)
	{
		i++;
		while (line[i] == ' ')
			i++;
		if (line[i] == c_bis)
			return (2);
		else
			return (0);
	}
	return (0);
}

int	check_error_3_space(char *line, char c, char *c_bis, int i)
{
	if (line[i] == c)
	{
		i++;
		while (line[i] == ' ')
			i++;
		if (line[i] == c_bis[0] && line[i + 1] == c_bis[1])
			return (2);
		else
			return (0);
	}
	return (0);
}

int	check_error_space(char *line, char c, int i)
{
	if (line[i] == c)
	{
		i++;
		while (line[i] == ' ')
			i++;
		if (line[i] == c)
			return (2);
		else
			return (0);
	}
	return (0);
}
