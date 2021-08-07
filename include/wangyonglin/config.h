#ifndef INCLUDE_WANGYONGLIN_CONFIG_H
#define INCLUDE_WANGYONGLIN_CONFIG_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>
typedef struct wangyonglin__config configify_t;
typedef struct wangyonglin__config wangyonglin__config_t;
typedef struct conf_s conf_t;
struct conf_s
{
  const char *pid_file;
  const char *log_file;
};
struct wangyonglin__config
{
  bool daemon;
  pid_t pid;
  char *pid_file;
  unsigned int log_dest;
  int log_facility;
  unsigned int log_type;
  bool log_timestamp;
  char *log_timestamp_format;
  char *log_file;
  FILE *log_fptr;
  char *user;
  char *group;
  wangyonglin_conf_table_t *conf;
};

configify_t* configify();
void configify_cleanup(configify_t *config);
int configify_loader(configify_t *config, const char *filename);

#endif