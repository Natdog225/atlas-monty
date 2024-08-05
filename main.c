#include "monty.h"

/**
 * main - Entry point of the Monty interpreter.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line arguments.
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int main(int argc, char *argv[])
{
	FILE *file;
	stack_t *stack = NULL;
	char line[1024];
	unsigned int line_number = 0;
	instruction_t instructions[] = {
		{"push", push},
		{"pall", pall},
		{NULL, NULL}};

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), file) != NULL)
	{
		line_number++;
		char *opcode = strtok(line, " \t\n");
		if (opcode && opcode[0] != '#')
		{
			int i = 0;
			while (instructions[i].opcode &&
				   strcmp(opcode, instructions[i].opcode) != 0)
			{
				i++;
			}

			if (instructions[i].opcode)
			{
				instructions[i].f(&stack, line_number);
			}
			else
			{
				fprintf(stderr,
						"L%u: unknown instruction %s\n", line_number, opcode);
				free_stack(stack);
				fclose(file);
				exit(EXIT_FAILURE);
			}
		}
	}

	free_stack(stack);
	fclose(file);
	return (EXIT_SUCCESS);
}
