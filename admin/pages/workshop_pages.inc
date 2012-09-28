<?php
/**
 * @file
 * This file provides the pages used in workshop administration context.
 */
 
/**
 * This function implements the page listing all workshops.
 *
 * @return
 *   An array containing the page elements to be displayed in the list workshops
 *   page.
 */
function kapi_manager_list_workshops_page() {
  drupal_set_title(t('Workshop'));
  module_load_include('inc', 'kapi_manager', 'database/workshop_handler');
  $result = _kapi_manager_db_get_workshops();
  $rows = array();
  foreach ($result as $workshop) {
    $rows[] = array(
      array('data' => $workshop->name, ),
      array('data' => l('edit', "kapi_manager/admin/workshops/$workshop->id/edit"), ),
      array('data' => l('delete', "kapi_manager/admin/workshops/$workshop->id/delete"), ),
    );
  }
  $header = array(
		  array('data' => 'Name', 'align' => 'center', ),
    array('data' => 'Operations', 'align' => 'center', 'colspan' => 2, ),
  );
  return theme('table', array('header' => $header, 'rows' => $rows));
}
