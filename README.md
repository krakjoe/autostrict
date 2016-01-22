# autostrict

Automatic strict types in PHP 7

# How ?

```autostrict``` is a Zend Extension that can force all code to be strict, because yolo!

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
