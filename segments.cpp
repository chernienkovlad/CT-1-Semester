#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//Функции взяты из решения задачи №1

struct list //список c действительными числами
{

	int value = 0; //в этом поле можно хранить указатель, чтобы хранить какие угодно элементы
	list* next = 0;

	int* get(int i) //получение значения элемента по индексу для чтения или изменения;
	{
		assert(i >= 0);
		list* element = this;
		for (int index = 0; index <= i; index++) //перемещаемся на i элементов цепи и получаем значение
		{
			assert(element->next); //убеждаемся в наличии следующего элемента
			element = element->next;
		}
		return &element->value;
	}
	list* getElement(int i) //получение указателя на следующий за данным элемент
	{
		assert(i >= 0);
		list* element = this;
		for (int index = 0; index <= i; index++) //перемещаемся на i элементов цепи и получаем значение
		{
			assert(element->next); //убеждаемся в наличии следующего элемента
			element = element->next;
		}
		return element;
	}
	int add(int i) //добавление элемента в конец списка. возвращает полученную длину.
	{
		list* element = this;
		while (element->next)
		{
			element = element->next;
		}
		element->next = (list*)malloc(sizeof(list));
		element->next->value = i;
		element->next->next = 0;

		value++;
		return value;
	}
	int checkfor(int v) //проверка на наличие элемента
	{
		list* element = this;
		while (element->next)
		{
			element = element->next;
			if (element->value == v)
				return 1;
		}
		return 0;
	}
	int destroy(int v) //убрать элемент; возвращает 1, если такой элемент был и убрать удалось, 0, если не был найден
	{
		list* element = this;
		list* previous;
		while (element->next)
		{
			previous = element;
			element = element->next;
			if (element->value == v)
			{
				list* next = element->next;
				free(element);
				previous->next = next;
				value--;
				return 1;
			}
		}
		return 0;
	}
	int pop(int i) //удаление элемента под индексом
	{
		assert(i >= 0);
		list* element = this;
		list* previous = 0;
		for (int index = 0; index <= i; index++) //перемещаемся на i элементов цепи и получаем значение
		{
			assert(element->next); //убеждаемся в наличии следующего элемента
			previous = element;
			element = element->next;
		}
		list* next = element->next;
		free(element);
		previous->next = next;
		value--;
		return 1;
	}
	int checkForDefects() //уточняет длину списка. Возвращает 1, если всё было правильно
	{
		int trueLength = 0;
		list* element = this;
		while (element->next)
		{
			trueLength++;
			element = element->next;
		}
		if (trueLength == value)
			return 1;
		value = trueLength;
		return 0;
	}
	int swap(int a, int b)
	{
		int* A, * B;

		A = get(a);
		B = get(b);

		if (*A == *B)
			return 0;

		double value = *A;
		*A = *B;
		*B = value;

		return 1;
	}
	double mean() //среднее арифметическое
	{
		double elements = 0.0;
		double sum = 0.0;

		list* element = this;
		while (element->next)
		{
			element = element->next;
			sum += element->value;
			elements++;
		}
		if (elements)
			return sum / elements;
		return 0.0;
	}
};

int* synchroSort(list* List);
int* getIdenticPermutation(int size);
int applyPermutation(list* List, int* permutation);
int swap(int* a, int* b);

int main()
{
	int quantity;
	scanf_s("%d", &quantity);
	assert(quantity > 0);

	list start = { 0, 0 }, end = { 0, 0 };
	int readStart, readEnd;

	for(int i = 0; i < quantity; i++)
	{ 
		assert(scanf_s("%d %d", &readStart, &readEnd));
		start.add(readStart), end.add(readEnd);
	}
	int* permutation = synchroSort(&start);
																		//сортировка отрезков по координате начала
	applyPermutation(&end, permutation); 

	int border = 0;
	int possible = 1;
	int count = 0;
	list startRes = { 0, 0 }, endRes = { 0, 0 };

	while (border < 10000)
	{
		int bestIndex = -1;
		int bestLength = -1;

		for (int i = 0; i < start.value; i++)
		{
			if (*start.get(i) > border)
				break;
			if (*end.get(i) > bestLength)
				bestLength = *end.get(i), bestIndex = i;
		}
		if (bestIndex < 0)
			{
			possible = 0;
			break;
			}
		count++;
		int newBorder = *end.get(bestIndex);

		startRes.add(*start.get(bestIndex)), endRes.add(*end.get(bestIndex));
		while(start.value > 0 &&*start.get(0) <= border)
		{
			start.pop(0), end.pop(0);
		}
		border = newBorder;
	}
	if (possible)
	{
		printf_s("%d segments:\n", count);
		for (int i = 0; i < startRes.value; i++)
			printf_s("[%d %d]\n", *startRes.get(i), *endRes.get(i));
	}
	else
		printf_s("No solution exists");
}

int* synchroSort(list* List) //Сортировка. Возвращает массив-перестановку
{
	int* permutation = getIdenticPermutation((int)List->value);

	for (int a = 0; a < (int)List->value - 1; a++)
	{
		int minIndex = a;
		int minimum = *List->get(a);
		for (int b = a + 1; b < (int)List->value; b++)
			if (*List->get(b) < minimum)
			{
				minIndex = b;
				minimum = *List->get(b);
			}
		List->swap(a, minIndex);
		swap(&permutation[a], &permutation[minIndex]);
	}
	return permutation;
}
int* getIdenticPermutation(int size) //тождественная перестановка
{
	int* permutation = (int*)calloc(size, sizeof(int));
	for (int i = 0; i < size; i++)
		permutation[i] = i;
	return permutation;
}
int applyPermutation(list* List, int* permutation) //переставить элементы в указанном порядке
{
	int* status = getIdenticPermutation((int)List->value);

	for (int i = 0; i < (int)List->value; i++)
	{
		if (status[i] != permutation[i])
		{
			int index = i + 1;
			int success = 0;
			for (; index < (int)List->value; index++)
				if (status[index] == permutation[i])
				{
					success = 1;
					break;
				}
			assert(success);

			List->swap(i, index);

			swap(&status[i], &status[index]);
		}
	}
	return 1;
}
int swap(int* a, int* b)
{
	assert(a);
	assert(b);

	int value = *a;
	*a = *b;
	*b = value;
	return 1;
}