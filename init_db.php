<?php

/*
 * This function will be called during modul installation to
 * create the default database entries.
 */
function kapi_manager_init_db() {
  _kapi_manager_init_products();
}


/*
 * This function creates the default values for the products table
 */
function _kapi_manager_init_products() {
  $table = 'kapi_manager_products';
  $record = new stdClass();
  $record->name = t('water');
  drupal_write_record($table, $record);
}
