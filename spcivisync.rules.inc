<?php
/**
 * @file
 * Rules integration.
 */

/**
 * Implements hook_rules_action_info().
 *
 * Provides an action sync civicrm data with local user. 
 */
function spcivisync_rules_action_info() {
  $actions = array();

  $actions['spcivisync_sync_user'] = array(
    'label' => t('Sync local user data with civicrm data.'),
    'parameter' => array(
      'user' => array(
        'type' => 'user',
        'label' => t('User')
      ),
    ),
  );

  $actions['spcivisync_sync_all_users'] = array(
    'label' => t('Sync all local users data with civicrm data.'),
  );

  return $actions;
}

function spcivisync_sync_user($account) {
  spcivisync_sync_users(array($account));
}

function spcivisync_sync_all_users() {
  $users = spcivisync_get_users();
  spcivisync_sync_roles($users);
  // Possibly new user, so update.
  $users = spcivisync_get_users();
  spcivisync_sync_users($users);
}
