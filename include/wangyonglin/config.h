#ifndef INCLUDE_WANGYONGLIN_CONFIG_H
#define INCLUDE_WANGYONGLIN_CONFIG_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>


typedef struct
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
  wangyonglin_conf_table_t *boot;
} configify_t;

configify_t *configify();
void configify_cleanup(configify_t *config);
int configify_loader(configify_t *config, const char *filename);

#endif