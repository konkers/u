#ifndef SANDBOX_TIME_H
#define SANDBOX_TIME_H

#include <stdint.h>

// TODO(konkers): I'm not happy with the name time because it conflicts with
// posix time.h. Clock also has the same problem.  Timer implies something
// that's actually counting vs just a value.

// TODO(konkers): Should time type be arch/platform specific?  This would mean
// that the compare functions would have to be architecture specific as well.
typedef uint32_t u_time_t;

static inline int32_t u_time_compare(u_time_t a, u_time_t b) {
    return (int32_t)(a - b);
}

#endif  // SANDBOX_TIME_H

