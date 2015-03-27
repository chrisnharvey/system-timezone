PHP_ARG_ENABLE(system_timezone, whether to enable system timezone extension,
[ --enable-system-timezone   Enable system timezone extension])
 
if test "$PHP_SYSTEM_TIMEZONE" = "yes"; then
  AC_DEFINE(HAVE_SYSTEM_TIMEZONE, 1, [Whether you have system timezone extension])
  PHP_NEW_EXTENSION(system_timezone, system_timezone.c, $ext_shared)
fi
