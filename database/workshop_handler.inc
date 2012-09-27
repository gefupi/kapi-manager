<?php
/**
 * @file
 *   A database handler for workshop related database operations.
 */


/**
 * This function is returns a ResultSet containing all workshops from db.
 */
function _kapi_manager_db_get_workshops() {
  $query = db_select('kapi_manager_workshops', 'w')
    ->fields('w', array('id', 'name'));
  return $query->execute();
}

/**
 * This function returns true if a workshop with given name already exists in
 * database, else false will be returned.
 *
 * @param name
 *   string containing the workshop name
 * @return boolean
 */
function _kapi_manager_db_exists_workshop($name) {
  $query = db_select('kapi_manager_workshops', 'w')
    ->fields('w', array('name'))
    ->condition('name', $name, 'LIKE')
    ->execute()
    ->fetchField();
  if ($query === $name) {
    return TRUE;
  }
  return FALSE;
}

/**
 * This function updates the workshop entry in db.
 *
 * @param old_name
 *   the old workshop name
 * @para new_name
 *   the new workshop name
 */
function _kapi_manager_db_update_workshop($old_name, $new_name) {
  $num_updated = db_update('kapi_manager_workshops')
    ->fields(array('name' => $new_name))
    ->condition('name', $old_name, '=')
    ->execute();
  return ($num_updated == 1);
}

/**
 * This function inserts a workshop with given name into db table.
 *
 * @para name
 *   Name of the workshop
 */
function _kapi_manager_db_insert_workshop($name) {
  db_insert('kapi_manager_workshops')
    ->fields(array('name' => $name))
    ->execute();
}

/**
 * This function returns the name of the workshop with given ID.
 *
 * @para id
 *   ID of the workshop
 * @return string
 */
function _kapi_manager_db_get_workshop_name($id) {
  return db_select('kapi_manager_workshops', 'w')
    ->fields('w', array('name'))
    ->condition('id', $id, 'LIKE')
    ->execute()
    ->fetchField();
}
