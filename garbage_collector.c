/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:49:30 by denizozd          #+#    #+#             */
/*   Updated: 2024/09/17 11:49:32 by denizozd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

/* Frees all the elements in the linked list and their content. */

void	gc_free_all(t_list *head)
{
	t_list	*curr;
	t_list	*next;

	curr = head;
	while (curr)
	{
		next = curr->next;
		if (curr->content)
			free(curr->content);
		free(curr);
		curr = next;
	}
}

/* Adds a new element to the end of the linked list. */

void	gc_add_to_list(t_list **head, void *new)
{
	t_list	*node;
	t_list	*tmp;

	node = ft_calloc(1, sizeof(t_list));
	if (!node)
	{
		ft_putstr_fd("Error: Failed to allocate memory\n", 2);
		return ;
	}
	node->content = new;
	node->next = NULL;
	if (!(*head))
	{
		(*head) = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

/* Allocates memory for an array of nmemb elements of size bytes each and adds
the allocated memory to the linked list by calling gc_add_to_list. */

void	*gc_calloc(t_list **head, size_t nmemb, size_t size)
{
	void	*new;

	new = ft_calloc(nmemb, size);
	if (!new)
	{
		ft_putstr_fd("Error: Failed to allocate memory\n", 2);
		return (NULL);
	}
	gc_add_to_list(head, new);
	return (new);
}



/* Below main function demonstrates the usage of above garbage collector.
It allocates memory for an array of integers and a series of strings,
initializes and prints their values, and ensures all allocated memory
is properly freed before the program exits. */

int	main()
{
	t_list	*head = NULL;
	int		i = 0;

	// Allocate memory for an array of integers and place numbers from 1 to 5 in it
	int *arr = gc_calloc(&head, 5, sizeof(int));
	if (arr != NULL)
	{
		while (i < 5)
		{
			arr[i] = i + 1;
			ft_putnbr_fd(arr[i], 1);
			i++;
		}
	}
	ft_putstr_fd("\n", 1);

	// Allocate memory for 10 strings and copy the word "Hello" into each
	i = 0;
	while (i < 10)
	{
		char *str = gc_calloc(&head, 8, sizeof(char));
		if (str != NULL) {
			ft_strlcpy(str, "Hello\n", 8);
			ft_putstr_fd(str, 1);
		}
		i++;
	}

	// Free all allocated memory using a single function call before the program terminates
	gc_free_all(head);

	return 0;
}

