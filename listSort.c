#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _Node
{
	int value;
	struct _Node *next, *prev;
} Node;

typedef struct _DbLinkedList
{
	size_t size;
	Node *head, *tail;
} DbLinkedList;


////////// Прототипы функций //////////
DbLinkedList* createDbLinkedList();
void deleteDbLinkedList(DbLinkedList**);
void pushFront(DbLinkedList*, int);
int popFront(DbLinkedList*);
void pushBack(DbLinkedList*, int);
int popBack(DbLinkedList*);
void insertBeforeElement(DbLinkedList*, Node*, int);
void insertionSort(DbLinkedList**);
void printDbLinkedList(DbLinkedList*);


int main()
{
	srand(time(0));


	DbLinkedList *list = createDbLinkedList();
	for (int i = 0; i < 50; i++)
		pushBack(list, rand()%101);
	
	printDbLinkedList(list);
	insertionSort(&list);
	printDbLinkedList(list);


	deleteDbLinkedList(&list);
	return 0;
}


/////////////////////////////////////////////////////////////////////////


////////// Создаём список //////////
DbLinkedList* createDbLinkedList()
{
	DbLinkedList *tmp = (DbLinkedList*)malloc(sizeof(DbLinkedList));
	if (tmp == NULL)
	{
		printf("Allocation failure.\nCannot create a List.");
		exit(1);
	}
	tmp->size = 0;
	tmp->head = tmp->tail = NULL;

	return tmp;
}

////////// Удаляем список //////////
void deleteDbLinkedList(DbLinkedList **list)
{
	Node *tmp = (*list)->head;
	Node *next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*list);
	(*list) = NULL;
}

////////// Вставка в список спереди //////////
void pushFront(DbLinkedList *list, int data)
{
	Node *tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL)
	{
		printf("Allocation failure.\nCannot create a Node.");
		exit(2);
	}
	tmp->value = data;
	tmp->prev = NULL;
	tmp->next = list->head;
	if (list->head)
		list->head->prev = tmp;
	list->head = tmp;

	if (list->tail == NULL)
		list->tail = tmp;
	list->size++;
}

////////// Удаление элемента из списка спереди //////////
int popFront(DbLinkedList *list)
{
	Node *prev;
	int tmp;
	if (list->head == NULL)
	{
		printf("Cannot pop.\nZero size of the list.");
		exit(3);
	}

	prev = list->head;
	list->head = list->head->next;
	if (list->head)
		list->head->prev = NULL;
	if (prev == list->tail)
		list->tail = NULL;
	tmp = prev->value;
	free(prev);
	list->size--;

	return tmp;
}

////////// Вставка в список сзади //////////
void pushBack(DbLinkedList *list, int data)
{
	Node *tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL)
	{
		printf("Allocation failure.\nCannot create a Node.");
		exit(2);
	}
	tmp->value = data;
	tmp->prev = list->tail;
	tmp->next = NULL;
	if (list->tail)
		list->tail->next = tmp;
	list->tail = tmp;

	if (list->head == NULL)
		list->head = tmp;
	list->size++;
}

////////// Удаление элемента из списка сзади //////////
int popBack(DbLinkedList *list)
{
	Node *next;
	int tmp;
	if (list->tail == NULL)
	{
		printf("Cannot pop.\nZero size of the list.");
		exit(3);
	}
	next = list->tail;
	list->tail = list->tail->prev;
	if (list->tail)
		list->tail->next = NULL;
	if (next == list->head)
		list->head = NULL;
	tmp = next->value;
	free(next);

	list->size--;
	return tmp;
}

////////// Вставка элемента перед другим элементом списка //////////
void insertBeforeElement(DbLinkedList *list, Node *elm, int data)
{
	Node *ins = NULL;
	if (elm == NULL)
	{
		printf("Cannot insert an empty element.");
		exit(4);
	}

	if (!elm->prev)
	{
		pushFront(list, data);
		return;
	}
	ins = (Node*)malloc(sizeof(Node));
	ins->value = data;
	ins->prev = elm->prev;
	elm->prev->next = ins;
	ins->next = elm;
	elm->prev = ins;

	list->size++;
}

////////// Сортировка вставками //////////
void insertionSort(DbLinkedList **list)
{
	DbLinkedList *out = createDbLinkedList();
	Node *sorted = NULL;
	Node *unsorted = NULL;

	pushFront(out, popFront(*list));

	unsorted = (*list)->head;
	while (unsorted)
	{
		sorted = out->head;
		while (sorted && !(unsorted->value < sorted->value))
			sorted = sorted->next;
		if (sorted)
			insertBeforeElement(out, sorted, unsorted->value);
		else
			pushBack(out, unsorted->value);
		unsorted = unsorted->next;
	}

	free(*list);
	*list = out;
}

////////// Печать списка //////////
void printDbLinkedList(DbLinkedList *list)
{
	Node *tmp = list->head;
	while (tmp)
	{
		printf("%d\n", tmp->value);
		tmp = tmp->next;
	}
	printf("\nSize: %zu\n–––––––––––\n\n", list->size);
}