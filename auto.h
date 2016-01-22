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

/* $Id$ */

#ifndef PHP_AUTOSTRICT_H
#define PHP_AUTOSTRICT_H

extern zend_module_entry autostrict_module_entry;
#define phpext_autostrict_ptr &autostrict_module_entry

#define PHP_AUTOSTRICT_VERSION "1.0.1"
#define PHP_AUTOSTRICT_EXTNAME "autostrict"

#ifdef PHP_WIN32
#	define PHP_AUTOSTRICT_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_AUTOSTRICT_API __attribute__ ((visibility("default")))
#else
#	define PHP_AUTOSTRICT_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(autostrict)
	HashTable ignore;
	HashTable ignored;
ZEND_END_MODULE_GLOBALS(autostrict)

#ifdef ZTS
#define ASG(v) TSRMG(autostrict_globals_id, zend_autostrict_globals *, v)
#else
#define ASG(v) (autostrict_globals.v)
#endif

#endif	/* PHP_AUTOSTRICT_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
