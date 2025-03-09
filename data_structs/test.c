#include <stdio.h>
#include <string.h>
#include "sizes_deque.h"

int main(int argc, char **argv)
{
    struct sizes_deque Q;
    size_t A[] = {1, 2 , 3 , 4, 5, 6};

    sizes_deque_init(&Q, 4);
    sizes_deque_head_append(&Q, 0);
    sizes_deque_head_append_from(&Q, 6, A);

    printf("%ld\n", sizes_deque_tail_pop(&Q));
    printf("%ld\n", sizes_deque_tail_pop(&Q));
    printf("%ld\n", sizes_deque_tail_pop(&Q));


    return 0;
}

