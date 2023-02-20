/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:54:57 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/17 17:57:59 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*
* creer le fichier si il existe et renvoie 1
* si le open a echouer renvoie -1
*
*/

int	check_output(t_input_output *output)
{
	int	fd;

	if (ft_strcmp(output->operator, ">"))
	{
		fd = open(output->file_name,
				O_WRONLY | O_CREAT | O_TRUNC, 0644, !O_DIRECTORY);
	}
	else if (ft_strcmp(output->operator, ">>"))
	{
		fd = open(output->file_name,
				O_WRONLY | O_CREAT | O_APPEND, 0644, !O_DIRECTORY);
	}
	if (fd == -1)
		return (-1);
	return (close(fd), 1);
}

int	check_input(t_input_output *output)
{
	int	fd;

	if (ft_strcmp(output->operator, "<"))
		fd = open(output->file_name, O_RDWR, O_DSYNC, !O_DIRECTORY);
	else if (ft_strcmp(output->operator, "<<"))
		return (1);
	if (fd == -1)
	{
		dprintf(2,"bad files Directorty %s\n", output->file_name);
		return (-1);
	}
	return (close(fd), 1);
}

int	check_input_output(t_input_output **input_output, t_garbage *garbage)
{
	t_input_output	*input;
	t_input_output	*output;
	t_input_output	*first;

	first = *input_output;
	input = NULL;
	output = NULL;
	while (*input_output)
	{
		if (ft_strcmp((*input_output)->operator, ">")
			|| ft_strcmp((*input_output)->operator, ">>"))
		{
			if (output)
				free_input_output_middle(&output, &first);
			output = (*input_output);
			if (check_output(output) == -1)
			{
				//dprintf(2, "1 output a pas ete valider \n");
				*input_output = first;
				free_garbage(garbage); // changer le exit code 
				return (-1);
			}
		}
		else if (ft_strcmp((*input_output)->operator, "<")
			|| ft_strcmp((*input_output)->operator, "<<"))
		{
			if (input)
				free_input_output_middle(&input, &first);
			input = (*input_output);
			if (check_input(input) == -1)
			{
				//dprintf(2, "2 input a pas ete valider \n");
				*input_output = first;
				free_garbage(garbage); // changer le exit code
				return (-1);
			}
		}
		*input_output = (*input_output)->next;
	}
	*input_output = first;
	return (1);
}
/*
int	check_inputs_outputs(t_maillons *maillons)
{
	while (maillons)
	{
		check_input_output(&(maillons)->output);
		maillons = (maillons)->next;
	}
	return (1);
}*/