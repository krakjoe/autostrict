--TEST--
Test autostrict ignorance
--DESCRIPTION--
This test verifies that files are ignored in the appropriate way
--INI--
autostrict.ignore=~002\.php~
--FILE--
<?php
include(sprintf("%s/tests.inc", dirname(__FILE__)));

/**
* no strict types, argument coerced to correct type silently
**/
var_dump(included("100"));

/**
* tests.inc still has strict_types
**/
var_dump(caller("100"));
--EXPECTF--
int(100)

Fatal error: Uncaught TypeError: Argument 1 passed to local() must be of the type integer, string given, called in %s on line %d and defined in %s:%d
Stack trace:
#0 %s(%d): local('100')
#1 %s(%d): caller('100')
#2 {main}
  thrown in %s on line %d
