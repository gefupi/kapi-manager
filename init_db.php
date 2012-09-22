<?php

/*
 * This function will be called during modul installation to
 * create the default database entries.
 */
function kapi_manager_init_db() {
//  _kapi_manager_init_products();

  return _kapi_manager_check_init_db();
}


/*
 * This function does some database checks after initialization
 */
function _kapi_manager_check_init_db() {
  // TODO
  $product_count = db_query('SELECT COUNT(name) FROM {kapi_manager_products}')->fetchField();
  $dependency_count = db_query('SELECT COUNT(product_id) FROM {kapi_manager_dependencies}')->fetchField();
  if (($product_count == 93) && ($dependency_count == 230)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/*
 * This function creates the default values for the products table
 */
function _kapi_manager_init_products() {
  // TODO: use english product names
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
