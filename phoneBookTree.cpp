#include <stdio.h>
#include <stdlib.h>

char* copystring(char* src);
int strcompare(char* a, char* b);

struct searchTree //Дерево с двоичным поиском
{
    int value;
    char* tag;

    searchTree* greater;
    searchTree* less;
    int get(char* Tag) //Поиск по значению строки: Переход к одной из двух вершин в зависимости от "алфавитного" порядка
    {                            //Возвращает -1, если нет записи с такой меткой.
        searchTree* tree = this;
        int res = -1;

        int delta;
        while (tree && (delta = strcompare(Tag, tree->tag)))
        {
            if (delta > 0)
                tree = tree->greater;
            else
                tree = tree->less;
        }
        if (tree)
            res = tree->value;
        return res;
    }
    int add(int Value, char* Tag) //добавление или обновление. Возвращает старое значение или -1 
    {
        searchTree* This = this;
        searchTree** tree = &This;

        int delta;
        while (*tree && (delta = strcompare(Tag, (*tree)->tag)))
        {
            if (delta > 0)
                tree = &((*tree)->greater);
            else
                tree = &((*tree)->less);
        }
        if (*tree)
        {
            int old = (*tree)->value;
            (*tree)->value = Value;
            return old;
        }
        searchTree* newTree = (searchTree*)calloc(1, sizeof(searchTree));

        newTree->value = Value;
        newTree->tag = copystring(Tag);

        *tree = newTree;
        return -1;
    }
};

int main()
{
    char const_empty[] = "\0";
    char const_insert[] = "INSERT";
    char const_find[] = "FIND";

    searchTree* root = (searchTree*)calloc(1, sizeof(searchTree));
    root->tag = copystring(const_empty);

    while (1)
    {
        char input[32] = {};
        int number;
        scanf_s("%s", input, 31);

        if (!strcompare(input, const_insert))
        {
            if (scanf_s("%s %d", input, 31, &number))
            {
                int old = root->add(number, input);
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
                int result = root->get(input);
                if (result > -1)
                    printf("%d\n", result);
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
    for(int i = 0; 1; i++)
    {
        if (a[i] != b[i])
            return a[i] - b[i];
        if (!a[i])
            return 0;
    }
}