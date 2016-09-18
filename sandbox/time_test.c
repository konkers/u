#include <stdio.h>

#include <external/unity/src/unity.h>
#include <sandbox/time.h>

void setUp(void) {
}

void tearDown(void) {
}

static void test_time_compare(void) {
    TEST_ASSERT(u_time_compare(0x1, 0x0) > 0);
    TEST_ASSERT(u_time_compare(0x0, 0x0) == 0);
    TEST_ASSERT(u_time_compare(0x0, 0x1) < 0);

    u_time_t time_a = 0x10000000;
    u_time_t time_b = 0x00000000;
    for (int i = 0; i < 16; i++) {
        TEST_ASSERT(u_time_compare(time_a, time_a) == 0);
        TEST_ASSERT(u_time_compare(time_a, time_b) > 0);
        TEST_ASSERT(u_time_compare(time_b, time_a) < 0);

        time_a += 0x10000000;
        time_b += 0x10000000;
    }

    time_a = 0x7fffffff;
    time_b = 0x00000000;
    for (int i = 0; i < 16; i++) {
        TEST_ASSERT(u_time_compare(time_a, time_a) == 0);
        TEST_ASSERT(u_time_compare(time_a, time_b) > 0);
        TEST_ASSERT(u_time_compare(time_b, time_a) < 0);

        time_a += 0x10000000;
        time_b += 0x10000000;
    }
}

int main(int argc, char *argv[]) {
    UNITY_BEGIN();

    RUN_TEST(test_time_compare);

    return UNITY_END();
}
