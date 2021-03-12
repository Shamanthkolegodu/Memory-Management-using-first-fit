#include <stdio.h>
#include "client.h"

void main()
{
    allocate(200);
    print_book();
    display_mem_map();
    printf("\n");
    char *a = (char *)mymalloc(30 * sizeof(char));
    display_mem_map();
    printf("\n");
    char *b = (char *)mymalloc(40 * sizeof(char));
    display_mem_map();
    printf("\n");
    char *c = (char *)mymalloc(30 * sizeof(char));
    display_mem_map();
    printf("\n");
    myfree(a);
    display_mem_map();
    printf("\n");
    myfree(b);
    display_mem_map();
    printf("\n");
    myfree(c);
    display_mem_map();
    allocate(300);
}