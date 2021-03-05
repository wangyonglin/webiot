#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
struct ccl_t config;
const struct ccl_pair_t *iter = NULL;
const char *conffile;
int wangyonglin_conf_setting(const char *filename)
{
  if (access(filename, F_OK) != 0)
  {
    fprintf(stderr, "\t%s %s\n", filename, strerror(errno));
    return -1;
  }
  config.comment_char = '#';
  config.sep_char = '=';
  config.str_char = '"';
  conffile = filename;
  return 0;
}

wangyonglin_string_t wangyonglin_conf_string(const char *lc_key)
{
  wangyonglin_string_t string_t = wangyonglin_null_string;
  ccl_parse(&config, conffile);
  const char *sval;
  if ((iter = ccl_iterate(&config)) != 0)
  {
    sval = ccl_get(&config, lc_key);
 
    wangyonglin_string_setting(&string_t, sval);
    return string_t;
  }
  ccl_release(&config);
  return string_t;
}

int wangyonglin_conf_int(const char *lc_key, int notfound)
{
  ccl_parse(&config, conffile);
  const char *sval=NULL;
  if ((iter = ccl_iterate(&config)) != 0)
  {
    sval = ccl_get(&config, lc_key);
    if(!sval)return notfound;
    return strtol(sval, NULL, 0);
  }
  ccl_release(&config);
  return notfound;
}