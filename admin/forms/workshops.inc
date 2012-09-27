<?php
/**
 * @file
 * This file provides the forms used in workshop context.
 */

/**
 * This function implements the form for the 'edit workshop form'.
 *
 * @param form
 *   an array of form arguments
 * @param form_stat
 *   reference to the array of form state
 * @param workshop_id
 *   0 - to add new workshop
 *   number - to edit workshop with given id
 */
function _kapi_manager_edit_workshop_form($node, &$form_state, $workshop_id) {
  $form['workshop_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Workshop name:'),
    '#default_value' => '',
    '#size' => 35,
    '#maxlength' => 35,
    '#description' => t('Please enter workshop name.'),
    '#required' => TRUE,
  );

  if ($workshop_id) {
    module_load_include('inc', 'kapi_manager', 'database/workshop_handler');
    $name = _kapi_manager_db_get_workshop_name($workshop_id);
    $form['workshop_name']['#default_value'] = $name;
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['cancel'] = array(
    '#markup' => l(t('Cancel'), 'kapi_manager/admin/workshops'),
  );

  return $form;
}

/**
 * This function implements validation for the 'edit workshop form'.
 *
 * @param form
 *   an array of form arguments
 * @param form_stat
 *   reference to the array containing the form state
 */
function _kapi_manager_edit_workshop_form_validate($form, &$form_state) {
  $workshop_name = $form_state['values']['workshop_name'];
  $old_name = $form['workshop_name']['#default_value'];
  $changed = !($old_name === $workshop_name);
  module_load_include('inc', 'kapi_manager', 'database/workshop_handler');
  $duplicate = _kapi_manager_db_exists_workshop($workshop_name);
  if ($workshop_name === '') {
    form_set_error('workshop_name', t('You must specify a name for the workshop'));
  }
  elseif ($changed && $duplicate) {
    form_set_error('workshop_name', t("The workshop '@workshop_name' already exists.",
      array('@workshop_name' => $workshop_name)));
  }
}

/**
 * This function implements submit actions for the 'edit workshop form'.
 *
 * If no default workshop name was not set in form, it is a new workshop and a
 * new entry will be inserted into database. If the default workshop name was
 * set and is changed the according database entry is updated. If the default
 * workshop name was set and is unchanged database will not be changed.
 * After each action an according drupal message is set and site 
 * 'kapi_manager/admin/workshops' is called.
 *
 * @param form
 *   an array of form arguments
 * @param form_stat
 *   reference to the array containing the form state
 */
function _kapi_manager_edit_workshop_form_submit($form, &$form_state) {
  $new_name = $form_state['values']['workshop_name'];
  $old_name = $form['workshop_name']['#default_value'];
  module_load_include('inc', 'kapi_manager', 'database/workshop_handler');
  if ($old_name === $new_name) {
    drupal_goto('kapi_manager/admin/workshops');
  }
  elseif ($old_name) {
    if (_kapi_manager_db_update_workshop($old_name, $new_name)) {
      drupal_set_message($message = t("Changed workshop name from '@old_name' to '@new_name'",
        array('@old_name' => $old_name, '@new_name' => $new_name, )),
        $type = 'status');
    }
    else {
      drupal_set_message($message = t("Failed to change workshop name from '@old_name' to '@new_name'",
        array('@old_name' => $old_name, '@new_name' => $new_name, )),
        $type = 'error');
    }
  }
  else {
    _kapi_manager_db_insert_workshop($new_name);
    drupal_set_message($message = t("Added workshop '@workshop_name'",
      array('@workshop_name' => $new_name)), $type = 'status');
  }
  drupal_goto('kapi_manager/admin/workshops');
}


/**
 * This function implements the confirm form for delete workshop action.
 *
 * @param form
 *   an array of form arguments
 * @param form_stat
 *   reference to the array of form state
 * @param workshop_id
 *   0 - to add new workshop
 *   number - to edit workshop with given id
 */
function _kapi_manager_delete_workshop_confirm_form($form, &$form_state, $workshop_id) {
  module_load_include('inc', 'kapi_manager', 'database/workshop_handler');
  $name = _kapi_manager_db_get_workshop_name($workshop_id);
  $form['workshop_name'] = array(
    '#type'  => 'value',
    '#value' => $name,
  );

  return confirm_form($form, 
    t("Are you sure you want to delete workshop '@workshop_name'?", array('@workshop_name' => $name)),
    'kapi_manager/admin/workshops',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}


/**
 * This function implements the confirm form submit for delete workshop action.
 *
 * @param form
 *   an array of form arguments
 * @param form_stat
 *   reference to the array of form state
 */
function _kapi_manager_delete_workshop_confirm_form_submit($form, &$form_state) {
  $name = $form_state['values']['workshop_name'];
  module_load_include('inc', 'kapi_manager', 'database/workshop_handler');
  _kapi_manager_db_delete_workshop($name);
  drupal_set_message($message = t("Deleted workshop '@workshop_name'",
    array('@workshop_name' => $name)), $type = 'status');
  drupal_goto('kapi_manager/admin/workshops');  
}



