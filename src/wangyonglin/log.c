#include <wangyonglin/config.h>
#include <wangyonglin/core.h>
typedef u_int wangyonglin_uint_t ;

static wangyonglin_string_t err_levels[] = {
	    wangyonglin_null_string,
	    wangyonglin_string("emerg"),
	    wangyonglin_string("alert"),
	    wangyonglin_string("crit"),
	    wangyonglin_string("error"),
	    wangyonglin_string("warn"),
	    wangyonglin_string("notice"),
	    wangyonglin_string("info"),
	    wangyonglin_string("debug")
	};



