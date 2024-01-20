#include "monty.h"

/**
 * pint - opcode to print top node in stack
 * @head: head node of list
 * @line_num: line number bytecode
 */
void pint(stack_t **head, unsigned int line_num)
{
	if (!head || !*head)
	{
		fprintf(stderr, "L%u: can't pint, stack is empty\n", line_num);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*head)->n);
}

/**
 * pop - opcode to remove node at front of list
 * @head: head of linked list, at bottom of list
 * @line_num: line number bytecode
 */
void pop(stack_t **head, unsigned int line_num)
{
	if (!head || !*head)
	{
		fprintf(stderr, "L%u: can't pop, stack is empty\n", line_num);
		free_list(head);
		exit(EXIT_FAILURE);
	}

	delete_node(head);
}
