<?php
/**
 * @file
 * TODO: documentation
 */

/*
 * This function implements the form for the 'add workshop form'.
 *
 * @param form
 *   an array of form arguments
 * @param form_stat
 *   reference to the array of form state
 */
function _kapi_manager_add_workshop_form($form, &$form_state) {
  $form['workshop_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Workshop name:'),
    '#default_value' => '',
    '#size' => 35,
    '#maxlength' => 35,
    '#description' => t('Please enter workshop name.'),
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/*
 * This function implements validation for the 'add workshop form'.
 *
 * @param form
 *   an array of form arguments
 * @param form_stat
 *   reference to the array containing the form state
 */
function _kapi_manager_add_workshop_form_validate($form, &$form_state) {
  $workshop_name = $form_state['values']['workshop_name'];
  module_load_include('inc', 'kapi_manager', 'database/workshop_handler');
  if ($workshop_name === '') {
    form_set_error('workshop_name', t('You must specify a name for the workshop'));
  }
  elseif (_kapi_manager_exists_workshop($workshop_name)) {
    form_set_error('workshop_name', t("The workshop '@workshop_name' already exists.",
      array('@workshop_name' => $workshop_name)));
  }
}

/*
 * This function implements submit actions for the 'add workshop form'.
 *
 * @param form
 *   an array of form arguments
 * @param form_stat
 *   reference to the array containing the form state
 */
function _kapi_manager_add_workshop_form_submit($form, &$form_state) {
  $workshop_name = $form_state['values']['workshop_name'];
  module_load_include('inc', 'kapi_manager', 'database/workshop_handler');
  // TODO: implement this function
  _kapi_manager_save_workshop($workshop_name);
  drupal_set_message($message = t("Added workshop '@workshop_name' to database", array('@workshop_name' => $workshop_name)), $type = 'status');
}

