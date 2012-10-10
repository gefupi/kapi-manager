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
    $form['workshop']['#default_value'] = $product->workshop_id;
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
  $workshop_options = array(t('--- SELECT ---'));
  $workshops = _kapi_manager_db_get_workshops();
   foreach($workshops as $workshop) {
    $workshop_options[] = $workshop->name;
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
  $dependencies = _kapi_manager_product_forms_get_depedencies_from_edit_form($form, $form_state);
  
  print_r($form_state['values']);
  /*
  $dep1_n = $form_state['values']['dependency_1'];
  $dep1_f = $form_state['values']['factor_1'];
  form_set_error('', t("[DEBUG]: Dependency 1 has name @dep_n and factor @dep_f", 
    array('@dep_n' => $dep1_n, '@dep_f' => $dep1_f)));
*/
}

/**
 * @todo: documentation
 */
function _kapi_manager_product_forms_get_depedencies_from_edit_form($form, $form_state) {
  $result = array();
  for($i=1; $i < 6; $i++) {
    $dependency_index = $form_state['values']['dependency_' . $i];
    $dependency = $form['dependency_group_' . $i]['dependency_' . $i]['#options'][$dependency_index];
    $factor = $form_state['values']['factor_' . $i];
    if ($dependency_index != 0) {
      // validate factor input
      if ($factor === ''){
        form_set_error('factor_' . $i, 
          t("Missing factor for dependency @i (@product).", 
          array('@i' => $i, '@product' => $dependency))
        );
      } else if (! is_numeric($factor)) {
        form_set_error('factor_' . $i, 
          t("Factor for dependency @i must be numeric.",
	    array('@i' => $i))
        );
      } else if ($factor <= 0) {
        form_set_error('factor_' . $i, 
          t("Factor for dependency @i must be greater than zero.",
          array('@i' => $i))
        );
      }
    }
    $result[$i] = array('dependency' => $dependency, 'factor' => $factor);
  }
  /* @todo: check wether a product is coosen twice as dependency */
  
  return $result;
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
  $new_workshop_index = $form_state['values']['workshop'];
  $old_workshop_index = $form['workshop']['#default_value'];
  $workshop = $form['workshop']['#options'][$new_workshop_index];
  module_load_include('inc', 'kapi_manager', 'database/product_handler');
  $changed_name = !($old_name === $new_name);
  $changed_workshop = !($old_workshop_index === $new_workshop_index);
  if (!$changed_name) {
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
    drupal_set_message($message = t("Added product '@product_name' with workshop '@workshop'",
      array('@product_name' => $new_name, '@workshop' => $workshop)), $type = 'status');
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
