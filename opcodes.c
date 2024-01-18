#include "monty.h"

/**
* push - Pushes an element to the stack.
* @stack: Double pointer to the beginning of the stack.
* @line_num: Line number in the Monty bytecodes file.
*/
void push(stack_t **stack, unsigned int line_num)
{
char *arg_token = strtok(NULL, " \n");

if (!arg_token || (!isdigit(*arg_token) && *arg_token != '-'))
{
	fprintf(stderr, "L%u: usage: push integer\n", line_num);
	exit(EXIT_FAILURE);
}

if (!add_node(stack, atoi(arg_token)))
{
	fprintf(stderr, "Error: malloc failed\n");
	exit(EXIT_FAILURE);
}
}

/**
* pall - Prints all values on the stack.
* @stack: Pointer to the beginning of the stack.
* @line_num: Line number in the Monty bytecodes file.
*/
void pall(stack_t **stack, __attribute__((unused)) unsigned int line_num)
{
stack_t *current = *stack;

while (current)
{
	printf("%d\n", current->n);
	current = current->next;
}
}

/**
* add_node - Adds a new node to the stack.
* @stack: Double pointer to the beginning of the stack.
* @n: Value to be added to the new node.
* Return: Address of the new node, or NULL on failure.
*/
stack_t *add_node(stack_t **stack, int n)
{
stack_t *new_node = malloc(sizeof(stack_t));

if (!new_node)
	return (NULL);

new_node->n = n;
new_node->prev = NULL;

if (!*stack)
	new_node->next = NULL;
else
{
	new_node->next = *stack;
	(*stack)->prev = new_node;
}

*stack = new_node;
return (new_node);
}
