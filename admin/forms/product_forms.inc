<?php
/**
 * @file
 * This file provides the forms used in product administration context.
 */


// @todo: all select options arrays should be sorted with sort. The default_value
//        must be detected afterwards using name not index of item.


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

  // add workshop selection and dependency input
  _kapi_manager_add_workshop_selection_to_form($form);
  _kapi_manager_add_dependency_selections_to_form($form);

  // set actual values if product is edited
  if ($product_id) {
    module_load_include('inc', 'kapi_manager', 'database/product_handler');
    module_load_include('inc', 'kapi_manager', 'database/dependency_handler');
    $product = _kapi_manager_db_get_products($product_id)->fetchObject();
    $form['product_name']['#default_value'] = $product->name;
    $workshop = _kapi_manager_db_get_workshop_name($product->workshop_id);
    $form['workshop']['#default_value'] = array_search($workshop, $form['workshop']['#options']);
    $dependencies = _kapi_manager_db_get_dependencies($product_id);
    $counter = 1;
    foreach ($dependencies as $dependency) {
      $form['dependency_group_' . $counter]['dependency_' . $counter]['#default_value'] = $dependency->dependency_id;
      $form['dependency_group_' . $counter]['factor_' . $counter]['#default_value'] = $dependency->factor;
      $counter += 1;
    }
  }

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
 * This function adds 5 dependency selections to the given form.
 *
 * @param form
 *   an array of form arguments
 */
function _kapi_manager_add_dependency_selections_to_form(&$form) {
  module_load_include('inc', 'kapi_manager', 'database/product_handler');
  $product_options = array(t('--- None ---'));
  $products = _kapi_manager_db_get_h_products();
   foreach($products as $product) {
    $product_options[] = $product->name;
  }

  $counter = 1;
  $form['dependencies'] = array(
    '#types' => 'vertical_tabs',
  );
  while ($counter <6) {
    $form['dependency_group_' . $counter] = array(
      '#type'        => 'fieldset',
      '#title'       => 'Dependency ' . $counter,
      '#collapsible' => TRUE,
      '#group'       => 'dependencies',
    );

    $form['dependency_group_'. $counter]['dependency_' . $counter] = array(
      '#title'         => t('Product'),
      '#type'          => 'select',
      '#default_value' => 0,
      '#description'   => t('Select a product as dependency'),
      '#options'       => $product_options,
    );

    $form['dependency_group_' . $counter]['factor_' . $counter] = array(
      '#type' => 'textfield',
      '#title' => t('Factor:'),
      '#default_value' => '',
      '#size' => 5,
      '#maxlength' => 5,
      '#description' => t('Please enter factor of dependency product.'),
    );

    $counter +=1;
  }
	
}

/**
 * This function adds a workshop selection to the given form.
 *
 * @param form
 *   an array of form arguments
 */
