#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
#include <ccl/ccl.h>
wangyonglin_conf_t * conf;
int wangyonglin_conf_open(const char * filename){

  conf = (wangyonglin_conf_t *)malloc(sizeof(wangyonglin_conf_t));
  if(conf!=NULL){
      memset(conf,0,sizeof(wangyonglin_conf_t));
      memcpy(conf->filename,filename,strlen(filename));
  }

	return 0;
}

void wangyonglin_conf_close(){
  if(conf!=NULL){
		free(conf);
	}
}
char * wangyonglin_conf_read(const char *key){
  if(conf==NULL){
    fprintf(stderr,"wangyonglin_conf_t conf not null");
    return NULL;
  }
    struct ccl_t 			config;
    const struct ccl_pair_t 	*iter;
    config.comment_char = '#';
    config.sep_char = '=';
    config.str_char = '"';
    ccl_parse(&config,conf->filename);
    while((iter = ccl_iterate(&config)) != 0) 
    {
      //printf("(%s,%s)\n", iter->key, iter->value);

      if(strcmp(iter->key,key)==0)
      {
        if(iter->value!=NULL)
        {
          return iter->value;
        }
         
      }
      
   }
     return "";
  ccl_release(&config);
}