#include <stdio.h>
#include <stdlib.h>
#include "client.h"

char *p;
int size;

struct book
{
    int size_of_chunk;
    int status;
    struct book *next;
    struct book *prev;
};

static void initialize()
{
    struct book *initial_book;
    //Initilizing the first book
    initial_book = (void *)p;
    initial_book->next = NULL;
    initial_book->prev = NULL;
    initial_book->size_of_chunk = size - sizeof(struct book);
    initial_book->status = 2;
}

void allocate(int n)
{
    p = (char *)malloc(n * sizeof(char));
    size = n;
    initialize();
}

void *mymalloc(int size)
{

    struct book *temp_block = (void *)p;
    void *pointer_point;
    while (((temp_block->next != NULL) && (temp_block->status != 2)) || (temp_block->size_of_chunk < size))
    {
        temp_block = temp_block->next;
    }
    // If block size is equal to allocating memory
    if (temp_block->size_of_chunk == size)
    {
        temp_block->status = 1;
        pointer_point = (void *)(++temp_block);
        return pointer_point;
    }
    // If block size is greater than allocating memory
    else if (temp_block->size_of_chunk > size)
    {
        // case for allocation if the memory remaining is less than book memory.
        if (temp_block->size_of_chunk <= size + sizeof(struct book))
        {
            temp_block->status = 1;
            pointer_point = (void *)(++temp_block);
            return pointer_point;
        }
        // case for allocation when the memory remaining is more than book memory.
        else
        {
            struct book *new = (void *)((void *)temp_block + size + sizeof(struct book));
            new->size_of_chunk = (temp_block->size_of_chunk) - size - sizeof(struct book);
            new->status = 2;
            new->next = temp_block->next;
            temp_block->size_of_chunk = size;
            temp_block->status = 1;
            temp_block->next = new;
            //returning the changed pointer.
            pointer_point = (void *)(++temp_block);
            return pointer_point;
        }
    }
    else
    {
        pointer_point = NULL;
        return pointer_point;
    }
}

void myfree(void *b)
{
    struct book *temp_block = (void *)b;
    temp_block--;
    temp_block->status = 2;
    struct book *back = (void *)p;
    struct book *front = back->next;
    //Checking for adjacent free space.
    while (back->next != NULL)
    {
        // for last blocks with adjacent free space
        if (back->status == 2 && front->status == 2 && front->next == NULL)
        {
            back->size_of_chunk = back->size_of_chunk + (front->size_of_chunk + sizeof(struct book));
            back->next = front->next;
            break;
        }
        //for all other blocks with adjacent free space
        else if (back->status == 2 && front->status == 2)
        {
            back->size_of_chunk = back->size_of_chunk + (front->size_of_chunk + sizeof(struct book));
            back->next = front->next;
            back->next->prev = back;
            front = back->next;
        }
        // if both the adjacent blocks have no free memory
        else
        {
            back = back->next;
            front = back->next;
        }
    }
}

void print_book()
{
    printf("%ld\n", sizeof(struct book));
}

void display_mem_map()
{
    struct book *temp_block = (void *)p;
    int pointer_posotion = 0;
    while (temp_block != NULL)
    {
        // printing book
        printf("%d\t%ld\t%d\n", pointer_posotion, sizeof(struct book), 0);
        pointer_posotion = pointer_posotion + sizeof(struct book);
        // printing memory block
        printf("%d\t%ld\t%d\n", pointer_posotion, temp_block->size_of_chunk, temp_block->status);
        pointer_posotion = pointer_posotion + temp_block->size_of_chunk;
        temp_block = temp_block->next;
    }
}
