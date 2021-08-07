AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=wangyonglin
wangyonglin_SOURCES=application.c 
AM_CPPFLAGS=-I $(top_srcdir)/include/
wangyonglin_LDADD= \
    $(top_srcdir)/src/wangyonglin/libwangyonglin.la \
    $(top_srcdir)/src/https/libhttps.la \
    $(top_srcdir)/src/mosquitto/libmqtt.la \
    $(FLIBS)
LIBS += -Wall -pedantic -lmosquitto  -lm -levent -lssl -lcrypto -lpthread -levent_openssl -lcjson