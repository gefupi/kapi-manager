<?php
/**
 * @file
 * TODO: documentation
 */

/*
 * TODO: Dokumentation
 */
function _kapi_manager_add_product_form($form, &$form_state) {
  $form['product_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Product name:'),
    '#default_value' => '',
    '#size' => 35,
    '#maxlength' => 35,
    '#description' => t('Please enter product name.'),
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/*
 * TODO: Dokumentation
 */
function _kapi_manager_add_product_form_validate($form, &$form_state) {
  $product_name = $form_state['values']['product_name'];
  module_load_include('inc', 'kapi_manager', 'database/product_handler');
  if ($product_name === '') {
    form_set_error('product_name', t('You must specify a name for the product'));
  }
  elseif (_kapi_manager_exists_product($product_name)) {
    form_set_error('product_name', t("The product '@product_name' already exists.",
      array('@product_name' => $product_name)));
  }
}

/*
 * TODO: Dokumentation
 */
function _kapi_manager_add_product_form_submit($form, &$form_state) {
  $product_name = $form_state['values']['product_name'];
  module_load_include('inc', 'kapi_manager', 'database/product_handler');
  // TODO: implement this function
  _kapi_manager_save_product($product_name);
  drupal_set_message($message = t("Added product '@product_name' to database", array('@product_name' => $product_name)), $type = 'status');
}

