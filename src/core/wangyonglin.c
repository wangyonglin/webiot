#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
struct wangyonglin__config *config = NULL;
int main(int argc, char *argv[])
{
	int rc;
	config = wangyonglin__config_new();
	rc = wangyonglin__config_load(config, argc, argv);
	if (rc != ERR_SUCCESS)
		return rc;
	/**开启日志功能**/
	wangyonglin__log_init(config);
	/**开启守护进程**/
	rc = wangyonglin__daemon(config);
	if (rc != ERR_SUCCESS)
		return rc;
	/**测试文件 pid **/
	rc = wangyonglin__pid_test(config);
	if (rc != ERR_SUCCESS)
		return rc;
	/**写入文件 pid**/
	rc = wangyonglin__pid_create(config);
	if (rc != ERR_SUCCESS)
		return rc;

	rc = application(config);
	if (rc != ERR_SUCCESS)
		return rc;
	/**删除文件	pid**/
	wangyonglin__pid_remove(config);
	/**关闭日志功能**/
	wangyonglin__log_close(config);
	wangyonglin__config_cleanup(config);
	return rc;
}