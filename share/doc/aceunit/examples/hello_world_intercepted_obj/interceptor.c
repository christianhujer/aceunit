#include "interceptor.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int base;
    int original;
    int intercepted[2];
} Channel;

typedef struct Interceptor {
    Channel out;
    Channel err;
} Interceptor;

void Channel_start(Channel *self, int fd) {
    self->base = fd;
    self->original = dup(self->base);
    if (self->original < 0) {
        perror("dup failed");
        abort();
    }
    if (pipe(self->intercepted) < 0) {
        perror("pipe failed");
        abort();
    }
    if (dup2(self->intercepted[1], self->base) < 0) {
        perror("dup2 failed");
        abort();
    }
}

void Channel_slurp(Channel *self, char *buffer, size_t bufferSize) {
    if (dup2(self->original, self->base) < 0) {
        perror("dup2 restore failed");
        abort();
    }
    close(self->intercepted[1]);

    ssize_t bytes_read = read(self->intercepted[0], buffer, bufferSize - 1);
    if (bytes_read < 0) {
        bytes_read = 0;
    }
    buffer[bytes_read] = '\0';

    close(self->intercepted[0]);
    close(self->original);
}


Interceptor *Interceptor_start(void) {
    Interceptor *self = malloc(sizeof(*self));
    assert(self);

    fflush(stdout);
    fflush(stderr);

    Channel_start(&self->out, STDOUT_FILENO);
    Channel_start(&self->err, STDERR_FILENO);

    return self;
}

void Interceptor_stop(Interceptor **self, char *stdoutBuffer, size_t stdoutBufferSize, char *stderrBuffer, size_t stderrBufferSize) {
    assert(self);
    assert(*self);

    assert(stdoutBuffer);
    assert(stderrBuffer);

    fflush(stdout);
    fflush(stderr);

    Channel_slurp(&(*self)->out, stdoutBuffer, stdoutBufferSize);
    Channel_slurp(&(*self)->err, stderrBuffer, stderrBufferSize);

    free(*self);
    *self = NULL;
}
