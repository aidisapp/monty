#include "monty.h"

/**
* add_node - adds a new node to the beginning of a doubly linked list
* @head: pointer to the head of the linked list
* @n: integer data for the new node
* Return: 0 on success, -1 on failure
*/
int add_node(stack_t **head, int n)
{
stack_t *new_node = malloc(sizeof(stack_t));

if (!head)
	return (-1);

if (!new_node)
{
	printf("Error: memory allocation failed\n");
	return (-1);
}
new_node->n = n;

if (*head == NULL)
{
	*head = new_node;
	new_node->next = NULL;
	new_node->prev = NULL;
}
else
{
	new_node->next = *head;
	(*head)->prev = new_node;
	*head = new_node;
}

return (0);
}

/**
* delete_node - deletes the last node in a doubly linked list
* @head: pointer to the head node of the linked list
*/
void delete_node(stack_t *head)
{
stack_t *node_to_delete = NULL;

if (head->next == NULL)
{
	node_to_delete = head;
	head = NULL;
}
else
{
	node_to_delete = head;
	head = head->next;
	head->prev = NULL;
}

free(node_to_delete);
}

/**
* free_list - frees an int linked list
* @head: pointer to the head node of the doubly list
*/
void free_list(stack_t **head)
{
if (!head || !(*head))
	return;

while (*head && (*head)->next)
{
	*head = (*head)->next;
	free((*head)->prev);
}
free(*head);
}

/**
* push - Pushes an element to the stack.
* @head: Double pointer to the beginning of the stack.
* @line_num: Line number in the Monty bytecodes file.
*/
void push(stack_t **head, unsigned int line_num)
{
char *arg_token = strtok(NULL, " \n");

if (!arg_token || (!isdigit(*arg_token) && *arg_token != '-'))
{
	fprintf(stderr, "L%u: usage: push integer\n", line_num);
	exit(EXIT_FAILURE);
}

if (!add_node(head, atoi(arg_token)))
{
	free_list(head);
	fprintf(stderr, "Error: memory allocation failed\n");
	exit(EXIT_FAILURE);
}
}

/**
* pall - prints all nodes in the stack
* @head: pointer to the head of the stack
* @line_num: bytecode line number (unused in this function)
*/
void pall(stack_t **head, __attribute__((unused)) unsigned int line_num)
{
stack_t *temp_node = NULL;

if (!head || !*head)
	return;

temp_node = *head;
while (temp_node != NULL)
{
	printf("%d\n", temp_node->n);
	temp_node = temp_node->next;
}
}

