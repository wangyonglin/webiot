AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=wangyonglin
wangyonglin_SOURCES=main.c httpserver.c jsonresult.c
AM_CPPFLAGS=-I ../include/
wangyonglin_LDADD= ../src/cjson/libjson.la ../src/wangyonglin/libcore.la $(FLIBS)
LIBS += -lm -levent