#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

const char *__ininame;
wangyonglin_rc_t rc;
int wangyonglin_conf_init(const char *ininame)
{
  if (access(ininame, F_OK) != 0)
  {
    fprintf(stderr, "\t%s %s\n", ininame, strerror(errno));
    rc = error;
    return wangyonglin_result_error;
  }
  __ininame = ininame;
  return wangyonglin_result_success;
}
int wangyonglin_conf_get(void *dest, const char *key, wangyonglin_type_t type)
{
  int ret;

  if (rc != ok)
  {
    fprintf(stderr, "\tconf file is not empty!\n");
    return wangyonglin_result_error;
  }
  dictionary *ini;
  ini = iniparser_load(__ininame);
  if (ini == NULL)
  {
    fprintf(stderr, "cannot parse file: %s\n", __ininame);
    return wangyonglin_result_error;
  }
  switch (type)
  {
  case wangyonglin_type_string:
    strcpy(dest, iniparser_getstring(ini, key, "null"));
    break;
  case wangyonglin_type_int:
    ret = iniparser_getint(ini, key, 0);
    memcpy(dest, &ret, sizeof(int));
    break;
  default:
    fprintf(stderr, "\ttype error: %s\n", key);
    break;
  }

  iniparser_freedict(ini);
  return wangyonglin_result_success;
}