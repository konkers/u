#ifndef TOOLS_TESTING_TEST_H_
#define TOOLS_TESTING_TEST_H_

#include <external/unity/src/unity.h>

void test_add(void (*test_func)(void), const char *name,
              const char *file, int line);

#define TEST(test_func) \
    __attribute__((constructor)) \
    static void test_func ## _constructor(void) { \
        test_add(test_func, #test_func, __FILE__, __LINE__); \
    }

#endif  // TOOLS_TESTING_TEST_H_

