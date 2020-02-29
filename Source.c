#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "Header.h"
#include <ctype.h>

void main() 
{
	int item;
	int el_size;

	printf("**Starting running the programme**\n\n");

	while (1)
	{
		el_size = ChooseType();
		item = ShowMenu();
		
		switch (item) 
		{
			case '1': 
			{
				Array* Polinom1 = Create(el_size, 1);
				Array* Polinom2 = Create(el_size, 2);
				Array* Polinom = Addition(Polinom1, Polinom2, el_size);
				break;
			}
			case '2': 
			{
				Array* Polinom1 = Create(el_size, 1);
				Array* Polinom2 = Create(el_size, 2);
				//Multiplication(Polinom1, Polinom2);
				break; 
			}
			case '3': 
			{
				Array* Polinom1 = Create(el_size, 1);
				//scanf(alpha);
				// MultiplicationbyNumber(Polinom, alpha);
				break; 
			}
			case '4': 
			{
				Array* Polinom1 = Create(el_size, 1);
				// scanf(x);
				//Calculate(Polinom, x);
				//printf(result);
				break;
			}
			case '5': 
			{
				//Композиция
			}
			case '6': 
			{
				printf("End of running the programme\n");
				exit(0); 
			}
			default:
			{
				printf("InputError: number of item doesn't exist. Please, repeat action\n\n");
				break; 
			}
		}
	}
}

