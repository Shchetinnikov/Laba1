#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
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

/*void SetElement(void* element, void*value, int el_size) 
{

}
*/

int ShowMenu() 
{
	int i;

	printf("Menu:\n"
		"\t1. Addition\n"
		"\t2. Multiplication\n"
		"\t3. Multiplication by number\n"
		"\t4. Calculate function value by argument\n"
		"\t5. Composition\n"
		"\t6. Exit\n\n");

	printf("Input your number of item : ");
	i = getchar();
	CleanCh();
	printf("Your item: %c\n\n", i);
	
	return i;
}

void ReadString(Array* Polinom)  //считывает коэффициенты полинома 
{
	int code_error;
	Polinom->buffer = malloc(Polinom->el_size * (Polinom->count_element));
	
	do 
	{
		printf("Please, input polynomial coefficients (a(0), a(1) ...a(n-1), a(n)) by Space : ");
		code_error = 1;

		if (Polinom->el_size == sizeof(int)) 
		{
			for (int i = 0; i < Polinom->count_element; i++) 
			{
				code_error = scanf("%d", *((int*)Polinom->buffer + i));
				if (!code_error)
					break;
			}
			if (!code_error) 
			{
				CleanCh();
				printf("InputError: integer polynomial coefficients expected. Please, start from the beginning\n\n");
			}
			else 
			{
				CleanCh();
				printf("Successfully inputed\n");
			}
		}
		else 
		{
			for (int i = 0; i < Polinom->count_element; i++) 
			{
				code_error = scanf("%lf", *((double*)Polinom->buffer + i));
				if (!code_error)
					break;
			}
			if (!code_error) 
			{
				CleanCh();
				printf("InputError: double polynomial coefficients expected. Please, start from the beginning\n\n");
			}
			else 
			{
				CleanCh();
				printf("Successfully inputed\n\n");
			}
		}
	} while (code_error == 0);
}

int ChooseType()  // Запрашивает тип, возвращает размер типа 
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
		printf("Your input : %c\n\n", data_type);
		
		if (data_type != '1' && data_type != '2') 
		{
			printf("InputError: number of type of date doesn't exist. Please, repeat action\n\n");
			continue;
		}

		if (data_type == '1')
			data_type = sizeof(int);
		else
			data_type = sizeof(double);
		
		return data_type;
	}
}

/*void OutputPolinom(int* buffer, int count)
{
	for (int i = 0; i < count; i++) 
	{
		printf("%d\n", buffer[i]);
	}
}
*/

//обязательные/необязательные параметры функции в Си
Array* Create(int el_size, int num)  // создает и возвращает структуру "полином"
{
	int degree;
	int code_error;
	Array* Polinom = (Array*)malloc(sizeof(Array));
	
	Polinom->el_size = el_size;

	do  // запрашивает степень полинома 
	{
		printf("Please, input degree 'n' of polinomial %d: ", num);
		code_error = scanf("%d", &degree);
		CleanCh();	
		if (code_error == 0)
			printf("\nInputError: expected integer argument. Please, repeat action\n\n");
	} while (code_error == 0);
	
	Polinom->degree = degree;
	Polinom->count_element = degree + 1;
	printf("Your input : %d\n\n", degree);

	ReadString(Polinom);
	//OutputPolinom((int*)Polinom->buffer, Polinom->count_element);
	
	return Polinom;
}


Array* Addition(Array* Polinom1, Array* Polinom2, int el_size)
{
	int min_count = min(Polinom1->count_element, Polinom2->count_element);
	int max_count = max(Polinom1->count_element, Polinom2->count_element);
	
	Array* MaxPolinom;
	if (max_count == Polinom1->count_element)
		MaxPolinom = Polinom1;
	else
		MaxPolinom = Polinom2;

	Array* Polinom = malloc(sizeof(Array));
	Polinom->buffer = malloc(el_size * max_count);
	Polinom->el_size = el_size;
	Polinom->degree = max_count - 1;
	Polinom->count_element = max_count;

	if (el_size == sizeof(int)) 
	{
		int i;
		for (i = 0; i < min_count; i++)
			*((int*)Polinom->buffer + i) = *((int*)Polinom1->buffer + i) + *((int*)Polinom2->buffer + i);
		for (; i < max_count; i++) 
			*((int*)Polinom->buffer + i) = *((int*)MaxPolinom->buffer + i);
	
		while(*((int*)Polinom->buffer + max_count - 1) == 0)
		{
			Polinom->degree--;
			Polinom->count_element--;
			max_count--;
		}
	}
	else 
	{
		int i;
		for (i = 0; i < min_count; i++)
			*((double*)Polinom->buffer + i) = *((double*)Polinom1->buffer + i) + *((double*)Polinom2->buffer + i);
		for (; i < max_count; i++)
			*((double*)Polinom->buffer + i) = *((double*)MaxPolinom->buffer + i);
		
		while (*((double*)Polinom->buffer + max_count - 1) == 0) 
		{
			Polinom->degree--;
			Polinom->count_element--;
			max_count--;
		}
	}
	//OutputPolinom(Polinom->buffer, Polinom->count_element);
	
	return Polinom;
}