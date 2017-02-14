#include <stdbool.h>

size_t __builtin_coro_size();
void  *__builtin_coro_frame();
void  *__builtin_coro_free(void *coro_frame);

void  *__builtin_coro_id(int align, void *promise, void *fnaddr, void *parts);
bool   __builtin_coro_alloc();
void  *__builtin_coro_begin(void *memory);
void   __builtin_coro_end(void *coro_frame, bool unwind);
char   __builtin_coro_suspend(bool final);
bool   __builtin_coro_param(void *original, void *copy);

#define CORO_SUSPEND_IMPL(IsFinal)                                             \
  switch (__builtin_coro_suspend(IsFinal)) {           \
  case 0:                                                                      \
    if (IsFinal)                                                               \
      __builtin_trap();                                                        \
    break;                                                                     \
  case 1:                                                                      \
    goto coro_Cleanup;                                                         \
  default:                                                                     \
    goto coro_Suspend;                                                         \
  }

#define CORO_SUSPEND() CORO_SUSPEND_IMPL(0)
#define CORO_FINAL_SUSPEND() CORO_SUSPEND_IMPL(1)

#define CORO_BEGIN(AllocFunc)                                                  \
  __builtin_coro_id(0, NULL, NULL, NULL);                         \
  void *frame = NULL; \
  if (__builtin_coro_alloc()) { \
    frame = AllocFunc(__builtin_coro_size()); \
  } \
  void *coro_hdl = __builtin_coro_begin(frame);

#define CORO_END(FreeFunc)                                                     \
  coro_Cleanup : {                                                             \
    void *coro_mem = __builtin_coro_free(__builtin_coro_frame());                            \
    if (coro_mem)                                                              \
      FreeFunc(coro_mem);                                                      \
  }                                                                            \
  coro_Suspend:                                                                \
  __builtin_coro_end(__builtin_coro_frame(), 0);                                                    \
  return coro_hdl;

#define CORO_RESUME(hdl) __builtin_coro_resume(hdl)
#define CORO_DESTROY(hdl) __builtin_coro_destroy(hdl)
