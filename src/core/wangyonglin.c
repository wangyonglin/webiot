#include <wangyonglin/linux_config.h>
#include <wangyonglin/wangyonglin.h>

int main(int argc, char *argv[])
{
	int rc;
	struct wangyonglin__config config;

	config__init(&config);
	rc = config__load(&config, argc, argv);
	if (rc != ERR_SUCCESS)
		return rc;
	/**开启日志功能**/
	log__init(&config);
	/**开启守护进程**/
	if (config.daemon)
	{
		wangyonglin__daemonise(&config);
	}

	/**写入pid文件**/
	rc = wangyonglin__pid_write(&config);
	if (rc != ERR_SUCCESS)
		return rc;

	application(&config);
	/**关闭日志功能**/
	log__close(&config);
	config__cleanup(&config);
	return rc;
}