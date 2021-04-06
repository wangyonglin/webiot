#WANGYONGLIN HTTP SERVER
### https 测试成功
    http://mqtt.wangyonglin.com/mosquitto?sign=wangyonglin&topic=wangyonglin&payload=4543rtnj43t4gf
### 安装其他依赖包
    yum install make gcc openssl-devel mosquitto-devel mosquitto libevent-devel
#### 如果 mosquitto-devel mosquitto 没法安装 就运行 sudo yum install epel-release
##安装Tengine 编译参数
```shell
./configure --prefix=/usr/local/wangyonglin
```
gcc -o Master Server.c
gcc -o Slave Client.c
handle SIGUSR1 noprint nostop
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
