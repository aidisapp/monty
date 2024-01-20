#include "monty.h"

/**
* sub_op - Subtracts the top element of the stack from the second top element.
* @head: Double pointer to the beginning of the stack.
* @line_num: Line number in the Monty bytecodes file.
*/
void sub_op(stack_t **head, unsigned int line_num)
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

/**
* div_op - Divides the second top element of the stack by the top element.
* @head: Double pointer to the beginning of the stack.
* @line_num: Line number in the Monty bytecodes file.
*/
void div_op(stack_t **head, unsigned int line_num)
{
if (!head || !*head || !(*head)->next)
{
	fprintf(stderr, "L%u: can't div, stack too short\n", line_num);
	free_list(head);
	exit(EXIT_FAILURE);
}

if ((*head)->n == 0)
{
	fprintf(stderr, "L%u: division by zero\n", line_num);
	free_list(head);
	exit(EXIT_FAILURE);
}

(*head)->next->n /= (*head)->n;
delete_node(head);
}

/**
* mul_op - Multiplies the second top element of the stack with the top element.
* @head: Double pointer to the beginning of the stack.
* @line_num: Line number in the Monty bytecodes file.
*/
void mul_op(stack_t **head, unsigned int line_num)
{
if (!head || !*head || !(*head)->next)
{
	fprintf(stderr, "L%u: can't mul, stack too short\n", line_num);
	free_list(head);
	exit(EXIT_FAILURE);
}

(*head)->next->n *= (*head)->n;
delete_node(head);
}

/**
* mod_op - Computes the rest of the division of the second
* top element by the top element.
* @head: Double pointer to the beginning of the stack.
* @line_num: Line number in the Monty bytecodes file.
*/
void mod_op(stack_t **head, unsigned int line_num)
{
if (!head || !*head || !(*head)->next)
{
	fprintf(stderr, "L%u: can't mod, stack too short\n", line_num);
	free_list(head);
	exit(EXIT_FAILURE);
}

if ((*head)->n == 0)
{
	fprintf(stderr, "L%u: division by zero\n", line_num);
	free_list(head);
	exit(EXIT_FAILURE);
}

(*head)->next->n %= (*head)->n;
delete_node(head);
}

/**
* pchar - Prints the char at the top of the stack.
* @head: Double pointer to the beginning of the stack.
* @line_num: Line number in the Monty bytecodes file.
*/
void pchar(stack_t **head, unsigned int line_num)
{
if (!head || !*head)
{
	fprintf(stderr, "L%u: can't pchar, stack empty\n", line_num);
	free_list(head);
	exit(EXIT_FAILURE);
}

if ((*head)->n < 0 || (*head)->n > 127)
{
	fprintf(stderr, "L%u: can't pchar, value out of range\n", line_num);
	free_list(head);
	exit(EXIT_FAILURE);
}

putchar((*head)->n);
putchar('\n');
}
