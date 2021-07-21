AUTOMAKE_OPTIONS=foreign
SUBDIRS = \
    src/wangyonglin \
    src/https \
    src/mosquitto \
    src/application
includedir= \
    $(prefix)/include
bindir =    \
    $(prefix)/bin
libdir =    \
    $(prefix)/lib

logsdir =   \
    $(prefix)/logs
logs_DATA = \
    $(top_srcdir)/logs/wangyonglin.log
confdir =   $(prefix)/conf
conf_DATA = $(top_srcdir)/conf/wangyonglin.conf

certdir         = \
    $(prefix)/cert
cert_DATA = \
    $(top_srcdir)/cert/broker.wangyonglin.com.key  \
    $(top_srcdir)/cert/broker.wangyonglin.com.pem
datadir         =\
    $(prefix)/share
sysconfdir      = \
    $(prefix)/etc
EXTRA_DIST      = \
    $(top_srcdir)/include \
    $(top_srcdir)/logs  \
    $(top_srcdir)/conf  \
    $(top_srcdir)/cert
