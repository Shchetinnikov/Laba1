#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include "action.h"

int CountPolinom()
{
	int n;
	int error_code;
	do {
		printf("Input count of polinomials: ");
		error_code = scanf("%d", &n);
		CleanCh();
		if (!error_code)
		{
			printf("InputError: expected integer argument. Please, try again.\n\n");
			continue;
		}
		printf("Your input : %d\n\n", n);
	} while (!error_code);
	
	return n;
}

void main() 
{
	int n;
	int item;
	int el_size;

	printf("**Starting running the programme**\n\n");
	Instroduce();

	while (1)
	{
		do
		{  // выбор типа данных и пункта меню
			el_size = ElementType();
			item = Menu();
		} while (item == '6');
		
		switch (item)
		{
			case '1': // Сложение многочленов
			{
				n = CountPolinom();

				Array* Polinom = Create(el_size, 1);
				for (int i = 2; i <= n; i++) 
				{
					Array* PolinomI = Create(el_size, i);
					if (i == n)
						printf("Result of polinomial addition:\n");
					Polinom = Addition(Polinom, PolinomI);
				}
				break;
			}
			case '2':
			{
				n = CountPolinom();

				Array* Polinom = Create(el_size, 1);
				for (int i = 2; i <= n; i++) 
				{
					Array* PolinomI = Create(el_size, i);		
					if (i == n)
						printf("Result of polinomial multiplication:\n");
					Polinom = Multiplication(Polinom, PolinomI);
				}
				break;
			}
			case '3':
			{
				Array* Polinom = Create(el_size, 0);
				MultiplicationbyConstant(Polinom);
				break;
			}
			case '4':
			{
				Array* Polinom = Create(el_size, 0);
				Calculate(Polinom);	
				break;
			}
			case '5':
			{
				//Композиция
				break;
			}
			case '7':
			{
				printf("End of running the programme...\n\n");
				exit(0);
			}
			default:
			{
				printf("InputError: item doesn't exist. Please, try again.\n\n");
				break;
			}
		}
	}
}

