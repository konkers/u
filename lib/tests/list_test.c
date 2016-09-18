#include <external/unity/src/unity.h>
#include <lib/list.h>

struct test_elem {
    struct list_head list;
    uint32_t val;
};

void setUp(void) {
}

void tearDown(void) {
}

static void test_list_add_front(void) {
    struct list_head list;
    struct test_elem elem0 = {.val = 0};
    struct test_elem elem1 = {.val = 1};
    struct test_elem elem2 = {.val = 2};
    struct test_elem elem3 = {.val = 3};

    list_init(&list);
    list_push_front(&list, &elem0.list);
    list_push_front(&list, &elem1.list);
    list_push_front(&list, &elem2.list);
    list_push_front(&list, &elem3.list);

    uint32_t val = 3;
    struct list_head *e;
    list_foreach(&list, e) {
        struct test_elem *elem;
        elem = container_of(e, struct test_elem, list);
        TEST_ASSERT_EQUAL_UINT32(val, elem->val);
        val--;
    }

    val = 0;
    list_foreach_rev(&list, e) {
        struct test_elem *elem;
        elem = container_of(e, struct test_elem, list);
        TEST_ASSERT_EQUAL_UINT32(val, elem->val);
        val++;
    }
    TEST_ASSERT_EQUAL_UINT32(4, val);
}

static void test_list_add_back(void) {
    struct list_head list;
    struct test_elem elem0 = {.val = 0};
    struct test_elem elem1 = {.val = 1};
    struct test_elem elem2 = {.val = 2};
    struct test_elem elem3 = {.val = 3};

    list_init(&list);
    list_push_back(&list, &elem0.list);
    list_push_back(&list, &elem1.list);
    list_push_back(&list, &elem2.list);
    list_push_back(&list, &elem3.list);

    uint32_t val = 0;
    struct list_head *e;
    list_foreach(&list, e) {
        struct test_elem *elem;
        elem = container_of(e, struct test_elem, list);
        TEST_ASSERT_EQUAL_UINT32(val, elem->val);
        val++;
    }
    TEST_ASSERT_EQUAL_UINT32(4, val);

    val = 3;
    list_foreach_rev(&list, e) {
        struct test_elem *elem;
        elem = container_of(e, struct test_elem, list);
        TEST_ASSERT_EQUAL_UINT32(val, elem->val);
        val--;
    }
    TEST_ASSERT_EQUAL_UINT32(0 - 1, val);

    val = 0;
    struct test_elem *elem;
    list_foreach_container(&list, elem, list) {
        TEST_ASSERT_EQUAL_UINT32(val, elem->val);
        val++;
    }
    TEST_ASSERT_EQUAL_UINT32(4, val);

    val = 3;
    list_foreach_container_rev(&list, elem, list) {
        TEST_ASSERT_EQUAL_UINT32(val, elem->val);
        val--;
    }
    TEST_ASSERT_EQUAL_UINT32(0 - 1, val);
}

static void test_list_insert(void) {
    struct list_head list;
    struct test_elem elem0 = {.val = 0};
    struct test_elem elem1 = {.val = 1};
    struct test_elem elem2 = {.val = 2};
    struct test_elem elem3 = {.val = 3};

    list_init(&list);
    list_push_back(&list, &elem0.list);
    list_push_back(&list, &elem3.list);
    list_insert_after(&elem0.list, &elem1.list);
    list_insert_before(&elem3.list, &elem2.list);


    uint32_t val = 0;
    struct test_elem *elem;
    list_foreach_container(&list, elem, list) {
        TEST_ASSERT_EQUAL_UINT32(val, elem->val);
        val++;
    }
    TEST_ASSERT_EQUAL_UINT32(4, val);

    val = 3;
    list_foreach_container_rev(&list, elem, list) {
        TEST_ASSERT_EQUAL_UINT32(val, elem->val);
        val--;
    }
    TEST_ASSERT_EQUAL_UINT32(0 - 1, val);
}

int main(int argc, char *argv[]) {
    UNITY_BEGIN();

    RUN_TEST(test_list_add_front);
    RUN_TEST(test_list_add_back);
    RUN_TEST(test_list_insert);

    return UNITY_END();
}
