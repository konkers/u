#include <stdio.h>
#include <stdlib.h>

#include <sandbox/coro_test.h>

void *coro_alloc(size_t size) {
    printf("allocating %ld.\n", size);
    return malloc(size);
}

void *f(int id) {
  CORO_BEGIN(coro_alloc);

    CORO_SUSPEND();

  for (int i = 0;; ++i) {
      printf("%d: %d\n", 0, i);
    CORO_SUSPEND();
  }

  CORO_END(free);
}

int main(int argc, char *argv[]) {
  void *coro1 = f(0);
 // void *coro2 = f(1);

  for (int i = 0; i < 3; i++) {
      CORO_RESUME(coro1);
  //    CORO_RESUME(coro2);
  }
  CORO_DESTROY(coro1);
  //CORO_DESTROY(coro2);

  return 0;
}
