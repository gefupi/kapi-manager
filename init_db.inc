<?php
/*
 * @file
 *   This file provides functions to initialize the tables of kapi_manager modul
 *   with default values.
 */


/*
 * This function will be called during modul installation to
 * create the default database entries.
 *
 * @return boolean
 */
function kapi_manager_init_db() {
  _kapi_manager_init_products();
  _kapi_manager_init_dependencies();

  return _kapi_manager_check_init_db();
}


/*
 * This function does some database checks after initialization.
 *
 * @return boolean
 */
function _kapi_manager_check_init_db() {
  $product_count = db_query('SELECT COUNT(name) FROM {kapi_manager_products}')->fetchField();
  $dependency_count = db_query('SELECT COUNT(product_id) FROM {kapi_manager_dependencies}')->fetchField();
  if (($product_count == 93) && ($dependency_count == 230)) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/*
 * This function creates the default values for the products table.
 */
function _kapi_manager_init_products() {
  $products = array(
    'water', 'wood', 'stones', 'tools', 'bees wax', 'bread', 'flax',
    'grain', 'honey', 'cheese', 'candles', 'herbs', 'beets', 'beer',
    'pear brandy', 'mead', 'cherry brandy', 'schnapps', 'wine', 'bibles',
    'books', 'pamphlets', 'parchments', 'quills', 'fish', 'lamp oil',
    'mussels', 'pearls', 'smoked fish', 'fish oil', 'gold jewellery',
    'saint statues', 'mussel necklaces', 'pearl necklaces', 'silver jewellery',
    'coal', 'pitch', 'spices', 'salt', 'silk', 'incense', 'boats', 'iron',
    'carts', 'casks', 'candied apples', 'gingerbread', 'flour', 'syrup',
    'sweet bread', 'apples', 'berries', 'pears', 'cherries', 'nuts', 'grapes',
    'roast goose', 'salt meat', 'dried meat', 'venison', 'benches',
    'shelves', 'cabinets', 'chairs', 'tables', 'iron ore', 'gold', 'saltpetre',
    'silver', 'eggs', 'geese', 'chicken', 'milk', 'horses', 'pigs', 'deer',
    'wool', 'goats', 'arquebuses', 'halberds', 'leather doublet', 'suits of armour',
    'shields', 'war horses', 'swords', 'eiderdowns', 'clothes',
    'raiments', 'leather', 'nets', 'shoes', 'carpets', 'drapery',
  );
  $table = 'kapi_manager_products';
  foreach ($products as $product) {
    $record = new stdClass();
    $record->name = t($product);
    drupal_write_record($table, $record);
  }
}


/*
 * This function creates the default values for the products table
 */
function _kapi_manager_init_dependencies() {
  $dependencies = array(
    array(2, 1, 20.0),   array(3, 4, 0.5),    array(3, 1, 0.5),    array(4, 2, 0.1),
    array(4, 43, 0.1),   array(5, 12, 5.0),   array(6, 1, 1.0),    array(6, 8, 2.0),
    array(7, 1, 10.0),   array(8, 1, 2.0),    array(9, 12, 5.0),   array(10, 73, 1.0),
    array(10, 1, 1.0),   array(10, 39, 0.05), array(11, 5, 0.2),   array(11, 4, 0.1),
    array(11, 7, 0.1),   array(12, 1, 5.0),   array(13, 1, 1.0),   array(14, 1, 2.0),
    array(14, 8, 1.0),   array(14, 45, 0.1),  array(15, 53, 10.0), array(15, 1, 10.0),
    array(15, 2, 2.0),   array(16, 1, 2.0),   array(16, 9, 2.0),   array(16, 45, 0.1),
    array(17, 54, 10.0), array(17, 1, 10.0),  array(17, 2, 2.0),   array(18, 1, 10.0),
    array(18, 12, 5.0),  array(18, 45, 0.1),  array(19, 1, 5.0),   array(19, 56, 20.0),
    array(19, 45, 0.1),  array(20, 2, 5.0),   array(20, 1, 2.0),   array(20, 4, 0.1),
    array(20, 67, 0.1),  array(20, 89, 1.0),  array(21, 2, 4.0),   array(21, 1, 2.0),
    array(21, 4, 0.1),   array(22, 2, 2.0),   array(22, 1, 1.0),   array(22, 4, 0.1),
    array(23, 2, 1.0),   array(23, 1, 0.5),   array(23, 4, 0.1),   array(24, 71, 0.1),
    array(24, 4, 0.1),   array(25, 42, 0.05), array(25, 90, 0.1),  array(26, 30, 0.1),
    array(26, 36, 0.1),  array(27, 42, 0.1),  array(27, 4, 0.1),   array(28, 42, 0.1),
    array(28, 4, 0.2),   array(29, 25, 1.0),  array(29, 36, 0.5),  array(29, 12, 0.3),
    array(30, 25, 0.1),  array(30, 1, 5.0),   array(31, 67, 5.0),  array(31, 4, 5.0),
    array(31, 28, 1.0),  array(32, 67, 1.0),  array(32, 69, 1.0),  array(32, 2, 2.0),
    array(32, 4, 5.0),   array(33, 27, 10.0), array(33, 67, 0.1),  array(33, 4, 1.0),
    array(34, 28, 20.0), array(34, 67, 0.1),  array(34, 4, 1.0),   array(35, 69, 5.0),
    array(35, 4, 5.0),   array(36, 2, 2.0),   array(37, 1, 2.0),   array(37, 2, 5.0),
    array(38, 44, 0.1),  array(38, 74, 0.1),  array(38, 59, 0.5),  array(38, 12, 2.0),
    array(39, 44, 0.1),  array(39, 74, 0.1),  array(39, 6, 5.0),   array(39, 92, 0.5),
    array(40, 44, 0.1),  array(40, 74, 0.1),  array(40, 59, 0.5),  array(40, 9, 1.0),
    array(41, 44, 0.1),  array(41, 74, 0.1),  array(41, 59, 0.5),  array(41, 18, 1.0),
    array(42, 2, 4.0),   array(42, 37, 1.0),  array(42, 4, 2.0),   array(43, 66, 2.0),
    array(43, 36, 1.0),  array(44, 2, 2.0),   array(44, 43, 0.5),  array(44, 4, 1.0),
    array(45, 2, 0.5),   array(45, 43, 0.1),  array(45, 4, 0.2),   array(46, 51, 1.0),
    array(46, 49, 1.0),  array(47, 48, 2.0),  array(47, 38, 0.1),  array(47, 1, 10.0),
    array(47, 49, 1.0),  array(47, 9, 0.1),   array(48, 8, 1.0),   array(48, 3, 0.05),
    array(49, 13, 2.0),  array(49, 1, 2.0),   array(50, 48, 3.0),  array(50, 73, 2.0),
    array(50, 9, 1.0),   array(50, 49, 1.0),  array(50, 56, 1.0),  array(51, 1, 10.0),
    array(52, 1, 10.0),  array(53, 1, 10.0),  array(54, 1, 10.0),  array(55, 1, 10.0),
    array(56, 1, 10.0),  array(57, 71, 1.0),  array(57, 12, 0.3),  array(57, 51, 3.0),
    array(58, 75, 0.2),  array(58, 39, 0.5),  array(58, 12, 0.5),  array(58, 38, 0.1),
    array(59, 75, 0.2),  array(59, 12, 0.5),  array(60, 76, 0.2),  array(60, 12, 0.5),
    array(61, 2, 4.0),   array(61, 4, 1.0),   array(61, 43, 0.1),  array(61, 89, 2.0),
    array(62, 2, 3.0),   array(62, 4, 1.0),   array(62, 43, 0.1),  array(63, 2, 10.0),
    array(63, 4, 2.0),   array(63, 43, 0.2),  array(64, 2, 3.0),   array(64, 4, 1.0),
    array(64, 43, 0.1),  array(65, 2, 5.0),   array(65, 4, 1.0),   array(65, 43, 0.1),
    array(66, 1, 10.0),  array(67, 4, 10.0),  array(67, 1, 50.0),  array(68, 4, 5.0),
    array(68, 1, 5.0),   array(68, 2, 5.0),   array(69, 4, 7.0),   array(69, 1, 30.0),
    array(70, 72, 0.1),  array(70, 8, 0.1),   array(70, 1, 1.0),   array(71, 1, 15.0),
    array(71, 8, 4.0),   array(72, 1, 20.0),  array(72, 8, 5.0),   array(73, 1, 0.1),
    array(73, 78, 0.1),  array(73, 13, 0.1),  array(74, 1, 200.0), array(74, 13, 300.0),
    array(75, 1, 30.0),  array(75, 13, 40.0), array(76, 1, 30.0),  array(76, 13, 50.0),
    array(77, 1, 0.1),   array(77, 13, 1.0),  array(78, 1, 50.0),  array(78, 13, 20.0),
    array(79, 43, 2.0),  array(79, 68, 2.0),  array(79, 2, 2.0),   array(80, 43, 2.0),
    array(80, 4, 2.0),   array(80, 2, 4.0),   array(81, 89, 2.0),  array(81, 4, 2.0),
    array(81, 93, 1.0),  array(81, 1, 10.0),  array(82, 43, 5.0),  array(82, 4, 5.0),
    array(82, 67, 1.0),  array(83, 2, 3.0),   array(83, 43, 1.0),  array(83, 36, 1.0),
    array(83, 4, 2.0),   array(84, 74, 1.0),  array(84, 43, 5.0),  array(84, 89, 5.0),
    array(85, 43, 3.0),  array(85, 4, 3.0),   array(85, 69, 1.0),  array(86, 71, 20.0),
    array(86, 4, 2.0),   array(86, 93, 1.0),  array(87, 77, 10.0), array(87, 40, 0.1),
    array(88, 77, 7.0),  array(88, 7, 10.0),  array(89, 78, 1.0),  array(89, 2, 2.0),
    array(89, 4, 0.2),   array(90, 7, 5.0),   array(90, 4, 0.1),   array(91, 89, 0.2),
    array(91, 2, 0.1),   array(91, 4, 0.1),   array(92, 77, 30.0), array(92, 4, 2.0),
    array(93, 77, 7.0),  array(93, 4, 0.1),
  );
  $table = 'kapi_manager_dependencies';
  foreach ($dependencies as $dependency) {
    $record = new stdClass();
    $record->product_id = $dependency[0];
    $record->dependency_id = $dependency[1];
    $record->factor     = $dependency[2];
    drupal_write_record($table, $record);
  }
}
