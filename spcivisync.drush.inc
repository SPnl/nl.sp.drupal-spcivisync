<?php

// ini_set('display_errors','on');
// error_reporting(E_ALL);

// Implements hook_drush_command
function spcivisync_drush_command() {
	$items = array();

	$items['spcivisync'] = array(
		'description' => "SP CiviCRM synchronizatie voor alle gebruikers",
		'aliases'     => array('spcs'),
        );

	return $items;
}

function drush_spcivisync() {
  spcivisync_sync_users(array(), FALSE, TRUE);
  return;
}
