<?php
function included(int $int) { return $int; }

function local(int $int) { 
	return $int;
}

function caller($int) {
	return local($int);
} 
?>
