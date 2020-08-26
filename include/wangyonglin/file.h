#ifndef _WANGYONGLIN_FILE_H_INCLUDE_
#define _WANGYONGLIN_FILE_H_INCLUDE_

#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

#define  wangyonglin_fd_t   FILE


int wangyonglin_file_fopen(char *filename,FILE *fd);
void wangyonglin_file_fclose(FILE *fd);
void wangyonglin_file_flocaltime(FILE *fd,struct tm * t);
int wangyonglin_file_exists(char *filename);
int wangyonglin_file_open(char *filename);
#endif /**_WANGYONGLIN_FILE_H_INCLUDE_**/
