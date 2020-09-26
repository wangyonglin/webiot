#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

struct tm *__timenow();
int __fileexists(char *filename);
wangyonglin_log_t __log;

void wangyonglin_log_conf(wangyonglin_log_t *log)
{
	wangyonglin_conf_get(log->access_log, "logs:access", wangyonglin_type_string);
	wangyonglin_conf_get(log->error_log, "logs:error", wangyonglin_type_string);
}

void wangyonglin_log_info(const char *format, ...)
{
	if (__log.access_log == NULL && __log.access_log == "")
	{
		fprintf(stderr, "_log_t->access_log : not null \n");
		exit(-1);
	}

	struct tm *t;

	if (__fileexists(__log.access_log) == 0)
	{
		fprintf(stderr, "it not exists : %s \n", __log.access_log);
		exit(-1);
	}
	else
	{
		int ret = open(__log.access_log, O_RDWR | O_CREAT, 0640);
		if (ret != -1)
		{
			close(ret);
		}
	}

	FILE *fd = fopen(__log.access_log, "a");
	if (fd == NULL)
	{
		fprintf(stderr, "it open fait : %s \n", __log.access_log);
		exit(-1);
	}
	t = __timenow();
	va_list args;
	va_start(args, format);

	fprintf(fd, "%04d-%02d-%02d %02d:%02d:%02d\t", t->tm_year, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	vfprintf(fd, format, args);
	fputc('\r', fd);
	fputc('\n', fd);
	fflush(fd);
	va_end(args);
	fclose(fd);
}
int wangyonglin_log_init(wangyonglin_log_t *log)
{
	__log = *log;
	return -1;
}
void wangyonglin_log_error(wangyonglin_log_levels_t level, const char *format, ...)
{
	if(access(__log.error_log,F_OK)!=0){
		fprintf(stderr,"\tlog error %s %s \n",__log.error_log,strerror(errno));
		return;
	}

	struct tm *t;
	char err_levels[16];
	switch (level)
	{
	case LOG_ERROR:
		strcpy(err_levels, "ERROR");

		break;
	case LOG_DEBUG:
		strcpy(err_levels, "DEBUG");
		break;
	case LOG_EMERG:
		strcpy(err_levels, "EMERG");
		break;
	case LOG_WARN:
		strcpy(err_levels, "WARN");
		break;
	default:
		strcpy(err_levels, "INFO");
		break;
	}

	if (__fileexists(__log.error_log) == 0)
	{
		fprintf(stderr, "it not exists : %s \n", __log.error_log);
		exit(-1);
	}
	else
	{
		int ret = open(__log.error_log, O_RDWR | O_CREAT, 0640);
		if (ret != -1)
		{
			close(ret);
		}
	}

	FILE *fd = fopen(__log.error_log, "a+");
	if (fd == NULL)
	{
		fprintf(stderr, "it open fait : %s \n", __log.error_log);
		exit(-1);
	}
	t = __timenow();
	va_list args;
	va_start(args, format);

	fprintf(fd, "%04d-%02d-%02d %02d:%02d:%02d\t", t->tm_year, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	fprintf(fd,"%s\t", err_levels);
	vfprintf(fd, format, args);
	fputc('\r', fd);
	fputc('\n', fd);
	fflush(fd);
	va_end(args);
	fclose(fd);
}
struct tm *__timenow()
{
	time_t time_seconds = time(0);
	struct tm *now_time = localtime(&time_seconds);
	now_time->tm_year += 1900;
	now_time->tm_mon += 1;
	return now_time;
}
int __fileexists(char *filename)
{
	return (access(filename, 0) == 0);
}