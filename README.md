#WANGYONGLIN HTTP SERVER

##安装Tengine 编译参数
```shell
./configure --prefix=/usr/local/wangyonglin
```
gcc -o Master Server.c
gcc -o Slave Client.c
## 配置wangyonglin开机启动，切换到/lib/systemd/system目录,创建 wangyonglin.service文件：
```shell
[Unit]
Description=wangyonglin
After=network.target
[Service]
Type=forking
ExecStart=/usr/local/wangyonglin/bin/wangyonglin
ExecReload=/usr/local/wangyonglin/bin/wangyonglin reload
ExecStop=/usr/local/wangyonglin/bin/wangyonglin quit
PrivateTmp=true
[Install]
WantedBy=multi-user.target
```
