<?php
/**
 * @file
 *   This file provides functions to initialize the tables of kapi_manager modul
 *   with default values.
 */

/**
 * This function will be called during modul installation to
 * create the default database entries.
 *
 * @return boolean
 */
function kapi_manager_init_db() {
  _kapi_manager_init_workshops();
  _kapi_manager_init_products();
  _kapi_manager_init_dependencies();
  return _kapi_manager_check_init_db();
}

/**
 * This function does some database checks after initialization.
 *
 * @return boolean
 */
function _kapi_manager_check_init_db() {
  $workshops_sane = (db_query('SELECT COUNT(id) FROM {kapi_manager_workshops}')->fetchField() == 17);
  $products_sane = (db_query('SELECT COUNT(id) FROM {kapi_manager_products}')->fetchField() == 93);
  $dependencies_sane = (db_query('SELECT COUNT(product_id) FROM {kapi_manager_dependencies}')->fetchField() == 230);
  $db_sane = $workshops_sane && $products_sane && $dependencies_sane;
  if ($db_sane) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * This function creates the default values for the workshops table.
 */
function _kapi_manager_init_workshops() {
  $workshops = array(
    'farm', 'brewery', 'printing press', 'fisching hut',
    'goldsmith', 'lumberjack', 'trade caravan', 'manufactory',
    'mill bakery', 'fruit picker', 'well', 'butchery',
    'joinery', 'stone pit', 'cattle farm', 'armourer',
    'weaving mill',
  );
  foreach ($workshops as $workshop) {
    db_insert('kapi_manager_workshops')
      ->fields(array('name' => $workshop))
      ->execute();
  }
}

/**
 * This function creates the default values for the products table.
 */
function _kapi_manager_init_products() {
  $products = array(
    array('water', 11), array('wood', 6), array('stones', 14),
    array('tools', 8), array('bees wax', 1), array('bread', 1),
    array('flax', 1), array('grain', 1), array('honey', 1), array('cheese', 1),
    array('candles', 1), array('herbs', 1), array('beets', 1), array('beer', 2),
    array('pear brandy', 2), array('mead', 2), array('cherry brandy', 2),
    array('schnapps', 2), array('wine', 2), array('bibles', 3),
    array('books', 3), array('pamphlets', 3), array('parchments', 3),
    array('quills', 3), array('fish', 4), array('lamp oil', 4),
    array('mussels', 4), array('pearls', 4), array('smoked fish', 4),
    array('fish oil', 4), array('gold jewellery', 5), array('saint statues', 5),
    array('mussel necklaces', 5), array('pearl necklaces', 5),
    array('silver jewellery', 5), array('coal', 6), array('pitch', 6),
    array('spices', 7), array('salt', 7), array('silk', 7), array('incense', 7),
    array('boats', 8), array('iron', 8), array('carts', 8), array('casks', 8),
    array('candied apples', 9), array('gingerbread', 9), array('flour', 9),
    array('syrup', 9), array('sweet bread', 9), array('apples', 10),
    array('berries', 10), array('pears', 10), array('cherries', 10),
    array('nuts', 10), array('grapes', 10), array('roast goose', 12),
    array('salt meat', 12), array('dried meat', 12), array('venison', 12),
    array('benches', 13), array('shelves', 13), array('cabinets', 13),
    array('chairs', 13), array('tables', 13), array('iron ore', 14),
    array('gold', 14), array('saltpetre', 14), array('silver', 14),
    array('eggs', 15), array('geese', 15), array('chicken', 15),
    array('milk', 15), array('horses', 15), array('pigs', 15), array('deer', 15),
    array('wool', 15), array('goats', 15), array('arquebuses', 16),
    array('halberds', 16), array('leather doublet', 16),
    array('suits of armour', 16), array('shields', 16), array('war horses', 16),
    array('swords', 16), array('eiderdowns', 17), array('clothes', 17),
    array('raiments', 17), array('leather', 17), array('nets', 17),
    array('shoes', 17), array('carpets', 17), array('drapery', 17),
  );
  foreach ($products as $product) {
    db_insert('kapi_manager_products')
      ->fields(array(
        'name'        => $product[0],
        'workshop_id' => $product[1],
      ))
      ->execute();
  }
}

/**
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
  foreach ($dependencies as $dependency) {
    db_insert('kapi_manager_dependencies')
      ->fields(array(
        'product_id'    => $dependency[0],
        'dependency_id' => $dependency[1],
        'factor'        => $dependency[2],
      ))
      ->execute();
  }
}
