AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=wangyonglin
wangyonglin_SOURCES=main.c 
AM_CPPFLAGS=-I ../include/
wangyonglin_LDADD= \
    $(top_srcdir)/src/ccl/libccl.la \
    $(top_srcdir)/src/cjson/libjson.la \
    $(top_srcdir)/src/core/libcore.la \
    $(top_srcdir)/src/network/libnetwork.la \
    $(FLIBS)
LIBS += -lm -levent -lssl  -lcrypto -lpthread