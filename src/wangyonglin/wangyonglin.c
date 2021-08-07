#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
configify_t *config = NULL;
int main(int argc, char *argv[])
{
	int rc;
	config = configify();
	rc = configify_loader(config, "/usr/local/wangyonglin/conf/wangyonglin.conf");
	if (rc != ERR_SUCCESS)
		return rc;
	/**开启日志功能**/
	logify_init(config);
	/**开启守护进程**/
	rc = daemonify(config);
	if (rc != ERR_SUCCESS)
		return rc;
	/**测试文件 pid **/
	rc = pidify_test(config);
	if (rc != ERR_SUCCESS)
		return rc;
	/**写入文件 pid**/
	rc = pidify_create(config);
	if (rc != ERR_SUCCESS)
		return rc;

	rc = application(config);
	if (rc != ERR_SUCCESS)
		return rc;
	/**删除文件	pid**/
	pidify_remove(config);
	/**关闭日志功能**/
	logify_close(config);
	configify_cleanup(config);
	return rc;
}