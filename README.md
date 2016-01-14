# autostrict

Automatic strict types in PHP 7

# How ?

```autostrict``` is a Zend Extension that forces all op arrays to be strict because yolo

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
