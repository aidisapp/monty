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
	if (head == NULL || *head == NULL)
	{
		fprintf(stderr, "L%u: can't pop, stack is emoty\n", line_num);
		free_list(head);
		exit(EXIT_FAILURE);
	}
	else
		delete_node(head);
}

/**
 * swap - Swaps the top two elements of the stack.
 * @head: Double pointer to the beginning of the stack.
 * @line_num: Line number in the Monty bytecodes file.
 */
void swap(stack_t **head, unsigned int line_num)
{
	int temp;

	if (!head || !*head || !(*head)->next)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_num);
		free_list(head);
		exit(EXIT_FAILURE);
	}

	temp = (*head)->n;
	(*head)->n = (*head)->next->n;
	(*head)->next->n = temp;
}

/**
 * add_op - Adds the top two elements of the stack.
 * @head: Double pointer to the beginning of the stack.
 * @line_num: Line number in the Monty bytecodes file.
 */
void add_op(stack_t **head, unsigned int line_num)
{
	if (!head || !*head || !(*head)->next)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_num);
		free_list(head);
		exit(EXIT_FAILURE);
	}

	(*head)->next->n += (*head)->n;
	delete_node(head);
}

/**
 * nop - Does nothing.
 * @head: Double pointer to the beginning of the stack.
 * @line_num: Line number in the Monty bytecodes file.
 */
void nop(stack_t **head, unsigned int line_num)
{
	(void)head;
	(void)line_num;
}
