# Simple Garbage Collector

A simple garbage collector to automatically collect all allocated memory and free it at program exit. This helps prevent memory leaks caused by forgotten frees during program execution.

I found it particularly useful for the projects [minishell](https://github.com/deniz-oezdemir/Minishell) and [miniRT](https://github.com/deniz-oezdemir/miniRT) at school 42.


## Features

- Compliant with school 42's norminette and less than 50 lines of code.
- Acts as a wrapper around `ft_calloc` with additional collection of all allocated memory in a linked list.
- Checks for memory allocation failure.

## Installation and Usage

1. Add the following three functions from [garbage_collector.c](./garbage_collector.c) to your project:

	```c
	void *gc_calloc(t_list **head, size_t nmemb, size_t size);
	void gc_add_to_list(t_list **head, void *new);
	void gc_free_all(t_list *head);
	```

2. Declare a pointer to the head node of a linked list:

	```c
	t_list *head;
	head = NULL;
	```

3. Use `gc_calloc` (instead of `ft_calloc` or `malloc`) and pass it the address of the pointer to the linked list's head whenever you want to allocate memory.

4. Call `gc_free_all(head)` just before program termination to free all allocated memory.

If the above explanation is too abstract, you can refer to the tests in the main function at the bottom of [garbage_collector.c](./garbage_collector.c) to gain a better intuition.

## Testing

To test the garbage collector, follow these steps:

1. Clone this repository and compile the `libft` library:

	```bash
	git clone https://github.com/deniz-oezdemir/simple-garbage-collector
	cd simple-garbage-collector
	git submodule update --init --recursive
	cd libft
	make
	cd ..
	```

2. Compile the garbage collector with the `libft` library:

	```bash
	cc garbage_collector.c ./libft/libft.a
	```

3. Run the program with `valgrind` to check for memory leaks:

	```bash
	valgrind --leak-check=full ./a.out
	```

The output should show no memory leaks.

## Dependencies

The garbage collector has few dependencies on the following functions and data structure from the [libft](https://github.com/deniz-oezdemir/libft) project: `ft_calloc`, `ft_putstr_fd`, and the `t_list` definition.

In addition to those dependencies, the test in the main function also relies on `ft_putnbr_fd` and `ft_strlcpy` from the [libft](https://github.com/deniz-oezdemir/libft).

## Additional Information

For each use of `gc_calloc`, you will notice two allocations. This is because `gc_calloc` allocates memory for both the data itself and a node to store the pointer to the allocated memory.

If you need to free specific allocated memory during program execution and not just at program exit, you can still manually allocate and free memory using `malloc`, `ft_calloc`, and `free`.

If you found this helpful or have any suggestions for improvements, I would love to hear from you! Feel free to reach out or make a pull request to contribute. Your feedback and contributions are greatly appreciated.

