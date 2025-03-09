#ifndef COMPILLER_INTEGERS_H
#define COMPILLER_INTEGERS_H

#include <stdint.h>
#include <stddef.h>

#ifdef __SIZEOF_INT128__
    typedef unsigned __int128 uint128_t;

    inline static uint128_t
    uint128_add(const uint128_t a, const uint128_t b)
    {
        return a + b;
    }

/*
    inline static uint128_t
    uint128_add_overflow(const uint128_t a, const uint128_t b, char *const overfl)
    {
        uint128_t res;
        *overfl = __builtin_add_overflow(a, b, &res);
        return res;
    }
*/

    inline static uint128_t
    uint128_mul(const uint128_t a, const uint128_t b)
    {
        return a * b;
    }
/*
    inline static uint128_t
    uint128_mul_overflow(const uint128_t a, const uint128_t b, char *const overfl)
    {
        uint128_t res;
        *overfl = __builtin_mul_overflow(a, b, &res);
        return res;
    }
*/

    inline static uint128_t
    uint128_cmp(const uint128_t a, const uint128_t b)
    {
        return a == b;
    }

    inline static uint128_t
    uint128_lshift(const uint128_t a,  const unsigned char shift)
    {
        return a << shift;
    }

    inline static uint128_t
    uint128_from_i64(const uint64_t x)
    {
        return (uint128_t) x;
    }

    inline static uint64_t
    uint128_to_i64(const uint128_t x)
    {
        return (uint64_t) x;
    }

    inline static uint128_t
    uint128_add_i64(uint128_t a, const uint64_t x)
    {
        return a + x;
    }

    inline static uint128_t
    uint128_add_i64_overflow(uint128_t a, const uint64_t x, char *const overf)
    {
        *overf = __builtin_add_overflow(a, x, &a);
        return a;
    }

    inline static uint128_t
    uint128_mul_i64(uint128_t a, const uint64_t x)
    {
        return a * x;
    }

    inline static uint128_t
    uint128_mul_i64_overflow(uint128_t a, const uint64_t x, char *const overf)
    {
        *overf = __builtin_mul_overflow(a, x, &a);
        return a;
    }


    inline static uint64_t
    uint128_high_half(const uint128_t x)
    {
        return x >> 64;
    }


#else
    typedef struct
    {
        uint64_t l_half;
        uint64_t r_half;
    }uint128_t;

    inline static uint128_t
    uint128_add(const uint128_t a, const uint128_t b)
    {
        uint128_t res;

        res.l_half = __builtin_add_overflow(a.r_half, b.r_half, &res.r_half);
        res.l_half += a.l_half + b.l_half;
        return res;
    }
/*
    inline static uint128_t
    uint128_add_overflow(const uint128_t a, const uint128_t b, char *const overfl)
    {
        uint128_t res;
        char overflowed = 0;

        res.l_half = __builtin_add_overflow(a.r_half, b.r_half, &res.r_half);

        *overfl = __builtin_add_overflow(res.l_half,a.r_half, &res.l_half)
                  | __builtin_add_overflow(res.l_half, b.r_half, &res.l_half);
        return res;
    }
*/
    inline static uint128_t
    uint128_mul(const uint128_t a, const uint128_t b)
    {
        uint128_t res;

        res.l_half = __builtin_mul_overflow(a.r_half, b.r_half, &res.r_half);
        res.l_half += a.l_half * b.r_half + a.r_half * b.l_half;
        return res;
    }
/*
    inline static uint128_t
    uint128_mul_overflow(const uint128_t a, const uint128_t b, char *const overfl)
    {
        uint128_t res;
        uint64_t tmp;

        res.l_half = __builtin_mul_overflow(a.r_half, b.r_half, &res.r_half);

        *overfl = __builtin_mul_overflow(a.l_half, b.r_half, &tmp)
                  | __builtin_add_overflow(res.l_half, tmp, &res.l_half)
                  | __builtin_mul_overflow(a.r_half, b.l_half, &tmp)
                  | __builtin_add_overflow(res.l_half, tmp, &res.l_half);
        return res;
    }
*/

    inline static uint128_t
    uint128_cmp(const uint128_t a, const uint128_t b)
    {
        return a.l_half == b.l_half && a.r_half == b.r_half;
    }

    inline static uint128_t
    uint128_lshift(const uint128_t a,  const unsigned char shift)
    {
        uint128_t res;

        if (shift >= 64)
        {
            res.l_half = a.r_half << (shift - 64);
            res.r_half = 0;
        }
        else
        {
            res.l_half = (res.l_half << shift) | (a.r_half >> (64 - shift));
            res.r_half = res.r_half << shift;
        }

        return res;
    }

    inline static uint128_t
    uint128_from_i64(const uint64_t x)
    {
        uint128_t res;

        res.l_half = 0;
        res.r_half = x;

        return res;
    }

    inline static uint128_t
    uint128_add_i64(uint128_t a, const uint64_t x)
    {
        a.l_half += __builtin_add_overflow(a.r_half, x, &a.r_half); 
        return a;
    }

    inline static uint128_t
    uint128_add_i64_overflow(uint128_t a, uint64_t x, char *const overf)
    {
        x = __builtin_add_overflow(a.r_half, x, &a.r_half); 
        *overf = __builtin_add_overflow(a.l_half, x, &a.l_half);
        return a;
    }

    inline static uint128_t
    uint128_mul_i64(const uint128_t a, const uint64_t x)
    {
        uint128_t res;

        res.l_half = __builtin_mul_overflow(a.r_half, x, &res.r_half);
        res.l_half += a.l_half * x;
        return res;
    }

    inline static uint128_t
    uint128_mul_i64_overflow(const uint128_t a, const uint64_t x, char *const overf)
    {
        uint128_t res;
        uint64_t tmp;

        res.l_half = __builtin_mul_overflow(a.r_half, x, &res.r_half);
        *overf = __builtin_mul_overflow(a.l_half, x, &tmp)
                 | __builtin_add_overflow(res.l_half, tmp, &res.l_half);
        return res;

    }

    inline static uint64_t
    uint128_to_i64(const uint128_t x)
    {
        return x.r_half;
    }

    inline static uint64_t
    uint128_high_half(const uint128_t x)
    {
        return x.l_half;
    }

#endif
#endif

