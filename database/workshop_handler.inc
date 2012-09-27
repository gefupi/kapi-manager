<?php
/**
 * @file
 *   A database handler for workshop related database operations.
 */


/**
 * This function is returns a ResultSet containing all workshops from db.
 */
function _kapi_manager_get_workshops() {
  $query = db_select('kapi_manager_workshops', 'w')
    ->fields('w', array('id', 'name'));
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
function _kapi_manager_update_workshop($old_name, $new_name) {
  $num_updated = db_update('kapi_manager_workshops') // Table name no longer needs {}
    ->fields(array('name' => $new_name))
    ->condition('name', $old_name, '=')
    ->execute();
  return ($num_updated == 1);
}

/*
 * @todo Documentation
 */
function _kapi_manager_save_workshop($workshop_name) {
  // @todo implement this function

}

/*
 * @todo Documentation
 */
function _kapi_manager_get_workshop_name($workshop_id) {
  return db_select('kapi_manager_workshops', 'w')
    ->fields('w', array('name'))
    ->condition('id', $workshop_id, 'LIKE')
    ->execute()
    ->fetchField();
}

