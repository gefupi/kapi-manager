<?php

/*
 *
 */
function kapi_manager_getSchemas() {
  $schemas = array();
  $schemas['kapi_manager_products'] = _getProductsSchema();
  return $schemas;
}


function _getProductsSchema() {
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
    'unique key'  => array(
      'name' =>'name'
    ),
    'index'       => array(
      'idx_name' => 'name'
    ),
  );
  return $productsSchema;
}


