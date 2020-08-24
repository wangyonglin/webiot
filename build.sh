#/bin/bash/
aclocal
autoheader
automake --add-missing
autoconf
./configure --prefix=/usr/local/wangyonglin
