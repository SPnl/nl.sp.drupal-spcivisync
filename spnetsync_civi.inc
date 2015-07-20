<?php

function spnetsync_sync() {

  set_time_limit(0);

  $civiapi     = spciviapi_get_api();

  _spnetsync_output_start('Sync: ');

  // Get tags and custom field id
  $civiapi->Tag->Getsingle(array(
    'name' => 'Erkend',
  ));
  $tag_erkend = $civiapi->result()->id;

  $civiapi->Tag->Getsingle(array(
    'name' => 'In Oprichting',
  ));
  $tag_io = $civiapi->result()->id;

  $civiapi->CustomField->Getsingle(array(
    'name' => 'Provincie',
    'return' => 'id',
  ));
  $cf_prov = 'custom_' . $civiapi->result()->id;

  // Get import data.
  $civiapi->Contact->Get(array(
    'contact_type'          => 'Organization',
    'contact_sub_type'      => 'SP_afdeling',
    'tag'                   => implode(',',array($tag_io, $tag_erkend)),
    'option.limit'          => 9999,
    'return'                => implode(',',array('contact_id','display_name',$cf_prov)),
  ));
  $afdelingen = $civiapi->result()->values;
  dpm($afdelingen);

  // Get relationships
  $civiapi->Relationship->Get(array(
    'version' => 3,
    'sequential' => 1,
  ));
  $relationship = $civiapi->result()->values;
  dpm($relationship);

  // Get Relionship types.
  $civiapi->RelationshipType->Get(array(
  ));
  $relationshipType = $civiapi->result()->values;
  dpm($relationshipType);

  return '';
}

function _spnetsync_output_text($text) {
  if (function_exists('drush_print'))
    drush_print($text);
  elseif (function_exists('dsm'))

    echo($text . "\n");
}

function _spnetsync_output_start($label) {
  if (function_exists('drush_print'))
    drush_print($label . ' ', 0, null, false);
  else
    echo($label . ' ');
}

function _spnetsync_output_progress() {
  if (function_exists('drush_print'))
    drush_print('.', 0, null, false);
}

function _spnetsync_output_finish() {
  if (function_exists('drush_print'))
    drush_print('', 0, null, true);
}
