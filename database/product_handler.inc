<?php
/**
 * @file
 *   A database handler for product related database operations.
 */


/**
 * This function is returns a ResultSet containing all products from db.
 */
function _kapi_manager_get_products() {
  $query = db_select('kapi_manager_products', 'p')
    ->fields('p', array('id', 'name'));
  return $query->execute();
}

/**
 * This function returns true if a product with given name already exists in
 * database, else false will be returned.
 *
 * @param product_name
 *   string containing the product name
 * @return boolean
 */
function _kapi_manager_exists_product($product_name) {
  $query = db_select('kapi_manager_products', 'p')
    ->fields('p', array('name'))
    ->condition('name', $product_name, 'LIKE')
    ->execute()
    ->fetchField();
  if ($query === $product_name) {
    return TRUE;
  }
  return FALSE;
}

/*
 * TODO: Documentation
 */
function _kapi_manager_save_product($product_name) {
  // TODO: implement this function

}