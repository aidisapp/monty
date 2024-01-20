#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

/**
* struct stack_s - doubly linked list representation of a stack (or queue)
* @n: integer
* @prev: points to the previous element of the stack (or queue)
* @next: points to the next element of the stack (or queue)
*
* Description: doubly linked list node structure
* for stack, queues, LIFO, FIFO
*/
typedef struct stack_s
{
int n;

struct stack_s *prev;
struct stack_s *next;
} stack_t;

/**
* struct instruction_s - opcode and its function
* @opcode: the opcode
* @f: function to handle the opcode
*
* Description: opcode and its function
* for stack, queues, LIFO, FIFO
*/
typedef struct instruction_s
{
char *opcode;
void (*f)(stack_t **stack, unsigned int line_number);

} instruction_t;

void (*get_instruction(char *token))(stack_t **head, unsigned int line_num);
void process_file(FILE *file, stack_t **stack_head);
void process_token(char *token, stack_t **stack_head, unsigned int line_num);

int add_node(stack_t **head, int n);
void delete_node(stack_t **head);
void free_list(stack_t **head);
void push(stack_t **head, unsigned int line_num, const char *token);
void pall(stack_t **head, __attribute__((unused)) unsigned int line_num);
void pint(stack_t **head, unsigned int line_num);
void pop(stack_t **head, unsigned int line_num);
void swap(stack_t **head, unsigned int line_num);
void add_op(stack_t **head, unsigned int line_num);
void nop(stack_t **head, unsigned int line_num);
void sub_op(stack_t **head, unsigned int line_num);
void div_op(stack_t **head, unsigned int line_num);
void mul_op(stack_t **head, unsigned int line_num);
void mod_op(stack_t **head, unsigned int line_num);

int is_digit(const char *str);

#endif
