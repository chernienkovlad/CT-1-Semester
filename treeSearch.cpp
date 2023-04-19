#include <stdio.h>
#include <stdlib.h>

struct searchTree //Дерево с двоичным поиском
{
    int value;

    searchTree* greater;
    searchTree* less;
    int get(int Val) //Поиск по дереву с выводом пути. Добавляет вершину на нужное место, если она не найдена.
    {      
        searchTree* This = this;
        searchTree** tree = &This;

        int depth = 0;

        while (*tree && Val != (*tree)->value)
        {
            if (Val > (*tree)->value)
            {
                printf_s("Layer %d: (%d > %d): Go right\n", depth, Val, (*tree)->value);
                tree = &((*tree)->greater);
            }
            else
            {
                printf_s("Layer %d: (%d < %d): Go left\n", depth, Val, (*tree)->value);
                tree = &((*tree)->less);
            }
            depth++;
        }
        if (*tree)
        {
            printf_s("Layer %d: (%d = %d): Stop\n", depth, Val, (*tree)->value);
            return 1;
        }
        printf_s("Layer %d: Not found: Stop\n", depth);
        *tree = (searchTree*)calloc(1, sizeof(searchTree));
        (*tree)->value = Val;
        printf_s("%d added to tree.\n", Val);
        return 0;
    }
};

int main()
{
    searchTree* root = (searchTree*)calloc(1, sizeof(searchTree));
    root->value = 0;

    int input;
    while (1) //Ввод вершин и построение пути до их расположения
        if (scanf_s("%d", &input))
            root->get(input);

}