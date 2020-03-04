#include <string.h>

typedef struct Array
{
	void* buffer;  // коэффициенты
	int degree;  // степень
	int count_element;
	int el_size;
} Array;

void CleanCh()
{
	while (getchar() != '\n')
		;
}

void Instroduce()
{
	printf("Polinomial: P(n)(x) = a(n) * x^n + a(n - 1) * x^(n - 1) + ... + a(1) * x^1 + a(0) * x^0\n"
		"\t\t n - degree of polinomial\n"
		"\t\t x - argument\n"
		"\t\t a(n) - coefficient of argument x^n\n\n");
}

int Menu() // Выводит меню, запрашивает и возвращает пункт
{
	int item;

	printf("Menu:\n"
		"\t1. Addition\n"
		"\t2. Multiplication\n"
		"\t3. Multiplication by constant\n"
		"\t4. Calculate function value by argument\n"
		"\t5. Composition\n"
		"\t6. Back\n"
		"\t7. Exit\n\n");

	printf("Input your number of item: ");
	item = getchar();
	CleanCh();
	printf("Your input: %c\n\n", item);

	return item;
}

int ElementType()  // Запрашивает тип, возвращает размер типа 
{
	int data_type;
	while (1)
	{
		printf("Types of data:\n"
			"\t 1. Integer\n"
			"\t 2. Double\n\n");

		printf("Input number of type of data: ");
		data_type = getchar();
		CleanCh();
		printf("Your input: %c\n\n", data_type);

		if (data_type != '1' && data_type != '2')
		{
			printf("InputError: number of type of date doesn't exist. Please, try again.\n\n");
			continue;
		}

		if (data_type == '1')
			data_type = sizeof(int);
		else
			data_type = sizeof(double);

		return data_type;
	}
}