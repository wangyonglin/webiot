#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
struct wangyonglin__config *config = NULL;
int main(int argc, char *argv[])
{
	int rc;
	config = config__new();
	rc = config__load(config, argc, argv);
	if (rc != ERR_SUCCESS)
		return rc;
	/**开启日志功能**/
	log__init(config);
	/**开启守护进程**/
	rc = wangyonglin__daemon(config);
	if (rc != ERR_SUCCESS)
		return rc;
	/**测试文件 pid **/
	rc = pid__test(config);
	if (rc != ERR_SUCCESS)
		return rc;
	/**写入文件 pid**/
	rc = pid__create(config);
	if (rc != ERR_SUCCESS)
		return rc;

	application(config);
	/**删除文件	pid**/
	pid__remove(config);
	/**关闭日志功能**/
	log__close(config);
	config__cleanup(config);
	return rc;
}