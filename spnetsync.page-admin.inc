<?php

function spnetsync_admin_add_relation_role_rules($form, &$form_state) {
  $form = array();
  $relations = spnetsync_get_civi_relationships();
  $form['relations'] = array(
    '#type' => 'fieldset', 
    '#title' => 'CiviCRM relaties -> Drupal rollen',
  );
  $form['relations']['civi_relations'] = array(
    '#type' => 'select',
    '#title' => 'CiviCRM relatie(s)',
    '#options' => $relations,
    '#multiple' => TRUE,
    '#required' => TRUE,
  );
  $roles = spnetsync_roles();
  $form['relations']['drupal_roles'] = array(
    '#type' => 'select',
    '#title' => 'Drupal rol(len)',
    '#options' => $roles,
    '#multiple' => TRUE,
    '#required' => TRUE,
  );

  $form['relations']['submit'] = array(
    '#type'  => 'submit',
    '#value' => 'Voeg toe',
    '#submit' => array('spnetsync_admin_add_relation_role_rules_submit'),
  );

  return $form;
}

function spnetsync_admin_add_relation_role_rules_submit($form, &$form_state) {
  //variable_set('spnetsync_rules', array());
  $values = $form_state['values'];
  // Create values to store.
  foreach ($values['civi_relations'] as $value) {
    $civi_relations[$value] = $form['relations']['civi_relations']['#options'][$value];
  }
  foreach ($values['drupal_roles'] as $value) {
    $drupal_roles[$value] = $form['relations']['drupal_roles']['#options'][$value];
  }
  // Store values.
  $rules = variable_get('spnetsync_rules', array());
  $new_rules = $rules;
  $new_rules['relations-roles'][] = array(
    'civi_relations' => $civi_relations,
    'drupal_roles' => $drupal_roles,
  );
  // Controleer of regel reeds bestaat.
  foreach ($new_rules['relations-roles'] as $key_a => $rule_a) {
    foreach ($new_rules['relations-roles'] as $key_b => $rule_b) {
      if ($rule_a == $rule_b) {
        $duplicates[$key_a] ++;
        foreach ($duplicates as $number) {
          if ($number > 1) {
            // Regel bestaat reeds.
            drupal_set_message('Regel bestaat al, er is geen nieuwe regel toegevoegd.', 'error');
            return;
          }
        }
      }
    }
  }
  // Nieuwe regel.
  variable_set('spnetsync_rules', $new_rules);
  drupal_set_message('Regel is opgeslagen.');
}

function spnetsync_admin_add_field_field_rules($form, &$form_state) {
  $form = array();
  $form['fields'] = array(
    '#type' => 'fieldset', 
    '#title' => 'CiviCRM velden -> Drupal velden',
  );
  $form['fields']['civi_contact_simple_fields'] = array(
    '#type' => 'fieldset', 
    '#prefix' => '<h4>Synchronizeer eenvoudig Civi contact veld</h4>',
  );

  $civi_fields = spnetsync_get_civi_contact_fields();
  $form['fields']['civi_contact_simple_fields']['civi_contact_simple_fields'] = array(
    '#type' => 'select',
    '#options' => $civi_fields,
    '#multiple' => TRUE,
    '#required' => TRUE,
  );

  $form['fields']['civi_contact_email_fields'] = array(
    '#type' => 'fieldset', 
    '#prefix' => '<h4>of Civi contact email veld</h4>',
  );
  $civi_email_location_fields = spnetsync_get_civi_email_locations();
  $form['fields']['civi_contact_email_fields']['civi_contact_email_location_field'] = array(
    '#type' => 'select',
    '#title' => 'Selecteer type',
    '#options' => $civi_email_location_fields,
    '#multiple' => TRUE,
    '#required' => TRUE,
  );

  $form['fields']['civi_contact_phone_fields'] = array(
    '#type' => 'fieldset', 
    '#prefix' => '<h4>of Civi contact telefoon veld</h4>',
  );
  $civi_phone_location_fields = spnetsync_get_civi_phone_locations();
  $form['fields']['civi_contact_phone_fields']['civi_contact_phone_location_field'] = array(
    '#type' => 'select',
    '#title' => 'Selecteer locatie',
    '#options' => $civi_phone_location_fields,
    '#multiple' => TRUE,
    '#required' => TRUE,
  );
  $civi_phone_type_fields = spnetsync_get_civi_phone_types();
  $form['fields']['civi_contact_phone_fields']['civi_contact_phone_type_field'] = array(
    '#type' => 'select',
    '#title' => 'Selecteer type',
    '#options' => $civi_phone_type_fields,
    '#multiple' => TRUE,
    '#required' => TRUE,
  );

  $form['fields']['civi_contact_address_fields'] = array(
    '#type' => 'fieldset', 
    '#prefix' => '<h4>of Civi contact adres veld</h4>',
  );
  $civi_address_location_fields = spnetsync_get_civi_address_locations();
  $form['fields']['civi_contact_address_fields']['civi_contact_address_location_field'] = array(
    '#type' => 'select',
    '#title' => 'Selecteer type',
    '#options' => $civi_address_location_fields,
    '#multiple' => TRUE,
    '#required' => TRUE,
  );
  $civi_address_fields = spnetsync_get_civi_address_fields();
  $form['fields']['civi_contact_address_fields']['civi_contact_address_field'] = array(
    '#type' => 'select',
    '#title' => 'Selecteer adres veld',
    '#options' => $civi_address_fields,
    '#multiple' => TRUE,
    '#required' => TRUE,
  );

  $drupal_fields = array(1 => 'TEST', 2 => 'TEST2');
  $form['fields']['drupal_fields'] = array(
    '#type' => 'select',
    '#prefix' => '<h4>met Drupal account veld</h4>',
    '#options' => $drupal_fields,
    '#multiple' => TRUE,
    '#required' => TRUE,
  );

  $form['fields']['submit'] = array(
    '#type'  => 'submit',
    '#value' => 'Voeg toe',
    '#submit' => array('spnetsync_admin_add_field_field_rules_submit'),
  );

  return $form;
}

