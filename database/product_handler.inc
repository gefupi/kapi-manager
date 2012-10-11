<?php
/**
 * @file
 *   A database handler for product related database operations.
 */


/**
 * This function is returns a ResultSet containing product(s) from db.
 *
 * The returned result set contains all fileds of the product table (id, name
 * and workshop_id). If an (optional) parameter is given, the result set will
 * only contain the product with given product_id.
 *
 * @para product_id
 *   (optional) product_id to constrain
 *
 * @return
 *   An array containing the result set
 */
function _kapi_manager_db_get_products($product_id = FALSE) {
  $query = db_select('kapi_manager_products', 'p')
    ->fields('p', array('id', 'name', 'workshop_id'));
  if ($product_id) {
    $query->condition('id', $product_id, '=');
  }
  $result = $query->execute();
  return $result;
}

/**
 * This function is returns a ResultSet containing all products and their
 * according workshops in human readable form from db.
 *
 * @return
 *   An array containing the result set
 */
function _kapi_manager_db_get_h_products() {
  $query = db_select('kapi_manager_products', 'p');	
  $query->join('kapi_manager_workshops', 'w', 'p.workshop_id = w.id');
  $query->fields('p', array('id', 'name'))
    ->fields('w', array('name'));
  return $query->execute();
}

/**
 * This function returns the id of the product with given name.
 *
 * @para name
 *   name of the product
 * @return string
 */
function _kapi_manager_db_get_product_id($name) {
  return db_select('kapi_manager_products', 'p')
    ->fields('p', array('id'))
    ->condition('name', $name, 'LIKE')
    ->execute()
    ->fetchField();
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
    ->condition('id', $id, '=')
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
  $result = db_select('kapi_manager_products', 'p')
    ->fields('p', array('name'))
    ->condition('name', $product_name, 'LIKE')
    ->execute()
    ->fetchField();
  if ($result === $product_name) {
    return TRUE;
  }
  return FALSE;
}

/**
 * This function insert a new row into the product table.
 *
 * @param $product_name
 *   string containing the name of the new product
 * @param $workshop_id
 *   workshop id for the product
 *
 * @return
 *   An array containing the result set
 */
function _kapi_manager_db_insert_product($product_name, $workshop_id) {
  $result = db_insert('kapi_manager_products')
    ->fields(array(
      'name'        => $product_name,
      'workshop_id' => $workshop_id,
    ))
    ->execute();
  return $result;
}

/**
 * This function updates a row in table product.
 *
 * @param $product_id
 *   the product id of product to update
 * @param $product_name
 *   string containing the product name
 * @param $workshop_id
 *   workshop id for the product
 *
 * @return
 *   An array containing the result set
 */
function _kapi_manager_db_update_product($product_id, $product_name, $workshop_id) {
  $result = db_update('kapi_manager_products')
    ->fields(array(
      'name'        => $product_name,
      'workshop_id' => $workshop_id,
    ))
    ->condition('id', $product_id, '=')
    ->execute();
  return $result;
}

/**
 * This function deletes a row in table product.
 *
 * @param $product_id
 *   the product id of product to delete
 * @return
 *   An array containing the result set
 */
function _kapi_manager_db_delete_product($product_id) {
  $result = db_delete('kapi_manager_products')
    ->condition('id', $product_id)
    ->execute();
  return $result;
}
