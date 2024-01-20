#include "monty.h"

/**
* sub - Subtracts the top element of the stack from the second top element.
* @head: Double pointer to the beginning of the stack.
* @line_num: Line number in the Monty bytecodes file.
*/
void sub(stack_t **head, unsigned int line_num)
{
if (!head || !*head || !(*head)->next)
{
	fprintf(stderr, "L%u: can't sub, stack too short\n", line_num);
	free_list(head);
	exit(EXIT_FAILURE);
}

(*head)->next->n -= (*head)->n;
delete_node(head);
}

