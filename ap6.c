#include <stdio.h>
#include <stdlib.h>

#define WORDSIZE 20
#define LEXSIZE 26

/*
print_arr(char **arr, int len)
parameters:
- arr: string array to be printed (char**)
- len: size of arr (int)

returns:
none
*/
void print_arr(char **arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%s ", arr[i]);
    }
    printf("\n");

    return;
}

/*
get_char_ranking(char character, char *key, int key_len)
parameters:
- character: character whose ranking is desired to know (char)
- key: array of characters in the desired lexicographic order (char*)
- key_len: lenght of "key" array

returns:
* character ranking
*/
int get_char_ranking(char character, char *key, int key_len)
{
    int i = 0;
    while (i < key_len)
    {
        if (character == key[i])
            return i;
        i++;
    }

    return -1;
}

/*
greater_than(char *a, char *b, char *key, int key_len)
parameters:
- a, b: strings to be compared(char*)
- key: array of characters in the desired lexicographic order (char*)
- key_len: length of "key" array

returns:
* 1 if a is considered greater than b according to the supplied lexicographic order or a equals b
* 0 otherwise
*/
int greater_than(char *a, char *b, char *key, int key_len)
{
    int len_a = strlen(a);
    int len_b = strlen(b);
    int i = 0;

    while (i < len_a && i < len_b)
    {
        int rank_a = get_char_ranking(a[i], key, key_len);
        int rank_b = get_char_ranking(b[i], key, key_len);

        if (rank_a > rank_b)
            return 1;
        else if (rank_a < rank_b)
            return 0;
        // if rank_a == rank_b, loop keeps going
        i++;
    }

    if (len_a < len_b)
        return 0;

    return 1;
}

/*
swap(char **arr, int pos_a, int pos_b)
parameters:
- arr: array of strings in which the swap will occur (char**)
- pos_a: index of first element (int)
- pos_b: index of second element (int)

returns:
none
*/
void swap(char **arr, int pos_a, int pos_b)
{
    char *aux = arr[pos_a];
    arr[pos_a] = arr[pos_b];
    arr[pos_b] = aux;

    return;
}

int main()
{

    return 0;
}