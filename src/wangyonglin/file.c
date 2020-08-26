#include <wangyonglin/config.h>
#include <wangyonglin/core.h>

  
int wangyonglin_file_fopen(char *filename,FILE *fd)
{

		if( (fd=fopen(filename,"a+") == NULL ))
        {
			fprintf(stderr,"Fail to open file!\n");
			return WANGYONGLIN_ERROR;
		}
        return WANGYONGLIN_OK;
}
void wangyonglin_file_fclose(FILE *fd)
{

	if(fd!=NULL){
		fclose(fd);
	}
}
int wangyonglin_file_exists(char *filename)
{
    return (access(filename, 0) == 0);
}

int wangyonglin_file_open(char *filename){
    int fd;
       if((fd=open(filename,O_WRONLY|O_CREAT))==-1)
    {
        fprintf(stderr,"open %s error! \n",filename);
        return WANGYONGLIN_ERROR;
    }
     return fd;
}

