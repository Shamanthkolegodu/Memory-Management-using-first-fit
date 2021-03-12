# Memory-Management-using-first-fit

Memory Management using first fit policy, allocates the first sufficient free memory block from the start of main memory.

## Memory management policies:

First Fit: Allocates the first sufficient free memory block from the start of main memory.

Next Fit: Similar to the first fit policy, but allocates the first sufficient free memory block starting from the last allocation point. Move back to the beginning of the main memory, once you reach the end.

Best Fit: Allocates the smallest sufficient memory block among the available free memory blocks. If there are multiple blocks with the same smallest size, choose the first one.

## Functions to be implemented :

1. void allocate (int n)
   Allocates memory of n bytes to the global character array.
   The memory allocated by mymalloc () function + memory needed to store the book-keeping structure must be allocated within those n bytes itself.
2. void mymalloc (int size)
   Allocates ‘size’ bytes from the available memory and returns a pointer pointing to this memory block.
   Allocate memory based on the memory allocation policy assigned to you, i.e, FirstFit, NextFit, or BestFit.
   If no free memory block is available, return NULL.
3. void myfree (void\* b)
   Free the block of memory pointed by pointer ‘b’.
   Should merge free blocks adjacent to the newly freed block.
   Note: Only valid pointers will be passed as parameters to the function.
4. void print_book_size ( )
   Prints the size of the book-keeping structure.
   Use the following print statement in this function
   printf(“%ld\n”,size_of_structure);
   Do not include any other code in this function. Do not change the above print statement.
5. void display_mem_map ( )
   Display the view of memory at any instance it is called.
   Structure of output:
   Start_address<\t>block_in_bytes<\t>encoded_status<\n>

- Allocation policy used: First Fit method.
  The memory space is traversed and allocation happens in the first free space that is found on linear traversal from start to end of memory.

- Basic logic used for implementation: Singly linked lists
  A singly linked list with each node with book-keeping information is created. The memory space is typecasted to structure type wherever necessary
  for the implementation of the same and consecutive book-keeping nodes connected in a typical singly list fashion.

- Explanation of the book-keeping structure:
  buffer : number of bytes/blocks allocated or free
  encoded_flag : 1 - allocated space ; 2 - free space (0 is explicitly print for bookkeeping in print_mem_map() function)
  link : the pointer holding the address of next book keeping node in the linked lists of book keeping nodes
  returned : the pointer pointing to the first allocated block which is returned to the caller.

### Fine techniques course @PES University.

## Additional notes:

The code is written in such a way that if mymalloc function is called before allocate function, it returns NULL
The validity of b pointer passed as parameter to myfree function is not verified
size_of_structure is defined using #define and is not a global variable, hence cannot be accessed in sanity_client.c
Due to %ld format specifier in the print statement of size_of_structure in print_book function, compilation is giving a warning to change it to unsigned int.
But it was not rectified as the print statement was not asked to be changed in the doc file.
