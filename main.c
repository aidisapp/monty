#include "monty.h"

/**
 * free_stack - Frees the memory associated with a stack.
 * @stack: Double pointer to the beginning of the stack.
 */

void free_stack(stack_t **stack)
{
	stack_t *current = *stack;
	stack_t *next;

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	*stack = NULL;
}

/**
 * get_instructions - Get Monty bytecode instructions.
 * Return: Array of instruction_t structures.
 */

instruction_t *get_instructions(void)
{
	static instruction_t instructions[] = {
			{"push", push},
			{"pall", pall},
			{NULL, NULL}};

	return (instructions);
}

/**
 * execute_instruction - Executes a Monty bytecode instruction.
 * @stack: Double pointer to the beginning of the stack.
 * @line: The instruction line from the Monty bytecode file.
 * @line_number: Line number in the Monty bytecode file.
 */

void execute_instruction(stack_t **stack, char *line, unsigned int line_number)
{
	char *opcode = strtok(line, " \t\n");
	instruction_t *instructions = get_instructions();

	if (opcode == NULL || opcode[0] == '#')
	{
		free(instructions);
		return;
	}
	while (instructions->opcode)
	{
		if (strcmp(opcode, instructions->opcode) == 0)
		{
			instructions->f(stack, line_number);
			free(instructions);
			return;
		}
		instructions++;
	}
	fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
	free(instructions);
	exit(EXIT_FAILURE);
}

/**
 * main - Monty bytecode interpreter.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */

int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	unsigned int line_number = 0;
	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		return (EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}

	while (getline(&line, &len, file) != -1)
	{
		line_number++;
		execute_instruction(&stack, line, line_number);
	}

	free_stack(&stack);
	fclose(file);
	if (line)
		free(line);

	return (EXIT_SUCCESS);
}

