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
function spnetsync_rules_action_info() {
  $actions = array();

  $actions['spnetsync_sync_user'] = array(
    'label' => t('Sync local user data with civicrm data.'),
    'parameter' => array(
      'user' => array(
        'type' => 'user',
        'label' => t('User')
      ),
    ),
  );

  $actions['spnetsync_sync_all_users'] = array(
    'label' => t('Sync all local users data with civicrm data.'),
  );

  return $actions;
}

function spnetsync_sync_user($user) {
  spnetsync_sync_roles($user);
}

function spnetsync_sync_all_users() {
  spnetsync_sync_roles();
}

