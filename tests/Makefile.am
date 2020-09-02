AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=test
test_SOURCES=main.c http.c
AM_CPPFLAGS=-I ../include/
test_LDADD= ../src/cjson/libjson.la ../src/wangyonglin/libcore.la $(FLIBS)
LIBS += -lm -levent