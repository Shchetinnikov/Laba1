#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "Header.h"
#include <ctype.h>

void main() {
	int item;
	int el_size;
	
	printf("**Starting running the programme**\n\n");

	while (1){
		el_size = ChooseType();
		item = ShowMenu();

		switch (item) {
			case '1': {
				struct Array* Polinom1 = Create(el_size);
				struct Array* Polinom2 = Create(el_size);
					//Addition(Polinom1, Polinom2);
					//printf('форма');
					break;
			}
			case '2': {
				//Polinom = Create();
				//Polinom2 = Create();
				//Multiplication(Polinom1, Polinom2);
				break; 
			}
			case '3': {
				//Polinom = Create();
				//scanf(alpha);
				// MultiplicationbyNumber(Polinom, alpha);
				break; 
			}
			case '4': {
				//Polinom = Create();
				// scanf(x);
				//Calculate(Polinom, x);
				//printf(result);
				break;
			}
			case '5': {
				printf("End of running the programme\n");
				exit(0); 
			}
			default:{
				printf("InputError: number of item doesn't exist. Please, repeat action\n\n");
				break; 
			}
		}
	}
}

