#ifndef REDISMQ_H
#define REDISMQ_H

#include <sys/queue.h>

#define RMQ_NONE 0
#define RMQ_BLPOP 1
#define RMQ_RPUSH 2

typedef void (rmq_callback)(char*);

struct rmq_message {
    char *message;
    STAILQ_ENTRY(rmq_message) entries;
};

struct rmq_context {
    // blpop or rpush
    int type;

    // redis config
    const char *redis_host;
    int redis_port;
    int redis_db;

    // redis key
    const char *key;

    // pointer to redis context
    void *redis_ctx;
    int connected;

    // callback for blpop
    rmq_callback *blpop_cb;

    // message queue for rpush
    STAILQ_HEAD(rmq_message_head, rmq_message) head;
};

void rmq_init(struct rmq_context *ctx, const char *redis_host, int redis_port,
    int redis_db, const char *key);

void rmq_blpop(struct rmq_context *ctx, rmq_callback *blpop_cb);

void rmq_rpush(struct rmq_context *ctx, const char *message);

#endif
