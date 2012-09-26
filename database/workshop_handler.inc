<?php
/**
 * @file
 *   A database handler for workshop related database operations.
 */


/**
 * This function returns a ResultSet containing 'id and 'name' of all workshops.
 */
function _kapi_manager_get_workshops() {
  $query = db_select('kapi_manager_workshops', 'w')
    ->fields('w', array('id', 'name'));
  return $query->execute();
}

/**
 * This function returns a ResultSet containing 'name' of all workshops.
 */
function _kapi_manager_get_workshop_names() {
  $query = db_select('kapi_manager_workshops', 'w')
    ->fields('w', array('name'));
  return $query->execute();
}

/**
 * This function returns true if a workshop with given name already exists in
 * database, else false will be returned.
 *
 * @param workshop_name
 *   string containing the workshop name
 * @return boolean
 */
function _kapi_manager_exists_workshop($workshop_name) {
  $query = db_select('kapi_manager_workshops', 'w')
    ->fields('w', array('name'))
    ->condition('name', $workshop_name, 'LIKE')
    ->execute()
    ->fetchField();
  if ($query === $workshop_name) {
    return TRUE;
  }
  return FALSE;
}

/*
 * @todo Documentation
 */
function _kapi_manager_save_workshop($workshop_name) {
  // @todo implement this function

}