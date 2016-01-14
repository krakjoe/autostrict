/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: krakjoe <krakjoe@php.net>                                    |
  +----------------------------------------------------------------------+
*/
#ifndef HAVE_AUTO
#define HAVE_AUTO

#include "zend.h"
#include "zend_extensions.h"

#ifdef ZTS
#	include "TSRM.h"
#endif

#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

#ifndef ZEND_EXT_API
#define ZEND_EXT_API    ZEND_DLEXPORT
#endif
ZEND_EXTENSION();

static inline int php_auto_start(zend_extension *extension) {
	CG(compiler_options) |= ZEND_COMPILE_HANDLE_OP_ARRAY;

	return SUCCESS;
}

static inline void php_auto_strict(zend_op_array *op) {
	op->fn_flags |= ZEND_ACC_STRICT_TYPES;
}

ZEND_EXT_API zend_extension zend_extension_entry = {
	"autostrict",
	"1.0.0",
	"Joe Watkins <krakjoe@php.net>",
	"https://github.com/krakjoe/autostrict",
	"Copyright (c) 2015",
	php_auto_start,		/* startup_func_t */
	NULL,           	/* shutdown_func_t */
	NULL,               /* activate_func_t */
	NULL,               /* deactivate_func_t */
	NULL,           	/* message_handler_func_t */
	php_auto_strict,	/* op_array_handler_func_t */
	NULL, 				/* statement_handler_func_t */
	NULL,             	/* fcall_begin_handler_func_t */
	NULL,           	/* fcall_end_handler_func_t */
	NULL,      			/* op_array_ctor_func_t */
	NULL,      			/* op_array_dtor_func_t */
	STANDARD_ZEND_EXTENSION_PROPERTIES
};
#endif
