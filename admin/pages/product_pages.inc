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
  $result = _kapi_manager_db_get_h_products();
  $rows = array();
  foreach ($result as $product) {
    $rows[] = array(
      array('data' => $product->name, ),
      array('data' => $product->w_name, ),
      array('data' => l(t('edit'), "kapi_manager/admin/products/$product->id/edit"), ),
      array('data' => l(t('delete'), "kapi_manager/admin/products/$product->id/delete"), ),
    );
  }
  $header = array(
    array('data' => 'Name', 'align' => 'center'),
    array('data' => 'Workshop', 'align' => 'center'),
    array('data' => 'Operations', 'align' => 'center', 'colspan' => 2, ),
  );
  return theme('table', array('header' => $header, 'rows' => $rows));
}
