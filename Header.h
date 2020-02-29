#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Array {
	void* buffer;  // коэффициенты
	int degree;  // степень
	int count_element;
	int el_size;
} Array;

void CleanCh() {
	while (getchar() != '\n')
		;
}

void ReadString(Array* Polinom) { //считывает коэффициенты полинома
	int code_error;
	void* index;
	Polinom->buffer = malloc(Polinom->el_size * (Polinom->count_element));
	if (Polinom->el_size == sizeof(int))
		do {
			printf("Please, input polynomial coefficients (a(n), a(n-1) ... a(0)) by Space : ");
			index = Polinom->buffer;
			code_error = 1;
			for (int i = 0; i < Polinom->count_element; i++) {
				code_error = scanf("%d", ((int*)index)++);
				if (!code_error)
					break;
			}
			if (!code_error) {
				CleanCh();
				printf("InputError: integer polynomial coefficients expected. Please, start from the beginning\n\n");
			}
			else {
				CleanCh();
				printf("Successfully inputed\n");
			}
		} while (code_error == 0);
	else {	
		do {
			printf("Please, input polynomial coefficients (a(n), a(n-1) ... a(0)) by Space : ");
			index = Polinom->buffer;
			code_error = 1;
			for (int i = 0; i < Polinom->count_element; i++) {
				code_error = scanf("%lf", ++(double*)index);
				if (!code_error)
					break;
			}
			if (!code_error) {
				CleanCh();
				printf("InputError: double polynomial coefficients expected. Please, start from the beginning\n\n");
			}
			else {
				CleanCh();
				printf("Successfully inputed\n\n");
			}

		}while(code_error == 0);
	}
}

int ShowMenu() {
	int i;
	
	printf("Menu:\n"
		"\t1. Addition\n"
		"\t2. Multiplication\n"
		"\t3. Multiplication by number\n"
		"\t4. Calculate function value by argument\n"
		"\t5. Exit\n\n");
	
	printf("Input your number of item : ");
	i = getchar();
	CleanCh();
	printf("Your item: %c\n\n", i);
	return i;
}

int ChooseType() { // Запрашивает тип, возвращает размер типа
	int data_type;
	while (1) {
		printf("Types of data:\n"
			   "\t 1. Integer\n"
			   "\t 2. Double\n\n");
		
		printf("Input number of type of data: ");
		data_type = getchar();
		CleanCh();
		printf("Your input : %c\n\n", data_type);
		
		if (data_type != '1' && data_type != '2') {
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

void OutputPolinom(int* p){
	for (int i = 0; i < 2; i++) {
		printf("%d\n", p[i]);
	}
}

Array* Create(int el_size) { // создает и возвращает структуру "полином"
	int degree;
	int code_error;
	Array* Polinom = (Array*)malloc(sizeof(Array));
	
	Polinom->el_size = el_size;

	do { // запрашивает степень полинома
		printf("Please, input polinomail degree n: ");
		code_error = scanf("%d", &degree);
		CleanCh();	
		if (code_error == 0)
			printf("\nInputError: expected integer argument. Please, repeat action\n\n");
	} while (code_error == 0);
	
	Polinom->degree = degree;
	Polinom->count_element = degree + 1;
	printf("Your input : %d\n\n", degree);

	ReadString(Polinom);
	OutputPolinom((int*)Polinom->buffer);
	return Polinom;
}