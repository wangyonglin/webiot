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
    return -1;
  }
  __ininame = ininame;
  return 0;
}

char *wangyonglin_conf_string(char * dest,const char *key)
{
  dictionary *dict;

  dict = iniparser_load(__ininame);
  if (dict == NULL)
  {
    fprintf(stderr, "cannot parse file: %s\n", __ininame);
    return NULL;
  }

  strcpy(dest, iniparser_getstring(dict, key, ""));
  iniparser_freedict(dict);
  return dest;
}
int wangyonglin_conf_number(const char *key)
{
  int rc;
  dictionary *dict;
  dict = iniparser_load(__ininame);
  if (dict == NULL)
  {
    fprintf(stderr, "cannot parse file: %s\n", __ininame);
    return -1;
  }

  rc = iniparser_getint(dict, key, 41);

  iniparser_freedict(dict);
  return rc;
}