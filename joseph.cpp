#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct list //список c целыми числами
{

	int value = 0.0; //в этом поле можно хранить указатель, чтобы хранить какие угодно элементы
	list* next = 0;

	int* get(int i) //получение значения элемента по индексу для чтения или изменения;
	{
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
};

int main()
{
	int units, delta;
	int pointer = 0;

	scanf_s("%d %d", &units, &delta);

	list roster = { 0, 0 };
	for (int i = 1; i <= units; i++)
		roster.add(i);

	while (units > 1)
	{
		pointer = (pointer + delta) % units;
		roster.pop(pointer);
		units--;
	}
	printf_s("%d",  * roster.get(0));
}

