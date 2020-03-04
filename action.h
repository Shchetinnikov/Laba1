#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "interface.h"

//считывает коэффициенты полинома 
void ReadCoefficients(Array* Polinom)
{
	int error_code;
	Polinom->buffer = malloc(Polinom->el_size * (Polinom->count_element));
	
	do 
	{
		printf("Please, input polynomial coefficients a(0), a(1) ...a(n-1), a(n) by Space : ");
		error_code = 1;

		switch(Polinom->el_size)
		{
			case sizeof(int):
			{
				for (int i = 0; i < Polinom->count_element; i++)
				{
					error_code = scanf("%d", (int*)Polinom->buffer + i);
					if (!error_code)
					{
						CleanCh();
						break;
					}
				}
				
				error_code ? printf("Successfully completed\n\n") : printf("InputError: expected integer polynomial coefficients. "
																			 "Please, try again.\n\n");
				break;
			}
			case sizeof(double):
			{
				for (int i = 0; i < Polinom->count_element; i++)
				{
					error_code = scanf("%lf", (double*)Polinom->buffer + i);
					if (!error_code)
					{
						CleanCh();
						break;
					}
				}
				error_code ? printf("Successfully completed\n\n") : printf("InputError: expected double polynomial coefficients. " 
																		     "Please, try again.\n\n");				
				break;
			}
		}
	} while (!error_code);
}

//вывод полинома в полной форме
void OutputPolinom(Array* Polinom)
{
	int i;
	printf("P(%d)(x) = ", Polinom->degree);
	switch (Polinom->el_size)
	{
		case sizeof(int):
		{
			for (i = Polinom->count_element - 1; i >= 0; i--)
				if (*((int*)Polinom->buffer + i) < 0)
				{
					printf("(%d) * x^%d", *((int*)Polinom->buffer + i), i);
					printf(i ? " + " : "");
				}
				else 
				{					
						printf("%d * x^%d", *((int*)Polinom->buffer + i), i);
						printf(i ? " + " : "");
				}
			break;
		}
		case sizeof(double):
		{
			for (i = Polinom->count_element - 1; i >= 0; i--)
				if (*((double*)Polinom->buffer + i) < 0)
				{
					printf("(%lf) * x^%d", *((double*)Polinom->buffer + i), i);
					printf(i ? " + " : "");
				}
				else
				{
					printf("%lf * x^%d", *((double*)Polinom->buffer + i), i);
					printf(i ? " + " : "");
				}
			break;
		}
	}
	printf("\n\n");
}

// удаляет нулевые коэффициенты при старших степенях
void ZeroCoefficients(Array* Polinom) 
{
	switch (Polinom->el_size)
	{
		case sizeof(int):
		{
			while (*((int*)Polinom->buffer + Polinom->count_element - 1) == 0)
			{
				Polinom->degree--;
				Polinom->count_element--;
				//освобождение адреса
			}
		}
		case sizeof(double):
		{
			while (*((double*)Polinom->buffer + Polinom->count_element - 1) == 0)
			{
				Polinom->degree--;
				Polinom->count_element--;
				//освобождение адреса
			}
		}
	}
}

// создает и возвращает структуру "полином" с порядковым номером num
// из заданного типа (num = 0 - полином без порядкового номера)
Array* Create(int el_size, int num)  
{									
	int degree;
	int error_code;
	Array* Polinom = (Array*)malloc(sizeof(Array));
	
	do  // запрашивает степень полинома 
	{
		num ? printf("Please, input degree 'n' of polinomial %d: ", num) : printf("Please, input degree 'n' of polinomial: ");
		
		error_code = scanf("%d", &degree);
		CleanCh();
		if (!error_code) 
		{
			printf("InputError: expected integer argument. Please, try again.\n\n");
			continue;
		}
		printf("Your input: %d\n\n", degree);
	} while (!error_code);
	
	Polinom->degree = degree;
	Polinom->count_element = degree + 1;
	Polinom->el_size = el_size;

	ReadCoefficients(Polinom);
	ZeroCoefficients(Polinom);
	OutputPolinom(Polinom);
	
	return Polinom;
}

// складывает 2 полинома
Array* Addition(Array* Polinom1, Array* Polinom2)
{
	int i;
	int min_count = min(Polinom1->count_element, Polinom2->count_element);
	int max_count = max(Polinom1->count_element, Polinom2->count_element);

	Array* MaxPolinom;
	if (max_count == Polinom1->count_element)
		MaxPolinom = Polinom1;
	else
		MaxPolinom = Polinom2;

	Array* Polinom = malloc(sizeof(Array));
	Polinom->buffer = malloc(Polinom1->el_size * max_count);
	Polinom->el_size = Polinom1->el_size;
	Polinom->degree = max_count - 1;
	Polinom->count_element = max_count;

	switch (Polinom1->el_size)
	{
		case sizeof(int) :
		{
			for (i = 0; i < min_count; i++)
				*((int*)Polinom->buffer + i) = *((int*)Polinom1->buffer + i) + *((int*)Polinom2->buffer + i);
			for (; i < max_count; i++)
				*((int*)Polinom->buffer + i) = *((int*)MaxPolinom->buffer + i);
			break;
		}
		case sizeof(double) :
		{
			for (i = 0; i < min_count; i++)
				*((double*)Polinom->buffer + i) = *((double*)Polinom1->buffer + i) + *((double*)Polinom2->buffer + i);
			for (; i < max_count; i++)
				*((double*)Polinom->buffer + i) = *((double*)MaxPolinom->buffer + i);
			break;
		}
	}
	ZeroCoefficients(Polinom);
	OutputPolinom(Polinom);
	free(Polinom1);
	free(Polinom2);
	return Polinom;
}

