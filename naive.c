#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORDSIZE 20
#define LEXSIZE 27

/*
print_arr(char **arr, int len)
parameters:
- arr: string array to be printed (char**)
- len: size of arr (int)
- single_line: boolean to determine if each element is
separated with a space or a newline

returns:
none
*/
void print_arr(char **arr, int len, int single_line)
{
    if (single_line)
    {
        for (int i = 0; i < len; i++)
        {
            printf("%s ", arr[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < len; i++)
        printf("%s\n", arr[i]);
    return;
}

void copy_arr(char **src, char **dst, int size)
{
    for (int i = 0; i < size; i++)
        dst[i] = src[i];
    return;
}

int get_c_idx(char *key, char character)
{
    for (int i = 0; i < strlen(key); i++)
    {
        if (key[i] == character)
            return i; // early return
    }

    return -1; // should not happen
}

/*
void counting_sort(char **arr, char **ans, char *key, char maxval, int len_arr, int radix)
parameters:
- arr: array to be sorted (char**)
- ans: pointer to sorted array (char**)
- key: sorting key (char*)
- maxval: originally, this parameter is the largest element in arr, however, for string
applications it is the size of the sorting key (int)
- radix: digit/position of the string to be sorted (int)

returns: none
*/
void counting_sort(char **arr, char **ans, char *key, char maxval, int len_arr, int radix)
{
    int *c = (int *)calloc(maxval + 1, sizeof(int));

    for (int i = 0; i < len_arr; i++)
    {
        int c_idx = get_c_idx(key, arr[i][radix]);
        c[c_idx] += 1;
    }

    for (int i = 1; i <= maxval; i++)
        c[i] += c[i - 1];

    // print counting array
    for (int i = 0; i < maxval; i++)
        printf("%d ", c[i]);
    printf("\n");

    for (int i = len_arr - 1; i >= 0; i--)
    {
        int c_idx = get_c_idx(key, arr[i][radix]);
        ans[c[c_idx] - 1] = arr[i];
        c[c_idx] -= 1;
    }

    return;
}

void radix_sort(char **arr, char **ans, char *key, int len_arr, int largest_strlen)
{
    char **aux = (char **)malloc(len_arr * sizeof(char *));
    copy_arr(arr, aux, len_arr);
    for (int radix = largest_strlen - 1; radix >= 0; radix--)
    {
        counting_sort(aux, ans, key, 27, len_arr, radix); // we'll have to update the maxval parameter on this call later
        copy_arr(ans, aux, len_arr);
    }

    return;
}

/*
 * rectify_str(char *str): converts all uppercase characters to lowercase
 parameters:
- str: string to be rectified (char*)
 */
void rectify_str(char *str)
{
    /*
     * acceptable range (lowercase and blankspaces): [97;122] U [32]
     * rectifiable range (uppercase): [65;90]
     */
    for (int i = 0; i < strlen(str); i++)
    {

        // rectifiable range
        if ((int)str[i] >= 65 && (int)str[i] <= 90)
            str[i] += 32;
    }
    return;
}

int main()
{
    int c; // clear buffer throwaway
    int len_words;
    char *key = (char *)malloc(LEXSIZE * sizeof(char));
    key[0] = (char)32; // shorter words first

    // scanning amount of words
    scanf("%d", &len_words);
    // clear buffer
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // do nothing
    }

    char **words = (char **)malloc(len_words * sizeof(char *));
    char **ans = (char **)malloc(len_words * sizeof(char *));

    // scanning sorting key
    for (int i = 1; i < LEXSIZE; i++)
        scanf("%c", &key[i]);
    // clear buffer
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // do nothing
    }

    // scanning word array
    int largest_len = 0;
    for (int k = 0; k < len_words; k++)
    {
        char *bufword = (char *)malloc(WORDSIZE * sizeof(char));
        scanf("%s", bufword);
        rectify_str(bufword);
        printf("%s.\n", bufword); // print rectified words
        if (strlen(bufword) > largest_len)
            largest_len = strlen(bufword);
        words[k] = bufword;
    }

    // printing largest_len
    printf("%d\n", largest_len);

    // filling in blankspaces
    for (int k = 0; k < len_words; k++)
    {
        int current_len = strlen(words[k]);
        if (current_len < largest_len)
        {
            for (int i = current_len; i < largest_len; i++)
            {
                words[k][i] = (char)32;
            }
        }
    }

    // calling sort function and printing array
    radix_sort(words, ans, key, len_words, largest_len);
    print_arr(ans, len_words, 0);
    return 0;
}