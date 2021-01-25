AUTOMAKE_OPTIONS=foreign
SUBDIRS = \
    src/ccl  \
    src/cjson \
    src/core \
     src/aliyun \
    src/server \
    src/https \
    app
bindir =    $(prefix)/bin
libdir =    $(prefix)/lib

logsdir =    $(prefix)/logs
logs_DATA = \
    $(top_srcdir)/logs/error.log  \
    $(top_srcdir)/logs/access.log 
confdir =   $(prefix)/conf
conf_DATA = \
    $(top_srcdir)/conf/wangyonglin.conf
datadir=    $(prefix)/share
sysconfdir= $(prefix)/etc
includedir= $(prefix)/include