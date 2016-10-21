#ifndef UTIL_H_
#define UTIL_H_

#ifndef ELEMENTSOF
#define ELEMENTSOF(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif /* ndef ELEMENTSOF */

#define ROUND_ORDER_TWO(n, o) (n + (1 << o) - 1) & ~((1 << o) - 1)
#define ROUND_2(n) ROUND_ORDER_TWO((n), 1)
#define ROUND_4(n) ROUND_ORDER_TWO((n), 2)
#define ROUND_8(n) ROUND_ORDER_TWO((n), 3)
#define ROUND_16(n) ROUND_ORDER_TWO((n), 4)
#define ROUND_32(n) ROUND_ORDER_TWO((n), 5)
#define ROUND_64(n) ROUND_ORDER_TWO((n), 6)
#define ROUND_128(n) ROUND_ORDER_TWO((n), 7)
#define ROUND_256(n) ROUND_ORDER_TWO((n), 8)
#define ROUND_512(n) ROUND_ORDER_TWO((n), 9)
#define ROUND_1024(n) ROUND_ORDER_TWO((n), 10)

#endif /* UTIL_H_ */
