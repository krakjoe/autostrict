# autostrict

Automatic strict types in PHP 7

# How ?

```autostrict``` is a Zend Extension that can force all code to be strict, because yolo!

Note that due to [a little bug in PHP](https://github.com/php/php-src/commit/bec0aec11691fa712750206d1b2cdd34bf6fc5a5),
this module only works from PHP >= 7.0.3.

# Build

Use something like the following to build ```autostrict```:

```
git clone https://github.com/krakjoe/autostrict
cd autostrict
phpize
./configure
make
sudo make install
```

# Load

Add the following to your configuration to enable the osum:

```
zend_extension=autostrict.so
```

*```autostrict``` may also be loaded with ```extension``` directive, but it's correct to use ```zend_extension```*

# Configure

You can disable strictness on a per-file basis using the configuration directive ```autostrict.ignore```.

```autostrict.ignore``` should be a comma separated list of regex patterns.

*Note that, you may have to jump through hoops because regex and configuration don't really mix very well !*

If you load the module, autostrict is enabled by default.
To disable autostrict use the configuration directive ```autostrict.enable=0```.

