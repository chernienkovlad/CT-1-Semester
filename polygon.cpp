#include<stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define PI 3.14159265358979323846

//ОПИСАНИЕ АЛГОРИТМА

//Вершины сортируются, чтобы они шли в порядке против часовой стрелки относительно центра фигуры, который
//вседствие выпуклости всегда находится внутри неё. Первая вершина считается "опорной", пары остальных стоящих рядом формируют
//с ней непересекающиеся треугольники, площади которых считаются и суммируются.

struct list //список c действительными числами
{

	double value = 0.0; //в этом поле можно хранить указатель, чтобы хранить какие угодно элементы
	list* next = 0;

	double* get(int i) //получение значения элемента по индексу для чтения или изменения;
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
	int add(double i) //добавление элемента в конец списка. возвращает полученную длину.
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
	int checkfor(double v) //проверка на наличие элемента
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
	int destroy(double v) //убрать элемент; возвращает 1, если такой элемент был и убрать удалось, 0, если не был найден
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
				return 1;
			}
		}
		return 0;
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
		double *A,*B;

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
int readConsoleFile(FILE** file);

double triangleArea(double x1, double y1, double x2, double y2, double x3, double y3);
double getAngle(double x, double y);
double magnitude(double x, double y);
double scalProduct(double x1, double y1, double x2, double y2);
double abs(double i);

int* getIdenticPermutation(int size);
int applyPermutation(list* List, int* permutation);
int swap(int* a, int* b);

int main()
{
    FILE* file;
    readConsoleFile(&file);

	list X = { 0.0, 0 }, Y = { 0.0, 0 };
	int x, y;
	int points = 0;

	int stop = 0;
	while (fscanf_s(file, "%d %d", &x, &y))
	{
		for (int k = 0; k < points; k++)
			if (*X.get(k) == x && *Y.get(k) == y)
			{
				stop = 1;
				break;
			}
		if (stop)
			break;
		X.add((double)x), Y.add((double)y), points++;
	}

	if (points < 3)
	{
		printf_s("Total area: 0");
		fclose(file);
		return 0;
	}
	double centerX = X.mean(), centerY = Y.mean();

	list angles = { 0.0, 0 };
	for (int i = 0; i < points; i++)
		angles.add(getAngle(*X.get(i) - centerX, *Y.get(i) - centerY));

	int* permutation = synchroSort(&angles); //переставляем вершины, чтобы они шли против часовой стрелки

	applyPermutation(&X, permutation);
	applyPermutation(&Y, permutation);

	double area = 0; //делим фигуру на треугольники и суммируем их площади
	double vertexX = *X.get(0);
	double vertexY = *Y.get(0);

	for (int i = 1; i < points - 1; i++)
		area += triangleArea(vertexX, vertexY, *X.get(i), *Y.get(i), *X.get(i + 1), *Y.get(i + 1));

	printf_s("Total area: %.3lf", area);
	fclose(file);
}
int readConsoleFile(FILE** file)
{
	if (!file)
		return 0;
    char path[256] = {};
    scanf_s("%s", path, 256);
    fopen_s(file, path, "r");
    if (!*file)
        return 0;
    return 1;
}
int* synchroSort(list *List) //Сортировка. Возвращает массив-перестановку
{
	int* permutation = getIdenticPermutation((int)List->value);

	for (int a = 0; a < (int)List->value - 1; a++)
	{
		int minIndex = a;
		double minimum = *List->get(a);
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

double triangleArea(double x1, double y1, double x2, double y2, double x3, double y3) //площадь треугольника
{
	double side1 = magnitude(x2 - x1, y2 - y1);
	double side2 = magnitude(x3 - x1, y3 - y1);

	double angle = getAngle(x2 - x1, y2 - y1) - getAngle(x3 - x1, y3 - y1);

	double area = abs(side1 * side2 * sin(angle) / 2);
	return area;
}
double getAngle(double x, double y) //угол против часовой стрелки от вектора (1, 0)
{
	double mag = magnitude(x, y);
	double sin = y / mag, cos = x / mag;

	if (sin < 0)
		return 2 * PI - acos(cos);
	else
		return acos(cos);
}
double magnitude(double x, double y) //модуль
{
	return sqrt(pow(x, 2) + pow(y, 2));
}
double scalProduct(double x1, double y1, double x2, double y2) //скалярное произведение
{
	return x1 * x2 + y1 * y2;
}
double abs(double i)
{
	if (i < 0.0)
		return -i;
	return i;
}

int* getIdenticPermutation(int size) //тождественная перестановка
{
	int* permutation = (int*)calloc(size, sizeof(int));
		for(int i = 0; i < size; i++)
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