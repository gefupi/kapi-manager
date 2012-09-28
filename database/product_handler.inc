<?php
/**
 * @file
 *   A database handler for product related database operations.
 */


/**
 * This function is returns a ResultSet containing all products from db.
 */
function _kapi_manager_db_get_products() {
  $query = db_select('kapi_manager_products', 'p')
    ->fields('p', array('id', 'name', 'workshop_id'));
  return $query->execute();
}

/**
 * This function returns the name of the product with given ID.
 *
 * @para id
 *   ID of the product
 * @return string
 */
function _kapi_manager_db_get_product_name($id) {
  return db_select('kapi_manager_products', 'p')
    ->fields('p', array('name'))
    ->condition('id', $id, 'LIKE')
    ->execute()
    ->fetchField();
}

/**
 * This function returns true if a product with given name already exists in
 * database, else false will be returned.
 *
 * @param product_name
 *   string containing the product name
 * @return boolean
 */
function _kapi_manager_db_exists_product($product_name) {
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
function _kapi_manager_db_insert_product($product_name) {
  // TODO: implement this function

}

/*
 * TODO: Documentation
 */
function _kapi_manager_db_update_product($product_name) {
  // TODO: implement this function

}
