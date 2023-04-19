#include <stdio.h>
#include <stdlib.h>

char check_str(char **s);

char check(char **s)
{
        char wait_for;
        char c = *(*s)++;
        switch (c)
        {
                case '{': wait_for = '}'; break;
                case '[': wait_for = ']'; break;
                case '(': wait_for = ')'; break;
                case '<': wait_for = '>'; break;
                case '"': return check_str(s);
                case '}': case ']': case ')': case '>': case '\0': return c;
                default:
                    return check(s);
        }

        return check(s) != wait_for ? -1 : check(s);
}

char check_str(char **s)
{
        char c = *(*s)++;
        switch (c)
        {
                case '"': return check(s);
                case '\0': return -1;
                default:
                    return check_str(s);
        }
}


int main()
{
		printf("Введите скобочное выражение: ");

        char buf[8190];
        char *s = fgets(buf, sizeof(buf), stdin);
        if (!check(&s))
                printf("Верное скобочное выражение\n");
        else
                printf("Неверное скобочное выражение\n");

        return 0;
}