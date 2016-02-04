# autostrict

This is a Zend module that makes it possible to use strict types in PHP 7
without ```define(strict_types=1)```.

This module only works from PHP >= 7.0.3 because of
[a bug in PHP](https://github.com/php/php-src/commit/bec0aec11691fa712750206d1b2cdd34bf6fc5a5).

## Build

Use something like the following to build ```autostrict```:

```
git clone https://github.com/krakjoe/autostrict
cd autostrict
phpize
./configure
make
sudo make install
```

## Load

Add the following to your configuration to enable the module:

```
zend_extension=autostrict.so
```

*```autostrict``` may also be loaded with ```extension``` directive, but it's correct to use ```zend_extension```*

## Configure

You can disable strictness on a per-file basis using the configuration directive ```autostrict.ignore```.

```autostrict.ignore``` should be a comma separated list of regex patterns.

*Note that, you may have to jump through hoops because regex and configuration don't really mix very well !*
