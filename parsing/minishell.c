/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mteffahi <mteffahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:10:06 by mteffahi          #+#    #+#             */
/*   Updated: 2025/06/16 17:56:15 by mteffahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_double_ptr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

void	print_env(struct passwd *env)
{
	printf("%s\n", env->pw_name);
	printf("%s\n", env->pw_passwd);
	printf("%d\n", (int)env->pw_uid);
	printf("%d\n", (int)env->pw_gid);
	printf("%s\n", env->pw_gecos);
	printf("%s\n", env->pw_dir);
	printf("%s\n", env->pw_shell);
}

void	print_ptr(t_ptr **head)
{
	t_ptr	*tmp;

	if (!*head)
		return ;
	tmp = *head;
	while (tmp && tmp->next)
	{
		printf("%p\n", tmp->ptr);
		tmp = tmp->next;
	}
}

int	ft_cmp(char *input, char *st)
{
	int	i;

	i = 0;
	while (input[i] && st[i])
	{
		if (input[i] != st[i])
			return 0;
		i++;
	}
	if (input[i] == '\0' && st[i] == '\0')  // Check if both strings ended
		return (1);
	return 1;
}

int main(int argc, char **argv, char **env) // wach ila m7iti env kamla wach getenv atl9a dak var li kt9allb 3lih fl expanding wla la, ila l9ato rah probleeeeem
{
	char *input;
	t_ptr	*head;

	(void)argc;
	(void)argv;
	head = NULL;
	add_node(&head, NULL);
	if (!head)
		return (ft_mall(NULL, -1), 0);
	print_double_ptr(env);
	while (1)
	{
		input = readline("Minishell --> : ");
		if (ft_cmp(input, "exit"))  // Fixed exit check
		{
			if (input)
				free(input);
			ft_mall(&head, -1);
			break;  // Exit the loop
		}

		add_history(input);
		// add_node(&head, input);
		// print_ptr(&head);
		pars(&head, ft_strdup(&head, input), env);
		free(input);
	}
	return (0);
}
