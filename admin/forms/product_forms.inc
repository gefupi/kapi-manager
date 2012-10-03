<?php
/**
 * @file
 * This file provides the forms used in product administration context.
 */

/**
 * This function implements the form for the 'edit product form'.
 *
 * @param form
 *   an array of form arguments
 * @param form_stat
 *   reference to the array of form state
 * @param product_id
 *   0 - to add new product or
 *   positiv number - to edit product with given id
 *
 * @return
 *   An array containing the form elements to be displayed in the product
 *   editing form.
 */
function _kapi_manager_edit_product_form($node, &$form_state, $product_id) {
  $form['product_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Product name:'),
    '#default_value' => '',
    '#size' => 35,
    '#maxlength' => 35,
    '#description' => t('Please enter product name.'),
    '#required' => TRUE,
  );

  // add workshop selection
  _kapi_manager_add_workshop_selection_to_form($form);

  // set actual values if product is edited
  if ($product_id) {
    module_load_include('inc', 'kapi_manager', 'database/product_handler');
    $product = _kapi_manager_db_get_products($product_id)->fetchObject();
    $form['product_name']['#default_value'] = $product->name;
    $form['workshop']['#default_value'] = $product->workshop_id;
  }

  /*
  $header = array(
    'product' = t('Product'),
    // @todo add factor header
  );
  $options = array();

  $form['dependencies'] = array(
    '#type'        => 'tableselect',
    '#title'       => t('Dependencies'),
    '#description' => t('Select the dependencies and set their factors'),
    '#header'      => $header,
    '#options'     => $options,
  );
  */

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['cancel'] = array(
    '#markup' => l(t('Cancel'), 'kapi_manager/admin/products'),
  );

  return $form;
}



/**
 * This add a workshop selection table to the given form.
 *
 * @param form
 *   an array of form arguments
 */
function _kapi_manager_add_workshop_selection_to_form(&$form) {
  module_load_include('inc', 'kapi_manager', 'database/workshop_handler');
  $workshop_header = array('workshop' => t('Workshop'), );
  $workshop_options = array();
  $workshops = _kapi_manager_db_get_workshops();
  foreach($workshops  as $workshop) {
    $workshop_options[$workshop->id] = array(
      'workshop' => t($workshop->name),
    );
  }

  $form['workshop'] = array(
    '#type'        => 'tableselect',
    '#title'       => t('Workshop'),
    '#description' => t('Select the Workshop'),
    '#header'      => $workshop_header,
    '#options'     => $workshop_options,
    '#multiple'    => FALSE,
    '#js_select'   => FALSE,
    '#empty' => t('no workshops found'),
  );
}


/**
 * This function implements validation for the 'edit product form'.
 *
 * @param form
 *   an array of form arguments
 * @param form_stat
 *   reference to the array containing the form state
 */
function _kapi_manager_edit_product_form_validate($form, &$form_state) {
  $product_name = $form_state['values']['product_name'];
  $old_name = $form['product_name']['#default_value'];
  $changed = !($old_name === $product_name);
  module_load_include('inc', 'kapi_manager', 'database/product_handler');
  $duplicate = _kapi_manager_db_exists_product($product_name);
  if ($product_name === '') {
    form_set_error('product_name', t('You must specify a name for the product'));
  }
  elseif ($changed && $duplicate) {
    form_set_error('product_name', t("The product '@product_name' already exists.",
      array('@product_name' => $product_name)));
  }
}

/**
 * This function implements submit actions for the 'edit product form'.
 *
 * If no default product name was not set in form, it is a new product and a
 * new entry will be inserted into database. If the default product name was
 * set and is changed the according database entry is updated. If the default
 * product name was set and is unchanged database will not be changed.
 * After each action an according drupal message is set and site
 * 'kapi_manager/admin/products' is called.
 *
 * @param form
 *   an array of form arguments
 * @param form_stat
 *   reference to the array containing the form state
 */
function _kapi_manager_edit_product_form_submit($form, &$form_state) {
// @todo: check wich workshop is chosen and whether it is changed
  $new_name = $form_state['values']['product_name'];
  $old_name = $form['product_name']['#default_value'];
  module_load_include('inc', 'kapi_manager', 'database/product_handler');
  if ($old_name === $new_name) {
    drupal_goto('kapi_manager/admin/products');
  }
  elseif ($old_name) {
    if (_kapi_manager_db_update_product($old_name, $new_name)) {
      drupal_set_message($message = t("Changed product name from '@old_name' to '@new_name'",
        array('@old_name' => $old_name, '@new_name' => $new_name, )),
        $type = 'status');
    }
    else {
      drupal_set_message($message = t("Failed to change product name from '@old_name' to '@new_name'",
        array('@old_name' => $old_name, '@new_name' => $new_name, )),
        $type = 'error');
    }
  }
  else {
    _kapi_manager_db_insert_product($new_name);
    drupal_set_message($message = t("Added product '@product_name'",
      array('@product_name' => $new_name)), $type = 'status');
  }
  drupal_goto('kapi_manager/admin/products');
}


/**
 * This function implements the confirm form for delete product action.
 *
 * @param form
 *   an array of form arguments
 * @param form_stat
 *   reference to the array of form state
 * @param product_id
 *   0 - to add new product
 *   number - to edit product with given id
 *
 * @return
 *   An array containing the confirm form elements to be displayed in the delete
 *   product confirm form.
 */
function _kapi_manager_delete_product_confirm_form($form, &$form_state, $product_id) {
  module_load_include('inc', 'kapi_manager', 'database/product_handler');
  $name = _kapi_manager_db_get_product_name($product_id);
  $form['product_name'] = array(
    '#type'  => 'value',
    '#value' => $name,
  );

  return confirm_form($form,
    t("Are you sure you want to delete product '@product_name'?", array('@product_name' => $name)),
    'kapi_manager/admin/products',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * This function implements the confirm form submit for delete product action.
 *
 * @param form
 *   an array of form arguments
 * @param form_stat
 *   reference to the array of form state
 */
function _kapi_manager_delete_product_confirm_form_submit($form, &$form_state) {
  $name = $form_state['values']['product_name'];
  module_load_include('inc', 'kapi_manager', 'database/product_handler');
  _kapi_manager_db_delete_product($name);
  drupal_set_message($message = t("Deleted product '@product_name'",
    array('@product_name' => $name)), $type = 'status');
  drupal_goto('kapi_manager/admin/products');
}
