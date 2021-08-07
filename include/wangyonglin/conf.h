/*
  MIT License

  Copyright (c) 2017 - 2019 CK Tan
  https://github.com/cktan/tomlc99

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef INCLUDE_WANGYONGLIN_CONF_H
#define INCLUDE_WANGYONGLIN_CONF_H
#include <wangyonglin/linux.h>
#include <wangyonglin/wangyonglin.h>

#ifdef __cplusplus
#define WANGYONGLIN_EXTERN extern "C"
#else
#define WANGYONGLIN_EXTERN extern
#endif

typedef struct wangyonglin_conf_timestamp_t wangyonglin_conf_timestamp_t;
typedef struct wangyonglin_conf_table_t wangyonglin_conf_table_t;
typedef struct wangyonglin_conf_array_t wangyonglin_conf_array_t;
typedef struct wangyonglin_conf_datum_t wangyonglin_conf_datum_t;

/* Parse a file. Return a table on success, or 0 otherwise.
 * Caller must wangyonglin_free(the-return-value) after use.
 */
WANGYONGLIN_EXTERN wangyonglin_conf_table_t* confify_file(FILE* fp,
										  char* errbuf,
										  int errbufsz);

/* Parse a string containing the full config.
 * Return a table on success, or 0 otherwise.
 * Caller must wangyonglin_conf_free(the-return-value) after use.
 */
WANGYONGLIN_EXTERN wangyonglin_conf_table_t* confify_parse(char* conf, /* NUL terminated, please. */
									 char* errbuf,
									 int errbufsz);

/* Free the table returned by wangyonglin_conf_parse() or wangyonglin_conf_parse_file(). Once
 * this function is called, any handles accessed through this tab
 * directly or indirectly are no longer valid.
 */
WANGYONGLIN_EXTERN void confify_free(wangyonglin_conf_table_t* tab);


/* Timestamp types. The year, month, day, hour, minute, second, z
 * fields may be NULL if they are not relevant. e.g. In a DATE
 * type, the hour, minute, second and z fields will be NULLs.
 */
struct wangyonglin_conf_timestamp_t {
	struct { /* internal. do not use. */
		int year, month, day;
		int hour, minute, second, millisec;
		char z[10];
	} __buffer;
	int *year, *month, *day;
	int *hour, *minute, *second, *millisec;
	char* z;
};


/*-----------------------------------------------------------------
 *  Enhanced access methods
 */
struct wangyonglin_conf_datum_t {
	int ok;
	union {
		wangyonglin_conf_timestamp_t* ts; /* ts must be freed after use */
		char*   s; /* string value. s must be freed after use */
		int     b; /* bool value */
		int64_t i; /* int value */
		double  d; /* double value */
	} u;
};

/* on arrays: */
/* ... retrieve size of array. */
WANGYONGLIN_EXTERN int wangyonglin_conf_array_nelem(const wangyonglin_conf_array_t* arr);
/* ... retrieve values using index. */
WANGYONGLIN_EXTERN wangyonglin_conf_datum_t wangyonglin_conf_string_at(const wangyonglin_conf_array_t* arr, int idx);
WANGYONGLIN_EXTERN wangyonglin_conf_datum_t wangyonglin_conf_bool_at(const wangyonglin_conf_array_t* arr, int idx);
WANGYONGLIN_EXTERN wangyonglin_conf_datum_t wangyonglin_conf_int_at(const wangyonglin_conf_array_t* arr, int idx);
WANGYONGLIN_EXTERN wangyonglin_conf_datum_t wangyonglin_conf_double_at(const wangyonglin_conf_array_t* arr, int idx);
WANGYONGLIN_EXTERN wangyonglin_conf_datum_t wangyonglin_conf_timestamp_at(const wangyonglin_conf_array_t* arr, int idx);
/* ... retrieve array or table using index. */
WANGYONGLIN_EXTERN wangyonglin_conf_array_t* wangyonglin_conf_array_at(const wangyonglin_conf_array_t* arr, int idx);
WANGYONGLIN_EXTERN wangyonglin_conf_table_t* wangyonglin_conf_table_at(const wangyonglin_conf_array_t* arr, int idx);

