AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=wangyonglin
wangyonglin_SOURCES=main.c 
AM_CPPFLAGS=-I ../include/
wangyonglin_LDADD= \
    $(top_srcdir)/src/ccl/libccl.la \
    $(top_srcdir)/src/cjson/libjson.la \
    $(top_srcdir)/src/core/libcore.la \
    $(top_srcdir)/src/server/libserver.la \
    $(top_srcdir)/src/https/libhttps.la \
    $(top_srcdir)/src/aliyun/libaliyun.la 
    $(FLIBS)
LIBS += -lm -levent -lssl  -lcrypto -lpthread -lcurl