--TEST--
Test autostrict ignorance more
--DESCRIPTION--
This test verifies that files are ignored in the appropriate way
--INI--
autostrict.ignore=~003\.php~,~tests\.inc~
--FILE--
<?php
include(sprintf("%s/tests.inc", dirname(__FILE__)));

/**
* no strict types, argument coerced to correct type silently
**/
var_dump(included("100"));

/**
* no strict types in tests.inc either
**/
var_dump(caller("100"));
--EXPECTF--
int(100)
int(100)
