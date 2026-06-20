#ifndef INTERCEPTOR_H
#define INTERCEPTOR_H

#include <stddef.h>

typedef struct Interceptor Interceptor;

Interceptor *Interceptor_start(void);
extern void Interceptor_stop(Interceptor **self, char *stdoutBuffer, size_t stdoutBufferSize, char *stderrBuffer, size_t stderrBufferSize);

#endif
