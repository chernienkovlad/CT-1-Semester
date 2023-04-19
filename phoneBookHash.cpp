#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char* copystring(char* src);
int strcompare(char* a, char* b);

struct hashTable //хэш-таблица. по сути, два массива, расположенных в соответствующем порядке.
{
    int size;
    int capacity;
    char** tags;
    int* values;
    int* get(char* Tag)
    {
        int index = -1;
        for (int i = 0; i < size; i++)
            if (!strcompare(tags[i], Tag))
            {
                index = i;
                break;
            }
        if (index == -1)
            return 0;
        return &(values[index]);
    }
    int add(int Value, char* Tag)
    {
        int* old;
        if (old = get(Tag))
        {
            int oldValue = *old;
            *old = Value;
            return oldValue;
        }

        if (size >= capacity)
            getMemory();

        tags[size] = copystring(Tag);
        values[size] = Value;

        size++;
        return -1;
    }
    int getMemory() //Выделяет больше памяти
    {
        char** newTags = (char**)realloc(tags, sizeof(char*) * (capacity + 10));
        int* newValues = (int*)realloc(values, sizeof(int) * (capacity + 10));

        //free(tags);  вызывает ошибки. realloc уже освобождает старую память?
       // free(values);

        tags = newTags;
        values = newValues;

        return capacity += 10;
    }
};

int main()
{
    char const_insert[] = "INSERT";
    char const_find[] = "FIND";

    hashTable* table = (hashTable*)calloc(1, sizeof(hashTable));
    table->size = 0;
    table->capacity = 0;

    while (1)
    {
        char input[32] = {};
        int number;
        scanf_s("%s", input, 31);

        if (!strcompare(input, const_insert))
        {
            if (scanf_s("%s %d", input, 31, &number))
            {
                int old = table->add(number, input);
                if (old > -1)
                    printf("Changed. Old value = %d\n", old);
                else
                    printf("OK\n");
                continue;
            }
            else
            {
                printf_s("Invalid input\n");
                continue;
            }
        }
        if (!strcompare(input, const_find))
        {
            if (scanf_s("%s", &input, 31))
            {
                int* result = table->get(input);
                if (result)
                    printf("%d\n", *result);
                else
                    printf("NO\n");
                continue;
            }
            else
            {
                printf_s("Invalid input\n");
                continue;
            }
        }
        printf("Invalid command\n");
    }
}
char* copystring(char* src) //создание копии строки
{
    int length;
    for (length = 0; src[length]; length++);

    char* res = (char*)calloc(length + 1, sizeof(char));
    for (int i = 0; src[i]; i++)
        res[i] = src[i];
    res[length] = 0;
    return res;
}
int strcompare(char* a, char* b) //сравнение строк в алфавитном порядке (разница двух первых с начала различающихся символов)
{
    for (int i = 0; 1; i++)
    {
        if (a[i] != b[i])
            return a[i] - b[i];
        if (!a[i])
            return 0;
    }
}