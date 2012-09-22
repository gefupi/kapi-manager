<?php

/*
 *
 */
function kapi_manager_getSchemas() {
  $schemas = array();
  $schemas['kapi_manager_products'] = _kapi_manager_getProductsSchema();
  $schemas['kapi_manager_dependencies'] = _kapi_manager_getDependenciesSchema();
  return $schemas;
}


/*
 * This function returns an array description for the products schema.
 */
function _kapi_manager_getProductsSchema() {
  $productsSchema = array(
    'description' => t('Stores product ID\'s and names'),
    'fields' => array(
      'id' => array(
        'type'        => 'serial',
        'unsigend'    => TRUE,
        'not null'    => TRUE,
        'description' => t('The product ID to indicate products by numbers'),
      ),
      'name' => array(
        'type'        => 'varchar',
        'length'      => '35',
        'not null'    => TRUE,
        'description' => t('The human readable name of the product'),
      ),
    ),
    'primary key' => array('id'),
    'unique key' => array(
      'name' => array('name'),
    ),
    'index' => array(
      'idx_name' => array('name'),
    ),
  );
  return $productsSchema;
}


/*
 * This function returns an array description for the dependencies schema.
 */
function _kapi_manager_getDependenciesSchema() {
  $dependenciesSchema = array(
    'descritpion' => t('Stores dependecies of products'),
    'fields' => array(
      'product_id' => array(
        'type'        => 'int',
        'unsigend'    => TRUE,
        'not null'    => TRUE,
        'description' => t('The product ID'),
      ),
      'dependency_id' => array(
        'type'        => 'int',
        'unsigend'    => TRUE,
        'not null'    => TRUE,
        'description' => t('The product ID of a dependency product'),
      ),
      'factor' => array(
        'type'        => 'float',
        'unsigend'    => TRUE,
        'not null'    => TRUE,
        'description' => t('The factor of the dependency product'),
      )
    ),
    'unique keys' => array(
      'dep' => array('product_id', 'dependency_id'),
    ),
    'foreign_keys' => array(
      'table'   => 'kapi_manager_products',
      'columns' => array(
        'product_id' => 'id',
        'dependency_id' => 'id',
      ),
    ),
    'index' => array(
      'idx_product_id' => array('product_id'),
    )
  );
  return $dependenciesSchema;
}



