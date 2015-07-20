<?php

// ini_set('display_errors','on');
// error_reporting(E_ALL);

// Implements hook_drush_command
function spnetsync_drush_command() {
	$items = array();

	$items['spnetsync'] = array(
		'description' => "SPNET sync",
		'aliases'     => array('spnetsync'),
        );

	return $items;
}

function drush_spnetsync_spnetsync() {
	require_once dirname(__FILE__) . '/spnetsync.inc';
	return spnetsync_sync();
}
