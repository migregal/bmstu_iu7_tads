#include "../inc/io.h"

void welcome()
{
    printf("%s",
           ANSI_MAGENTA
           "Данная программа позволяет построить ДДП, сбалансированное двоичное дерево \n"
           "и хеш-таблицу по указанным данным, вывести на экран дерево в виде дерева, \n"
           "провести реструктуризацию хеш-таблицы, если среднее количество сравнений \n"
           "больше указанного, вывести количественную характеристику моделирования. \n\n" ANSI_RESET);
}
