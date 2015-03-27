#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include <zend_API.h>
 
#define PHP_SYSTEM_TIMEZONE_VERSION "1.0"
#define PHP_SYSTEM_TIMEZONE_EXTNAME "system_timezone"
 
extern zend_module_entry system_timezone_module_entry;
#define phpext_system_timezone_ptr &system_timezone_module_entry
 
/* declaration of a custom system_timezone() */
PHP_FUNCTION(system_timezone);
 
/* list of custom PHP functions provided by this extension
   set {NULL, NULL, NULL} as the last record to mark the end of list
*/
static zend_function_entry timezone_functions[] = {
    PHP_FE(system_timezone, NULL)
    {NULL, NULL, NULL}
};
 
/* the following code creates an entry for the module and registers it with Zend. */
zend_module_entry system_timezone_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_SYSTEM_TIMEZONE_EXTNAME,
    timezone_functions,
    NULL, /* name of the MINIT function or NULL if not applicable */
    NULL, /* name of the MSHUTDOWN function or NULL if not applicable */
    NULL, /* name of the RINIT function or NULL if not applicable */
    NULL, /* name of the RSHUTDOWN function or NULL if not applicable */
    NULL, /* name of the MINFO function or NULL if not applicable */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_SYSTEM_TIMEZONE_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};
 
ZEND_GET_MODULE(system_timezone)
 
/* implementation of a custom system_timezone() */
PHP_FUNCTION(system_timezone)
{
    time_t t = time(NULL);
    struct tm lt = {0};

    /* Get the localtime */
    localtime_r(&t, &lt);

    /* Setup args to be passed to timezone_name_from_abbr */
    zval *args[3];
    MAKE_STD_ZVAL(args[0]);
    ZVAL_STRING(args[0], lt.tm_zone, 1); 
    
    MAKE_STD_ZVAL(args[1]);
    ZVAL_LONG(args[1], lt.tm_gmtoff);

    MAKE_STD_ZVAL(args[2]);
    ZVAL_LONG(args[2], lt.tm_isdst);

    /* Setup timezone_name_from_abbr function name */
    zval *fname;
    MAKE_STD_ZVAL(fname);
    ZVAL_STRING(fname, "timezone_name_from_abbr", 1);

    /* Setup timezone_name_from_abbr return value */
    zval *retval = NULL;
    MAKE_STD_ZVAL(retval);

    /* Call the timezone_name_from_abbr function */
    if (call_user_function(EG(function_table), NULL, fname, retval, 1, args TSRMLS_CC) == SUCCESS) {
        /* Return value from the timezone_name_from_abbr function */
        RETURN_ZVAL(retval, 1, 0);
    }
}
