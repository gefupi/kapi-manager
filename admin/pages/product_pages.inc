<?php
/**
 * @file
 * This file provides the pages used in product administration context.
 */

/**
 * This function implements the page listing all products.
 *
 * @return
 *   An array containing the page elements to be displayed in the list products
 *   page.
 */
function kapi_manager_list_products_page() {
  drupal_set_title(t('Product'));
  module_load_include('inc', 'kapi_manager', 'database/product_handler');
  $result = _kapi_manager_get_products();
  $rows = array();
  foreach ($result as $product) {
    $rows[] = array(
      array('data' => $product->id, ),
      array('data' => $product->name, ),
    );
  }
  $header = array(
    array('data' => 'id', 'align' => 'center'),
    array('data' => 'name', 'align' => 'center'),
  );
  return theme('table', array('header' => $header, 'rows' => $rows));
}
