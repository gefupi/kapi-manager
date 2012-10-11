<?php
/**
 * @file
 *   A database handler for dependency related database operations.
 */

/**
 * This function is returns a ResultSet containing the dependencies for a given
 * product from db.
 *
 * @param $product_id
 *   The product_id value
 *
 * @return
 *   An array containing the result set
 */
function _kapi_manager_db_get_dependencies($product_id) {
  $query = db_select('kapi_manager_dependencies', 'd');
  $query->fields('d', array('dependency_id', 'factor'))
    ->condition('d.product_id', $product_id, '=');
  return $query->execute();
}

/**
 * This function is returns a ResultSet containing the human readable 
 * dependencies for a given product from db.
 *
 * @param $product_id
 *   The product_id value
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


/**
 * This function first deletes all entries for given product from dependency
 * table. Afterwards all dependencies from given array will be added.
 *
 * @param $product_id
 *   The product_id
 * @param $dependencies
 *   An Array containing all dependencies, each is an array with keys 
 *   'id' and 'factor'
 */
function _kapi_manager_db_set_dependencies($product_id, $dependencies) {
  db_delete('kapi_manager_dependencies')
    ->condition('product_id', $product_id)
    ->execute();
  foreach($dependencies as $dependency) {
    db_insert('kapi_manager_dependencies')
      ->fields(array(
        'product_id'    => $product_id,
        'dependency_id' => $dependency['id'],
        'factor'        => $dependency['factor'],
      ))
    ->execute();
  }
}