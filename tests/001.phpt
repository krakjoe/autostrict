--TEST--
Test autostrict ness
--DESCRIPTION--
This test verifies that by default all code is strict!
--FILE--
<?php
function local(int $int) {}

local("string");
--EXPECTF--
Fatal error: Uncaught TypeError: Argument 1 passed to local() must be of the type integer, string given, called in %s on line %d and defined in %s:%d
Stack trace:
#0 %s(%d): local('string')
#1 {main}
  thrown in %s on line %d
