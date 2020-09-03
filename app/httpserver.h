#ifndef _APP_HTTPSERVER_H_INCLUDE_
#define _APP_HTTPSERVER_H_INCLUDE_
#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <evhttp.h>
#include <event.h>
#include "event2/http.h"
#include "event2/event.h"
#include "event2/buffer.h"
#include "event2/bufferevent.h"
#include "event2/bufferevent_compat.h"
#include "event2/http_struct.h"
#include "event2/http_compat.h"
#include "event2/util.h"
#include "event2/listener.h"

typedef struct httpd_info{
	struct event_base *base;
	struct evhttp *httpd;
}httpd_info;


int wangyonglin_httpserver_start(int port, int nthreads, int backlog);




#endif /**_APP_HTTPSERVER_H_INCLUDE_**/