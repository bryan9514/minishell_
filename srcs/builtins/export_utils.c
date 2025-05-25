/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brturcio <brturcio@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:37:00 by brturcio          #+#    #+#             */
/*   Updated: 2025/05/20 15:47:17 by brturcio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_lstnew_env(t_env *content)
{
	t_env	*cont;

	cont = malloc(sizeof(t_env));
	if (!cont)
		return (NULL);
	cont->data = ft_strdup(content->data);
	if (!cont->data)
	{
		free(cont);
		return (NULL);
	}
	cont->var = ft_extract_var(cont->data);
	cont->value = ft_extract_value(cont->data);
	cont->exporte = content->exporte;
	cont->next = NULL;
	cont->prev = NULL;
	return (cont);
}

static void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*last_node;

	if (!*lst)
		*lst = new;
	else
	{
		last_node = *lst;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new;
		new->prev = last_node;
	}
}

t_env	*ft_cread_env_copy(t_env *env)
{
	t_env	*env_copy;
	t_env	*new_nodo;

	env_copy = NULL;
	new_nodo = NULL;
	while (env)
	{
		new_nodo = ft_lstnew_env(env);
		if (!new_nodo)
		{
			ft_free_env(env_copy);
			return (NULL);
		}
		ft_lstadd_back_env(&env_copy, new_nodo);
		env = env->next;
	}
	return (env_copy);
}

void	ft_swap_env_content(t_env *a, t_env *b)
{
	char	*tmp;
	int		tmp_exporte;

	tmp = a->data;
	a->data = b->data;
	b->data = tmp;
	tmp = a->var;
	a->var = b->var;
	b->var = tmp;
	tmp = a->value;
	a->value = b->value;
	b->value = tmp;
	tmp_exporte = a->exporte;
	a->exporte = b->exporte;
	b->exporte = tmp_exporte;
}

void	ft_sort_env_copy(t_env *head)
{
	t_env	*current;
	int		swap;

	swap = 1;
	while (swap)
	{
		swap = 0;
		current = head;
		while (current && current->next)
		{
			if (ft_strcmp(current->var, current->next->var) > 0)
			{
				ft_swap_env_content(current, current->next);
				swap = 1;
			}
			current = current->next;
		}
	}
}
