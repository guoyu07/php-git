/*
 * PHP Libgit2 Extension
 *
 * https://github.com/libgit2/php-git
 *
 * Copyright 2014 Shuhei Tanuma.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef PHP_GIT2_PRIV_H
#define PHP_GIT2_PRIV_H

extern int git2_resource_handle;

#if PHP_VERSION_ID>=50399
#define PHP_GIT2_LIST_INSERT(type, handle) zend_list_insert(type, handle TSRMLS_CC)
#else
#define PHP_GIT2_LIST_INSERT(type, handle) zend_list_insert(type, handle)
#endif

#define PHP_GIT2_V(git2, type) git2->v.type
#define GIT2_RVAL_P(git2) git2->resource_id
#define GIT2_SHOULD_FREE(git2) git2->should_free_v

#ifdef ZTS
#define GIT2_TSRMLS_SET(target) void ***tsrm_ls = target;
#define GIT2_TSRMLS_DECL void ***tsrm_ls;
#define GIT2_TSRMLS_SET2(target, value) target->tsrm_ls = value;
#else
#define GIT2_TSRMLS_SET(target)
#define GIT2_TSRMLS_SET2(target, value)
#define GIT2_TSRMLS_DECL
#endif

#define PHP_GIT2_MAKE_RESOURCE(val) \
do {\
	val = (php_git2_t *)emalloc(sizeof(php_git2_t));\
	if (!val) {\
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "emalloc failed");\
		RETURN_FALSE;\
	}\
	val->should_free_v = 0;\
	val->type = 0;\
	val->mutable = 0;\
} while (0);\


#define PHP_GIT2_MAKE_RESOURCE_NOCHECK(val) \
do {\
	val = (php_git2_t *)emalloc(sizeof(php_git2_t));\
	val->should_free_v = 0;\
	val->type = 0;\
	val->mutable = 0;\
} while (0);\

#define GIT2_OID_HEXSIZE (GIT_OID_HEXSZ+1)

typedef struct php_git2_cb_t {
	zval *payload;
	zend_fcall_info *fci;
	zend_fcall_info_cache *fcc;
	GIT2_TSRMLS_DECL
} php_git2_cb_t;

#include "helper.h"

#endif