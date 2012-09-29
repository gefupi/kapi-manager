<?php
/**
 * @file
 *   A database handler for dependency related database operations.
 */

/**
 * This function is returns a ResultSet containing the dependencies for a given product from db.
 *
 * @return
 *   An array containing the result set
 */
function _kapi_manager_db_get_h_dependencies($product_id) {
  $query = db_select('kapi_manager_dependencies', 'd');
  $query->join('kapi_manager_products', 'p', 'p.id = d.dependency_id');
  $query->fields('d', array('factor'))
    ->fields('p', array('name'))
    ->condition('d.product_id', $product_id, '=');
  return $query->execute();
}
