AUTOMAKE_OPTIONS=foreign
SUBDIRS = \
    src/cjson \
    src/core \
    src/https \
    src/mosquitto \
    src/user




includedir= $(prefix)/include
bindir =    $(prefix)/bin
libdir =    $(prefix)/lib

logsdir =    $(prefix)/logs
logs_DATA = \
        $(top_srcdir)/logs/error.log  \
        $(top_srcdir)/logs/access.log 

confdir =   $(prefix)/conf
conf_DATA = $(top_srcdir)/conf/wangyonglin.conf

datadir=    $(prefix)/share
sysconfdir= $(prefix)/etc
EXTRA_DIST =   $(top_srcdir)/include     $(top_srcdir)/logs  $(top_srcdir)/conf
                               
