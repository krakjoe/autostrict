PHP_ARG_ENABLE(autostrict, whether to enable automatic strict types support,
[  --enable-autostrict   Enable automatic strict types support])

if test "$PHP_AUTOSTRICT" != "no"; then
  PHP_NEW_EXTENSION(autostrict, auto.c, $ext_shared)
fi
