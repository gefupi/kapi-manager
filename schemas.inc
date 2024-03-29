<?php
/*
 * @file
 *   This file provides the database schemas for tables used by modul
 *   kapi_manager.
 */

/*
 * TODO: documentation
 */
function kapi_manager_getSchemas() {
  $schemas = array();
  $schemas['kapi_manager_products'] = _kapi_manager_getProductsSchema();
  $schemas['kapi_manager_dependencies'] = _kapi_manager_getDependenciesSchema();
  $schemas['kapi_manager_workshops'] = _kapi_manager_getWorkshopSchema();
  return $schemas;
}


/*
 * This function returns an array description for the products schema.
 *
 * @return array
 */
function _kapi_manager_getProductsSchema() {
  $schema = array(
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
      'workshop_id' => array(
        'type'        => 'int',
        'unsigend'    => TRUE,
        'not null'    => TRUE,
        'description' => t('The workshop ID where product is manufactured'),
      ),
    ),
    'primary key' => array('id'),
    'unique key' => array(
      'name' => array('name'),
    ),
    'index' => array(
      'idx_name' => array('name'),
    ),
    'foreign_keys' => array(
      'table'   => 'kapi_manager_workshops',
      'columns' => array(
        'workshop_id' => 'id',
      ),
    )
  );
  return $schema;
}

/*
 * This function returns an array description for the dependencies schema.
 *
 * @return array
 */
function _kapi_manager_getDependenciesSchema() {
  $schema = array(
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
        'product_id'    => 'id',
        'dependency_id' => 'id',
      ),
    ),
    'index' => array(
      'idx_product_id' => array('product_id'),
    )
  );
  return $schema;
}

/*
 * This function returns an array description for the workshops schema.
 *
 * @return array
 */
function _kapi_manager_getWorkshopSchema() {
  $schema = array(
    'description' => t('Stores workshop ID\'s and names'),
    'fields' => array(
      'id' => array(
        'type'        => 'serial',
        'unsigend'    => TRUE,
        'not null'    => TRUE,
        'description' => t('The workshop ID to indicate products by numbers'),
      ),
      'name' => array(
        'type'        => 'varchar',
        'length'      => '35',
        'not null'    => TRUE,
        'description' => t('The human readable name of the workshop'),
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
  return $schema;
}


