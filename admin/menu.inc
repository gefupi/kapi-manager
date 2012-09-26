<?php
/*
 * @file
 *   This file provides the menu items of the admin section in kapi_menu.
 */

/*
 * TODO: Dokumentation
 */
function _kapi_manager_admin_menu(&$items, $admin_access) {
  $items['kapi_manager/admin'] = array(
    'title' => 'Administration',
    'page callback' => 'kapi_manager_test_page',
    'access arguments' => $admin_access,
    'type' => MENU_NORMAL_ITEM,
    'menu_name' => 'kapi_manager',
  );

  _kapi_manager_admin_product_menu($items, $admin_access);
}

/*
 * TODO: Dokumentation
 */
function _kapi_manager_admin_product_menu(&$items, $admin_access) {
  $items['kapi_manager/admin/products'] = array(
    'title' => 'Products',
    'page callback' => 'kapi_manager_list_products_page',
    'access arguments' => $admin_access,
    'type' => MENU_NORMAL_ITEM,
    'menu_name' => 'kapi_manager',
  );
  $items['kapi_manager/admin/products/list'] = array(
    'title' => 'list',
    'access arguments' => $admin_access,
    'type' => MENU_DEFAULT_LOCAL_TASK,
    'menu_name' => 'kapi_manager',
    'wight' => 0,
  );

  $items['kapi_manager/admin/products/edit'] = array(
    'title' => 'edit',
    'page callback' => 'kapi_manager_edit_products_page',
    'access arguments' => $admin_access,
    'type' => MENU_LOCAL_TASK,
    'menu_name' => 'kapi_manager',
    'weight' => 1,
  );

  $items['kapi_manager/admin/products/add'] = array(
    'title' => 'add a product',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('kapi_manager_add_product_form'),
    'access arguments' => $admin_access,
    'type' => MENU_LOCAL_ACTION,
    'menu_name' => 'kapi_manager',
  );
}
