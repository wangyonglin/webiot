#include "event2/http.h"
#include "event2/event.h"
#include "event2/buffer.h"

#include <stdlib.h>
#include <stdio.h>

void HttpGenericCallback(struct evhttp_request* request, void* arg)
{
    const struct evhttp_uri* evhttp_uri = evhttp_request_get_evhttp_uri(request);
    char url[8192];
    evhttp_uri_join(const_cast<struct evhttp_uri*>(evhttp_uri), url, 8192);

    printf("accept request url:%s\n", url);

    struct evbuffer* evbuf = evbuffer_new();
    if (!evbuf)
    {
        printf("create evbuffer failed!\n");
        return ;
    }

    evbuffer_add_printf(evbuf, "Server response. Your request url is %s", url);
    evhttp_send_reply(request, HTTP_OK, "OK", evbuf);
    evbuffer_free(evbuf);
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("usage:%s port\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    if (port == 0)
    {
        printf("port error:%s\n", argv[1]);
        return 1;
    }

    struct event_base* base = event_base_new();
    if (!base)
    {
        printf("create event_base failed!\n");
        return 1;
    }

    struct evhttp* http = evhttp_new(base);
    if (!http)
    {
        printf("create evhttp failed!\n");
        return 1;
    }

    if (evhttp_bind_socket(http, "0.0.0.0", port) != 0)
    {
        printf("bind socket failed! port:%d\n", port);
        return 1;
    }

    evhttp_set_gencb(http, HttpGenericCallback, NULL);

    event_base_dispatch(base);
    return 0;
}