function _kapi_manager_add_workshop_selection_to_form(&$form) {
  module_load_include('inc', 'kapi_manager', 'database/workshop_handler');
  $workshops = _kapi_manager_db_get_workshops();
  $sorted_workshops = array();
  foreach($workshops as $workshop) {
    $sorted_workshops[] = $workshop->name;
  }
  sort($sorted_workshops, SORT_STRING);
  $workshop_options = array(t('--- SELECT ---'));
  foreach($sorted_workshops as $workshop) {
    $workshop_options[] = $workshop;
  }

  $form['workshop'] = array(
    '#title'         => t('Workshop'),
    '#type'          => 'select',
    '#default_value' => 0,
    '#description'   => t('Select the workshop'),
    '#options'       => $workshop_options,
    '#required'      => TRUE,
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
  _kapi_manager_edit_product_form_validate_dependencies($form, $form_state, $old_name);
}

/**
 * This function is used to vaildate the dependencies
 *
 * @todo: documentation
 */
function _kapi_manager_edit_product_form_validate_dependencies($form, $form_state, $product) {
  $dependencies = array();
  for($i=1; $i < 6; $i++) {
    $dependency_index = $form_state['values']['dependency_' . $i];
    $dependency = $form['dependency_group_' . $i]['dependency_' . $i]['#options'][$dependency_index];
    $factor = $form_state['values']['factor_' . $i];
    if ($dependency_index != 0) {
      if ($factor === ''){
	// factor is empty 
        $message = t("Missing factor for dependency @i (@product).", 
	  array('@i' => $i, '@product' => $dependency));
	form_set_error('factor_' . $i, $message);
      } else if (! is_numeric($factor)) {
        // factor is not a valid number
        $message = t("Factor for dependency @i (@product) must be numeric.",
          array('@i' => $i, '@product' => $dependency));
        form_set_error('factor_' . $i, $message);
      } else if ($factor <= 0) {
        // factor is less than or equal zero
        $message = t("Factor for dependency @i (@product) must be greater than "
          . "zero.", array('@i' => $i, '@product' => $dependency));
        form_set_error('factor_' . $i, $message);
      }
      if ($dependency === $product) {
        // dependency equals edited product
        $message = t("The product (@product) cannot be selected as it's own "
          . "dependency @i (even if you try to renamed it in the same step).",
          array('@i' => $i, '@product' => $product));
        form_set_error('dependency_' . $i, $message);
      }
    }
    $dependencies[$i] = array('name' => $dependency, 'index' => $dependency_index);
  }
  // check that each dependency product is selected only once as dependency
  for ($i=1; $i < 6; $i++) {
    for ($j=1; $j < 6; $j++) {
      if (! ($i < $j)) {continue;}
      if (($dependencies[$i]['index'] === '0') or ($dependencies[$j]['index'] === '0')) {continue;}
      if ($dependencies[$i]['index'] === $dependencies[$j]['index']) {
        // found a product as dependency twice
        form_set_error('dependency_' . $i, t("@product is selected as dependency @i",
        array('@i' => $i, '@product' => $dependencies[$i]['name'])));
        form_set_error('dependency_' . $j, t("and @product is also selected as dependency @j",
        array('@j' => $j, '@product' => $dependencies[$i]['name'])));
      }
    }
  }
}

/**
 * @todo: documentation
 */
function _kapi_manager_edit_product_form_read_values($form, $form_state) {
  module_load_include('inc', 'kapi_manager', 'database/product_handler');
  module_load_include('inc', 'kapi_manager', 'database/workshop_handler');
  // gather product info
  $old_name = $form['product_name']['#default_value'];
  $product = array(
    'name' => $form_state['values']['product_name'],
    'id'   => _kapi_manager_db_get_product_id($old_name)
  );
  if($old_name === '') {
    $product['existed'] = FALSE;
  } else {
    $product['existed'] = TRUE;
  }
  //gather workshop info
  $index = $form_state['values']['workshop'];
  $name = $form['workshop']['#options'][$index];
  $workshop = array(
    'id' => _kapi_manager_db_get_workshop_id($name),
  );
  // gather dependency info
  $dependencies = array();
  for($i = 1; $i < 6; $i++){
    $dependency_index = $form_state['values']['dependency_' . $i];
    if (! ($dependency_index === '0')) {
      $dependency_name = $form['dependency_group_' . $i]['dependency_' . $i]['#options'][$dependency_index];
      $factor = $form_state['values']['factor_' . $i];
      $dependency_id = _kapi_manager_db_get_product_id($dependency_name);
      $dependencies[] = array(
        'id'     => $dependency_id,
        'factor' => $factor
      );
    }
  }
  return array($product, $workshop, $dependencies);
}

/**
 * This function implements submit actions for the 'edit product form'.
 *
 * @todo: update this documentation
 * If no default product name was set in form, it is a new product and a
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
  module_load_include('inc', 'kapi_manager', 'database/product_handler');
  list($product, $workshop, $dependencies) = _kapi_manager_edit_product_form_read_values($form, $form_state);
  if ($product['existed']) {
    // update existing product
    _kapi_manager_db_update_product($product['id'], $product['name'], $workshop['id']);
  } else {
    // add a new product
    _kapi_manager_db_insert_product($product['name'], $workshop['id']);
  }
  // set dependencies in database
  _kapi_manager_db_set_dependencies($product['id'], $dependencies);  
  drupal_set_message($message = t("Saved product '@product' successful.", 
    array('@product' => $product['name'])), $type = 'status');
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
    t("Are you sure you want to delete product '@product_name'? "
      . "WARNING: This may result in corupt data.", 
      array('@product_name' => $name)),
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
  $id = _kapi_manager_db_get_product_id($name);
  _kapi_manager_db_delete_product($id);
  drupal_set_message($message = t("Deleted product '@product_name'",
    array('@product_name' => $name)), $type = 'status');
  drupal_goto('kapi_manager/admin/products');
}
