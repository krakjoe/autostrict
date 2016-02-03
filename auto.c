/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 2016 The PHP Group                                     |
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

#include "php.h"
#include "zend_extensions.h"

#include "auto.h"

#include "ext/pcre/php_pcre.h"

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

ZEND_DECLARE_MODULE_GLOBALS(autostrict);

zend_module_entry autostrict_module_entry;

/* {{{ */
static inline int zend_auto_start(zend_extension *extension) {
	return zend_startup_module(&autostrict_module_entry);
}

static inline void zend_auto_strict(zend_op_array *op) {
	if ((NULL != op->filename) && 										/* There must be a filename */
		!(op->fn_flags & ZEND_ACC_STRICT_TYPES)) {						/* We can skip over ops where strict is already set */
		pcre_cache_entry *cache;
		zend_string *pattern;

		if (!zend_hash_num_elements(&ASG(ignore))) {					/* We can unconditionally set strict where ignore is not used */
			op->fn_flags |= ZEND_ACC_STRICT_TYPES;
			return;
		}

		if (zend_hash_exists(&ASG(ignored), op->filename)) {			/* We cache results of previous attempts to match to try to avoid next block */
			return;
		}
		
		ZEND_HASH_FOREACH_STR_KEY_PTR(&ASG(ignore), pattern, cache) {	/* Nothing for it ... iterate, we must ... */
			zval result,
				 subs;

			ZVAL_UNDEF(&result);
			ZVAL_UNDEF(&subs);

			php_pcre_match_impl(cache, ZSTR_VAL(op->filename), ZSTR_LEN(op->filename), &result, &subs, 0, 0, 0, 0);

			if (zend_is_true(&result)) {
				zend_hash_add_empty_element(
					&ASG(ignored), op->filename);						/* Avoid running this match again */
				zval_ptr_dtor(&subs);
				return;
			}

			zval_ptr_dtor(&subs);
		} ZEND_HASH_FOREACH_END();

		op->fn_flags |= ZEND_ACC_STRICT_TYPES;
	}
}

ZEND_EXT_API zend_extension zend_extension_entry = {
	PHP_AUTOSTRICT_EXTNAME,
	PHP_AUTOSTRICT_VERSION,
	"Joe Watkins <krakjoe@php.net>",
	"https://github.com/krakjoe/autostrict",
	"Copyright (c) 2016",
	zend_auto_start,	/* startup_func_t */
	NULL,           	/* shutdown_func_t */
	NULL,               /* activate_func_t */
	NULL,               /* deactivate_func_t */
	NULL,           	/* message_handler_func_t */
	zend_auto_strict,	/* op_array_handler_func_t */
	NULL, 				/* statement_handler_func_t */
	NULL,             	/* fcall_begin_handler_func_t */
	NULL,           	/* fcall_end_handler_func_t */
	NULL,      			/* op_array_ctor_func_t */
	NULL,      			/* op_array_dtor_func_t */
	STANDARD_ZEND_EXTENSION_PROPERTIES
}; /* }}} */

/* {{{ */
static PHP_INI_MH(OnUpdateIgnore) {
	zend_string *sep = zend_string_init(ZEND_STRL(","), 0);
	zval ignore, *value;
	zend_string *key;
	
	array_init(&ignore);
	php_explode(sep, new_value, &ignore);

	if (!ASG(ignore).nTableSize) {
		zend_hash_init(&ASG(ignore), 8, NULL, NULL, 1);
	}

	ZEND_HASH_FOREACH_VAL(Z_ARRVAL(ignore), value) {
		pcre_cache_entry *re;

		if (Z_TYPE_P(value) != IS_STRING || 
			!Z_STRLEN_P(value) || 
			zend_hash_exists(&ASG(ignore), key) ||
			!(re = pcre_get_compiled_regex_cache(Z_STR_P(value))))
			continue;

		zend_hash_update_ptr(&ASG(ignore), Z_STR_P(value), re);
	} ZEND_HASH_FOREACH_END();

	zval_ptr_dtor(&ignore);
}

PHP_INI_BEGIN()
	PHP_INI_ENTRY("autostrict.ignore", "", PHP_INI_SYSTEM | PHP_INI_PERDIR, OnUpdateIgnore)
PHP_INI_END()

static inline php_autostrict_globals_ctor(zend_autostrict_globals *asg) {
	memset(asg, 0, 
		sizeof(zend_autostrict_globals));
}

static PHP_MINIT_FUNCTION(autostrict) {
	if (!zend_get_extension("autostrict")) {
		zend_extension_entry.startup = NULL;
		zend_register_extension(
			&zend_extension_entry, NULL);
	}

	ZEND_INIT_MODULE_GLOBALS(autostrict, php_autostrict_globals_ctor, NULL);

	CG(compiler_options) |= ZEND_COMPILE_HANDLE_OP_ARRAY;

	REGISTER_INI_ENTRIES();

	return SUCCESS;
}

static PHP_MSHUTDOWN_FUNCTION(autostrict) {
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}

static PHP_RINIT_FUNCTION(autostrict) {
#if defined(ZTS) && defined(COMPILE_DL_AUTOSTRICT)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	zend_hash_init(&ASG(ignored), 8, NULL, NULL, 0);

	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(autostrict) {
	zend_hash_destroy(&ASG(ignored));

	return SUCCESS;
}

static PHP_MINFO_FUNCTION(autostrict) {
	php_info_print_table_start();
	php_info_print_table_header(2, "autostrict support", "enabled");
	php_info_print_table_end();
}

zend_module_entry autostrict_module_entry = {
	STANDARD_MODULE_HEADER,
	PHP_AUTOSTRICT_EXTNAME,
	NULL,
	PHP_MINIT(autostrict),
	PHP_MSHUTDOWN(autostrict),
	PHP_RINIT(autostrict),
	PHP_RSHUTDOWN(autostrict),
	PHP_MINFO(autostrict),
	PHP_AUTOSTRICT_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_AUTOSTRICT
ZEND_GET_MODULE(autostrict)
#endif
#endif
