/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakariyahamdouchi <zakariyahamdouchi@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:39:06 by zhamdouc          #+#    #+#             */
/*   Updated: 2023/02/18 23:28:10 by zakariyaham      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parenthesis_close_2(char *str);
int	parenthesis_close_1(char *str);
//test : fkfs;sf      '''ho"''''l"a'''    'ho"''l"a'
//si rien apres pipe = probleme
// pour chaque if du parsinf check meme en skipant tout les espace qui separes les char
//comment gerer les "()"
// remplacer prinf par s_fd pour ecrire sur la sortie d'erreur
//pour $HOLA il fonctionne tout seul ou avec "$HOLA", on ne peut pas declarer une variable globale en commencant par un chiffre ou $, pas de caractere speciale, mais on peut mettre un chiffre dedans

extern int	g_exit_code[2];

int	after_pipe(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '|')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '\0')
			{
				s_fd("minishell: syntax error near unexpected token `|'\n", 2);
				g_exit_code[0] = 2;
				return (g_exit_code[0]);
			}
		}
		i++;
	}
	return (0);
}

static int	check_the_line_condition(char *line, int i)
{
	if ((line[i] == '"' && line[i + 1] == '"')
		|| (line[i] == '\'' && line[i + 1] == '\''))
		return (0);
	else
		return (1);
}

int	del_quote(char *line, int i, int j)
{
	while (line && line[i])
	{
		i = skip_quote(line, i);
		if (i == -1 || !line || line[i] == '\0')
			return (0);
		if (check_the_line_condition(line, i) == 0)
		{
			j = i;
			if (line[i + 2] == '\0')
			{
				line[j] = '\0';
				return (0);
			}
			while (line && line[j])
			{
				line[j] = line[j + 2];
				line [j + 1] = line [j + 3];
				j++;
			}
			i = 0;
		}
		else
			i++;
	}
	return (0);
}

int	first_pipe_check(char *line)
{
	int	i;

	i = 0;
	while ((line[i] > 7 && line[i] < 14) || line[i] == 32)
		i++;
	if (line[i] == '|')
	{
		s_fd("bash: syntax error near unexpected token `|'\n", 2);
		g_exit_code[0] = 2;
		return (1);
	}
	return (0);
}

int	parse(char *line)
{
	if (quote_close(line) == 0)
	{
		s_fd("Minishell : syntax error, quote not close\n", 2);
		g_exit_code[0] = 2;
		return (1);
	}
	if (first_pipe_check(line) == 1)
		return (1);
	if (check_parenthesis(line) == 1)
	{
		s_fd("Minishell : syntax error, parenthesis not close\n", 2);
		g_exit_code[0] = 2;
		return (1);
	}
	if (after_pipe(line) == 2)
		return (1);
	if (line[0] == ';')
	{
		s_fd("bash: syntax error near unexpected token `;'\n", 2);
		return (1);
	}
	if (check_1(line) == 1)
	{
		g_exit_code[0] = 2;
		return (1);
	}
	if (after_redirection(line) == 2)
		return (1);
	del_quote(line, 0, 0);
	if (ft_strlen(line) == 1)
	{
		if (line[0] == '>' || line[0] == '<')
		{
			s_fd("bash: syntax error near unexpected token `newline'\n", 2);
			g_exit_code[0] = 2;
			return (1);
		}
	}
	if (str_cmp(line, "<<") == 1 || str_cmp(line, ">>") == 1)
	{
		s_fd("bash: syntax error near unexpected token `newline'\n", 2);
		g_exit_code[0] = 2;
		return (1);
	}
	return (0);
}

/*
int parenthesis_close_1 (char *str)
{
	int i;
	int count_1;

	i = 0;
	count_1 = 0;

	while (str && str[i])
	{
		if (str[i] == '(')
			count_1++;
		i++;
	}
	i = 0;
	while (str && str[i])
	{
		if (str[i] == ')')
			count_1--;
		i++;
	}
	if (count_1 < 0)
	{
		s_fd("bash: syntax error near unexpected token `)'\n");
		return (1);
	}
	return (0);
}

int parenthesis_close_2 (char *str)
{
	char    c;
	int i;
	int count;

	i = 0;
	count = 0;
	if (!str)
			return (0);
	while(str && str[i])
	{
		while (str[i] == '(')
		{
			i++;
			count++;
		}
		if (count > 0)
		{
			while(str[i] == ')' || str[i] == ' ')
			{
				if (str[i] == ')')
					count--;
				i++;
			}
			if (count <= 0)
			{
				s_fd("bash: syntax error near unexpected token `)'\n");
				return (1);
			}
			return(0);
		}
		i++;
	}
	return (0);
}
*/
