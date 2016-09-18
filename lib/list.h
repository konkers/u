#ifndef LIB_LIST_H_
#define LIB_LIST_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// TODO(konkers): This really belongs somewhere else.
#define container_of(p, type, member) \
    ((type *)((uint8_t *)(p) - offsetof(type, member)))

struct list_head {
    struct list_head *next;
    struct list_head *prev;
};

#define LIST(name) struct list_head name = {.next = &(name), .prev = &(name)}

static inline void list_init(struct list_head *list) {
    list->next = list;
    list->prev = list;
}

static inline void list_insert_after(struct list_head *cur_elem,
                                     struct list_head *new_elem) {
    new_elem->next = cur_elem->next;
    new_elem->prev = cur_elem;
    cur_elem->next->prev = new_elem;
    cur_elem->next = new_elem;
}

static inline void list_insert_before(struct list_head *cur_elem,
                                     struct list_head *new_elem) {
    new_elem->next = cur_elem;
    new_elem->prev = cur_elem->prev;
    cur_elem->prev->next = new_elem;
    cur_elem->prev = new_elem;
}

static inline void list_push_front(struct list_head *list,
                                   struct list_head *elem) {
    list_insert_after(list, elem);
}

static inline void list_push_back(struct list_head *list,
                                  struct list_head *elem) {
    list_insert_before(list, elem);
}

static inline struct list_head *list_front(struct list_head *list) {
    return list->next;
}

static inline struct list_head *list_back(struct list_head *list) {
    return list->prev;
}

static inline bool list_is_end(struct list_head *list, struct list_head *elem) {
    return list == elem;
}

#define list_container(list, type, member) \
    container_of(list, type, member)

#define list_container_next(elem, member) \
    container_of(elem->member.next, typeof(*elem), member)

#define list_container_prev(elem, member) \
    container_of(elem->member.prev, typeof(*elem), member)

#define list_foreach(list, elem)    \
    for (elem = list_front((list)); \
         !list_is_end(list, elem);  \
         elem = elem->next)

#define list_foreach_rev(list, elem) \
    for (elem = list_back((list));   \
         !list_is_end(list, elem);   \
         elem = elem->prev)

#define list_foreach_container(list, elem, member)                       \
    for (elem = list_container(list_front(list), typeof(*elem), member); \
         !list_is_end(list, &elem->member);                              \
         elem = list_container_next(elem, member))

#define list_foreach_container_rev(list, elem, member)                  \
    for (elem = list_container(list_back(list), typeof(*elem), member); \
         !list_is_end(list, &elem->member);                             \
         elem = list_container_prev(elem, member))

#endif // LIB_LIST_H_

