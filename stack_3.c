#include "monty.h"

/**
 * mod - computes the rest of the division of the second and top element.
 * @stack: Pointer to top of the stack
 * @line_number: Instruction line number
 * Return: void
 */
void mod(stack_t **stack, unsigned int line_number)
{
	stack_t *copy = NULL;

	if (*stack == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	copy = *stack;
	if (copy->next == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n == 0)
	{
		dprintf(STDERR_FILENO, "L%d: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}
	copy->next->n = copy->next->n % (*stack)->n;
	*stack = copy->next;
	(*stack)->prev = NULL;
	free(copy);
}

/**
 * pchar -  prints the char at the top of the stack, followed by a new line
 * @stack: Pointer to top of the stack
 * @line_number: Instruction line number
 * Return: void
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	stack_t *copy = NULL;
	int count = 0;

	if (*stack == NULL)
	{
		dprintf(STDERR_FILENO, "L%d: can't pchar, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	copy = *stack;
	count = copy->n;
	if (count >= 1 && count <= 126)
	{
		putchar(count);
		putchar('\n');
	}
	else
	{
		dprintf(STDERR_FILENO, "L%d: can't pchar, value out of range\n",
		line_number);
		exit(EXIT_FAILURE);
	}
}

/**
 * pstr -prints the string starting at the top of the stack.
 * @stack: Pointer to top of the stack
 * @line_number: Instruction line number
 * Return: void
 */
void pstr(stack_t **stack, unsigned int line_number __attribute__((unused)))
{
	stack_t *copy = NULL;
	int count = 0;

	if (*stack != NULL)
	{
		copy = *stack;
		while (copy != NULL)
		{
			count = copy->n;
			if (count >= 1 && count <= 126)
			{
				putchar(count);
			}
			else
			{
				break;
			}
			copy = copy->next;
		}
		putchar('\n');
	}
	else
	{
		putchar('\n');
	}
}

/**
 * rotr - rotates the stack to the bottom.
 * @stack: Pointer to top of the stack
 * @line_number: Instruction line number
 * Return: void
 */
void rotr(stack_t **stack, unsigned int line_number __attribute__((unused)))
{
	stack_t  *copy = NULL;

	copy = *stack;

	if (*stack != NULL && (*stack)->next != NULL)
	{
		if ((*stack)->next->next == NULL)
		{
		copy = copy->next;
		(*stack)->prev = copy;
		(*stack)->next = NULL;
		copy->next = *stack;
		copy->prev = NULL;
		*stack = copy;
		}
		else
		{
		while (copy != NULL)
		{
			if ((*stack)->prev == NULL)
			{
				copy = copy->next;
				(*stack)->prev = copy;
				(*stack)->next = NULL;
				*stack = copy;
				copy = copy->next;
				(*stack)->next = (*stack)->prev;
			}
			(*stack)->prev = copy;
			*stack = copy;
			copy = copy->next;
			(*stack)->next = (*stack)->prev;
			(*stack)->prev = copy;
			}
		}
	}
}


/**
 * rotl - rotates the stack to the top.
 * @stack: Pointer to top of the stack
 * @line_number: Instruction line number
 * Return: void
 */
void rotl(stack_t **stack, unsigned int line_number __attribute__((unused)))
{
	stack_t  *copy = NULL, *aux = NULL;

	copy = *stack;
	aux = *stack;

	if (*stack != NULL && (*stack)->next != NULL)
	{
		if ((*stack)->next->next == NULL)
		{
			copy = copy->next;
			(*stack)->prev = copy;
			(*stack)->next = NULL;
			copy->next = *stack;
			copy->prev = NULL;
		}
		else
		{
			while (copy->next != NULL)
			{
				copy = copy->next;
			}
			*stack = (*stack)->next;
			aux->prev = copy;
			aux->next = NULL;
			copy->next = aux;
			(*stack)->prev = NULL;
		}
	}
}
