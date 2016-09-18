#include <tools/testing/test.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <lib/list.h>

struct test {
    struct list_head list;
    void (*func)(void);
    const char *name;
    const char *file;
    int line;
};

LIST(test_list);

void test_add(void (*test_func)(void), const char *name,
              const char *file, int line) {
    struct test *test = malloc(sizeof(struct test));
    assert(test);
    test->func = test_func;
    test->name = name;
    test->file = file;
    test->line = line;
    list_push_back(&test_list, &test->list);
}

// These are required for unity.
void setUp(void) {
}

void tearDown(void) {
}

extern struct _Unity Unity;

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    UNITY_BEGIN();

    struct test *test;
    list_foreach_container(&test_list, test, list) {
        // Hack to get test results printing correctly.
        Unity.TestFile = test->file;
        UnityDefaultTestRun(test->func, test->name, test->line);
    }

    return UNITY_END();
}
