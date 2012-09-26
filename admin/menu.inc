<?php
/*
 * @file
 *   This file provides the menu items of the admin section in kapi_menu.
 */


/*
 * This functions add the 'administration' section to kapi_manager menu.
 *
 * @param items
 *   reference to an array of menu items
 * @param admin_access
 *   an array of access arguments
 */
function kapi_manager_admin_menu(&$items, $admin_access) {
  $items['kapi_manager/admin'] = array(
    'title' => 'Administration',
    'page callback' => 'kapi_manager_test_page',
    'access arguments' => $admin_access,
    'type' => MENU_NORMAL_ITEM,
    'menu_name' => 'kapi_manager',
  );

  _kapi_manager_admin_workshop_menu($items, $admin_access);
  _kapi_manager_admin_product_menu($items, $admin_access);
}

/*
 * This functions add the 'workshop' part of administration to kapi_manager
 * menu.
 *
 * @param items
 *   reference to an array of menu items
 * @param admin_access
 *   an array of access arguments
 */
function _kapi_manager_admin_workshop_menu(&$items, $admin_access) {
  $items['kapi_manager/admin/workshop'] = array(
    'title' => 'Workshop',
    'page callback' => 'kapi_manager_list_workshops_page',
    'access arguments' => $admin_access,
    'type' => MENU_NORMAL_ITEM,
    'menu_name' => 'kapi_manager',
    'weight' => 0,
  );
  $items['kapi_manager/admin/workshop/list'] = array(
    'title' => 'List',
    'access arguments' => $admin_access,
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'menu_name' => 'kapi_manager',
    'wight' => 0,
  );

  $items['kapi_manager/admin/workshop/%/edit'] = array(
    'title' => 'Edit workshop',
    'page callback' => 'kapi_manager_edit_workshop_page',
    'page arguments' => array(3),
    'access arguments' => $admin_access,
    /* 'type' => MENU_LOCAL_ACTION, */
    'type' => MENU_CALLBACK,
    'menu_name' => 'kapi_manager',
  );

  $items['kapi_manager/admin/workshop/add'] = array(
    'title' => 'Add a workshop',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('kapi_manager_add_workshop_form'),
    'access arguments' => $admin_access,
    'type' => MENU_LOCAL_ACTION,
    'menu_name' => 'kapi_manager',
    'weight' => 1,
  );

  // @todo: add delete page
}

/*
 * This functions add the 'product' part of administration to kapi_manager
 * menu.
 *
 * @param items
 *   reference to an array of menu items
 * @param admin_access
 *   an array of access arguments
 */
function _kapi_manager_admin_product_menu(&$items, $admin_access) {
  $items['kapi_manager/admin/products'] = array(
    'title' => 'Products',
    'page callback' => 'kapi_manager_list_products_page',
    'access arguments' => $admin_access,
    'type' => MENU_NORMAL_ITEM,
    'menu_name' => 'kapi_manager',
    'weight' => 1,
  );
  $items['kapi_manager/admin/products/list'] = array(
    'title' => 'List',
    'access arguments' => $admin_access,
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'menu_name' => 'kapi_manager',
    'wight' => 0,
  );

  $items['kapi_manager/admin/products/edit'] = array(
    'title' => 'Edit',
    'page callback' => 'kapi_manager_edit_products_page',
    'access arguments' => $admin_access,
    'type' => MENU_LOCAL_TASK,
    'menu_name' => 'kapi_manager',
    'weight' => 1,
  );

  $items['kapi_manager/admin/products/add'] = array(
    'title' => 'Add a product',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('kapi_manager_add_product_form'),
    'access arguments' => $admin_access,
    'type' => MENU_LOCAL_ACTION,
    'menu_name' => 'kapi_manager',
  );
}