function spnetsync_admin_add_field_field_rules_submit($form, &$form_state) {
  //variable_set('spnetsync_rules', array());
  $values = $form_state['values'];
  // Create values to store.
  foreach ($values['civi_fields'] as $value) {
    $civi_fields[$value] = $form['fields']['civi_fields']['#options'][$value];
  }
  foreach ($values['drupal_fields'] as $value) {
    $drupal_fields[$value] = $form['fields']['drupal_fields']['#options'][$value];
  }
  // Store values.
  $rules = variable_get('spnetsync_rules', array());
  $new_rules = $rules;
  $new_rules['fields-fields'][] = array(
    'civi_fields' => $civi_fields,
    'drupal_fields' => $drupal_fields,
  );
  // Controleer of regel reeds bestaat.
  foreach ($new_rules['fields-fields'] as $key_a => $rule_a) {
    foreach ($new_rules['fields-fields'] as $key_b => $rule_b) {
      if ($rule_a == $rule_b) {
        $duplicates[$key_a] ++;
        foreach ($duplicates as $number) {
          if ($number > 1) {
            // Regel bestaat reeds.
            drupal_set_message('Regel bestaat al, er is geen nieuwe regel toegevoegd.', 'error');
            return;
          }
        }
      }
    }
  }
  // Nieuwe regel.
  variable_set('spnetsync_rules', $new_rules);
  drupal_set_message('Regel is opgeslagen.');
}

function spnetsync_admin_list_rules() {
  $rules = variable_get('spnetsync_rules');
  $output = '';
  // Relation - role rules.
  if (!empty($rules['relations-roles'])) {
    $output .= '<table><tr><th>CiviCRM relaties</th><th></th><th>Drupal rollen</th><th></th></tr>';
    foreach($rules['relations-roles'] as $rule_id => $rule) {
      $output .= '<tr><td>';
      foreach ($rule['civi_relations'] as $id => $title) {
        $output .= $title . '<br/>';
      }
      $output .= '</td><td>&rarr;</td><td>';
      foreach ($rule['drupal_roles'] as $id => $title) {
        $output .= $title . '<br/>';
      }
      $output .= '</td><td><a href="/admin/config/sp/spnetsync/delete/relations-roles/' . $rule_id . '">' . t('Delete') . '</a></td></tr>';
    }
    $output .= '</table>';
  }

  // Field - field rules.
  if (!empty($rules['fields-fields'])) {
    $output .= '<table><tr><th>CiviCRM velden</th><th></th><th>Drupal velden</th><th></th></tr>';
    foreach($rules['fields-fields'] as $rule) {
      $output .= '<tr><td>';
      foreach ($rule['civi_fields'] as $id => $title) {
        $output .= $title . '<br/>';
      }
      $output .= '</td><td>&rarr;</td><td>';
      foreach ($rule['drupal_fields'] as $id => $title) {
        $output .= $title . '<br/>';
      }
      $output .= '</td><td>' . t('Delete') . '</td></tr>';
    }
    $output .= '</table>';
  }
  if (empty($output)) {
    drupal_set_message('Er zijn nog geen regels aangemaakt.', 'warning');
  }
  return $output;
}

function spnetsync_delete($type, $rule_id) {
  $rules = variable_get('spnetsync_rules');
  switch ($type) {
  case 'relations-roles':
    if (!empty($rules['relations-roles'][$rule_id])) {
      unset($rules['relations-roles'][$rule_id]);
      variable_set('spnetsync_rules', $rules);
      drupal_set_message('Rule was deleted.');
    }
    else {
      drupal_set_message('Error deleting rule.', 'error');
    }
    break;
  case 'field-field':
    break;
  }
  drupal_goto('/admin/config/sp/spnetsync');
}
