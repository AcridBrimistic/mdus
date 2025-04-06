#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#include <event2/event.h>
#include <event2/thread.h>
#include <event2/http.h>

#include <curl/curl.h>

#include "options.h"
#include "server.h"
#include "util.h"
#include "main.h"

#define PROGRAM_NAME "mdus"
#define PROGRAM_VERSION "0.0.2"

extern pthread_mutex_t active_request_lock;
extern pthread_mutex_t request_pending_lock;
extern pthread_cond_t  request_pending_cond;
extern pthread_mutex_t pool_ready_lock;
extern pthread_cond_t  pool_ready_cond;
extern int pool_ready_count;