/* on tables: */
/* ... retrieve the key in table at keyidx. Return 0 if out of range. */
WANGYONGLIN_EXTERN const char* wangyonglin_conf_key_in(const wangyonglin_conf_table_t* tab, int keyidx);
/* ... retrieve values using key. */
WANGYONGLIN_EXTERN wangyonglin_conf_datum_t wangyonglin_conf_string_in(const wangyonglin_conf_table_t* arr, const char* key);
WANGYONGLIN_EXTERN wangyonglin_conf_datum_t wangyonglin_conf_bool_in(const wangyonglin_conf_table_t* arr, const char* key);
WANGYONGLIN_EXTERN wangyonglin_conf_datum_t wangyonglin_conf_int_in(const wangyonglin_conf_table_t* arr, const char* key);
WANGYONGLIN_EXTERN wangyonglin_conf_datum_t wangyonglin_conf_double_in(const wangyonglin_conf_table_t* arr, const char* key);
WANGYONGLIN_EXTERN wangyonglin_conf_datum_t wangyonglin_conf_timestamp_in(const wangyonglin_conf_table_t* arr, const char* key);
/* .. retrieve array or table using key. */
WANGYONGLIN_EXTERN wangyonglin_conf_array_t* wangyonglin_conf_array_in(const wangyonglin_conf_table_t* tab,
										const char* key);
WANGYONGLIN_EXTERN wangyonglin_conf_table_t* wangyonglin_conf_table_in(const wangyonglin_conf_table_t* tab,
										const char* key);

/*-----------------------------------------------------------------
 * lesser used
 */
/* Return the array kind: 't'able, 'a'rray, 'v'alue, 'm'ixed */
WANGYONGLIN_EXTERN char wangyonglin_conf_array_kind(const wangyonglin_conf_array_t* arr);

/* For array kind 'v'alue, return the type of values
   i:int, d:double, b:bool, s:string, t:time, D:date, T:timestamp, 'm'ixed
   0 if unknown
*/
WANGYONGLIN_EXTERN char wangyonglin_conf_array_type(const wangyonglin_conf_array_t* arr);

/* Return the key of an array */
WANGYONGLIN_EXTERN const char* wangyonglin_conf_array_key(const wangyonglin_conf_array_t* arr);

/* Return the number of key-values in a table */
WANGYONGLIN_EXTERN int wangyonglin_conf_table_nkval(const wangyonglin_conf_table_t* tab);

/* Return the number of arrays in a table */
WANGYONGLIN_EXTERN int wangyonglin_conf_table_narr(const wangyonglin_conf_table_t* tab);

/* Return the number of sub-tables in a table */
WANGYONGLIN_EXTERN int wangyonglin_conf_table_ntab(const wangyonglin_conf_table_t* tab);

/* Return the key of a table*/
WANGYONGLIN_EXTERN const char* wangyonglin_conf_table_key(const wangyonglin_conf_table_t* tab);

/*--------------------------------------------------------------
 * misc
 */
WANGYONGLIN_EXTERN int wangyonglin_conf_utf8_to_ucs(const char* orig, int len, int64_t* ret);
WANGYONGLIN_EXTERN int wangyonglin_conf_ucs_to_utf8(int64_t code, char buf[6]);
WANGYONGLIN_EXTERN void wangyonglin_conf_set_memutil(void* (*xxmalloc)(size_t),
								  void	(*xxfree)(void*));


/*--------------------------------------------------------------
 *  deprecated
 */
/* A raw value, must be processed by wangyonglin_conf_rto* before using. */
typedef const char* wangyonglin_conf_raw_t;
WANGYONGLIN_EXTERN wangyonglin_conf_raw_t wangyonglin_conf_raw_in(const wangyonglin_conf_table_t* tab, const char* key);
WANGYONGLIN_EXTERN wangyonglin_conf_raw_t wangyonglin_conf_raw_at(const wangyonglin_conf_array_t* arr, int idx);
WANGYONGLIN_EXTERN int wangyonglin_conf_rtos(wangyonglin_conf_raw_t s, char** ret);
WANGYONGLIN_EXTERN int wangyonglin_conf_rtob(wangyonglin_conf_raw_t s, int* ret);
WANGYONGLIN_EXTERN int wangyonglin_conf_rtoi(wangyonglin_conf_raw_t s, int64_t* ret);
WANGYONGLIN_EXTERN int wangyonglin_conf_rtod(wangyonglin_conf_raw_t s, double* ret);
WANGYONGLIN_EXTERN int wangyonglin_conf_rtod_ex(wangyonglin_conf_raw_t s, double* ret, char* buf, int buflen);
WANGYONGLIN_EXTERN int wangyonglin_conf_rtots(wangyonglin_conf_raw_t s, wangyonglin_conf_timestamp_t* ret);



#endif /**INCLUDE_WANGYONGLIN_CONF_H**/