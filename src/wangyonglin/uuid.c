#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

struct globle
{
	int global_int : 12;
	uint64_t last_stamp;
	int workid;
	int seqid;
};

void set_workid(int workid);
pid_t gettid(void);
uint64_t get_curr_ms();
uint64_t wait_next_ms(uint64_t lastStamp);
int atomic_incr(int id);



struct globle g_info;
#define   sequenceMask  (-1L ^ (-1L << 12L))

pid_t gettid( void )
{
	return syscall( __NR_gettid );
}
uint64_t get_curr_ms()
{
	struct timeval time_now;
	gettimeofday(&time_now,NULL);
	uint64_t ms_time =time_now.tv_sec*1000+time_now.tv_usec/1000;
	return ms_time;
}

uint64_t wait_next_ms(uint64_t lastStamp)
{
	uint64_t cur = 0;
	do {
		cur = get_curr_ms();
	} while (cur <= lastStamp);
	return cur;
}
int atomic_incr(int id)
{
	__sync_add_and_fetch( &id, 1 );
	return id;
}
uint64_t wangyonglin__uuid(struct wangyonglin__config * config,int workid)
{
    g_info.workid = workid;
	uint64_t  uniqueId=0;
	uint64_t nowtime = get_curr_ms();
	uniqueId = nowtime<<22;
	uniqueId |=(g_info.workid&0x3ff)<<12;

	if (nowtime <g_info.last_stamp)
	{
		log__printf(config,LOG_ERR,"make uuid faile!");
		exit(EXIT_FAILURE);
	}
	if (nowtime == g_info.last_stamp)
	{
		g_info.seqid = atomic_incr(g_info.seqid)& sequenceMask;
		if (g_info.seqid ==0)
		{
			nowtime = wait_next_ms(g_info.last_stamp);
		}
	}
	else
	{
		g_info.seqid  = 0;
	}
	g_info.last_stamp = nowtime;
	uniqueId |=g_info.seqid;
	return uniqueId;
}