// перемножает два введенных полинома
Array* Multiplication(Array* Polinom1, Array* Polinom2)
{
	int degree = Polinom1->degree + Polinom2->degree;
	Array* Polinom = malloc(sizeof(Array));

	Polinom->buffer = malloc(Polinom1->el_size * degree);
	Polinom->el_size = Polinom1->el_size;
	Polinom->degree = degree;
	Polinom->count_element = degree + 1;

	switch (Polinom->el_size)
	{
		case sizeof(int):
		{
			int a;

			for (int i = 0; i <= Polinom->degree; i++)
				*((int*)Polinom->buffer + i) = 0;
			
			for(int i = 0; i <= Polinom2->degree; i++)
				for (int j = 0; j <= Polinom1->degree; j++)
				{
					a = *((int*)Polinom1->buffer + j) * *((int*)Polinom2->buffer + i);
					degree = j + i;
					*((int*)Polinom->buffer + degree) += a;
				}
			break;
		}
		case sizeof(double):
		{
			double a;

			for (int i = 0; i <= Polinom->degree; i++)
				*((double*)Polinom->buffer + i) = 0;

			for (int i = 0; i <= Polinom2->degree; i++)
				for (int j = 0; j <= Polinom1->degree; j++)
				{
					a = *((double*)Polinom1->buffer + j) * *((double*)Polinom2->buffer + i);
					degree = j + i;
					*((double*)Polinom->buffer + degree) += a;
				}
			break;
		}
	}
	ZeroCoefficients(Polinom);
	OutputPolinom(Polinom);
	free(Polinom1);
	free(Polinom2);
	return Polinom;
}

// умножает полином на число
void MultiplicationbyConstant(Array* Polinom)
{
	switch (Polinom->el_size)
	{
		case sizeof(int) :
		{
			int alpha;
			int error_code;
			do
			{	
				error_code = 1;
				printf("Input constant: ");
				error_code = scanf("%d", &alpha);
				CleanCh();
				if (!error_code)
				{
					printf("InputError: expected integer argument. Please, try again.\n\n");
					continue;
				}
				printf("Your input: %d\n\n", alpha);
				for (int i = 0; i < Polinom->count_element; i++)
					*((int*)Polinom->buffer + i) *= alpha;
			} while (!error_code);
			break;
		}
		case sizeof(double) :
		{
			double alpha;
			int error_code;
			do
			{
				error_code = 1;
				printf("Input constant: ");
				error_code = scanf("%lf", &alpha);
				CleanCh();
				if (!error_code)
				{
					printf("InputError: expected double argument. Please, try again\n\n");
					continue;
				}
				printf("Your input: %lf\n\n", alpha);
				for (int i = 0; i < Polinom->count_element; i++)
					*((double*)Polinom->buffer + i) *= alpha;
			} while (!error_code);
			break;
		}
	}
	ZeroCoefficients(Polinom);
	printf("Result of polinomial multiplication by constant:\n");
	OutputPolinom(Polinom);
}

//Композиция
void Composition()
{

}


// считает значение полинома при заданом аргументе
void Calculate(Array* Polinom)
{
	int i;
	switch (Polinom->el_size)
	{
		case sizeof(int) :
		{
			int x;
			int xh;
			int result = 0;
			int error_code;
			do
			{
				error_code = 1;
				printf("Input argument: ");
				error_code = scanf("%d", &x);
				CleanCh();
				if (!error_code)
				{
					printf("InputError: expected integer argument. Please, try again\n\n");
					continue;
				}
				printf("Your input: %d\n\n", x);
				for (i = Polinom->count_element - 1; i >= 0; i--)
				{
					xh = (int)pow(x, i);
					result += *((int*)Polinom->buffer + i) * xh;
				}
			} while (!error_code);
			printf("Result: P(%d)(%d) = %d\n\n", Polinom->degree, x, result);
			break;
		}
		case sizeof(double) :
		{
			double x;
			double xh;
			double result = 0;
			int error_code;
			do
			{
				error_code = 1;
				printf("Input argument: ");
				error_code = scanf("%lf", &x);
				CleanCh();
				if (!error_code)
				{
					printf("InputError: expected double argument. Please, try again\n\n");
					continue;
				}
				printf("Your input: %lf\n\n", x);
				for (i = Polinom->count_element - 1; i >= 0; i--)
				{
					xh = pow(x, i);
					result += *((double*)Polinom->buffer + i) * xh;
				}
			} while (!error_code);
			printf("Result: P(%d)(%lf) = %lf\n\n", Polinom->degree,  x, result);
			break;
		}
	}
}