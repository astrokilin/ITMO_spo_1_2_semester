#ifndef GENERAL_H
#define GENERAL_H

typedef enum 
{
    ERROR,
    SUCCESS
}default_retcode;

#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)

#define LOG2(X) ((unsigned) (8*sizeof (unsigned long long) - __builtin_clzll((X)) - 1))

#endif
