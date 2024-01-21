#include "monty.h"

/**
* pstr - Prints the string starting at the top of the stack.
* @head: Double pointer to the beginning of the stack.
* @line_num: Line number in the Monty bytecodes file.
*/
void pstr(stack_t **head, __attribute__((unused)) unsigned int line_num)
{
stack_t *temp_node = *head;

while (temp_node != NULL && temp_node->n != 0 && temp_node->n >= 0
&& temp_node->n <= 127)
{
	putchar(temp_node->n);
	temp_node = temp_node->next;
}

putchar('\n');
}

