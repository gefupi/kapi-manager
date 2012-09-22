<?php

/*
 * This function will be called during modul installation to
 * create the default database entries.
 */
function kapi_manager_init_db() {
  _kapi_manager_init_products();

  return _kapi_manager_check_init_db();
}


/*
 * This function does some database checks after initialization
 */
function _kapi_manager_check_init_db() {
  // TODO
  $product_count = db_query('SELECT COUNT(name) FROM {kapi_manager_products}')->fetchField();
  if ($product_count == 93) {
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
    'Wasser', 'Holz', 'Stein', 'Werkzeug', 'Bienenwachs', 'Brote', 'Flachs',
    'Getreide', 'Honig', 'Käse', 'Kerzen', 'Kräuter', 'Rüben', 'Bier',
    'Birnenschnaps', 'Met', 'Kirschwasser', 'Schnaps', 'Wein', 'Bibeln',
    'Bücher', 'Pamphlete', 'Pergamente', 'Schreibfedern', 'Fische', 'Lampenöl',
    'Muscheln', 'Perlen', 'Räucherfisch', 'Tran', 'Goldgeschmeide',
    'Heiligenstatuen', 'Muschelketten', 'Perlenketten', 'Silbergeschmeide',
    'Kohle', 'Pech', 'Gewürze', 'Salz', 'Seide', 'Weihrauch', 'Boote', 'Eisen',
    'Fuhrwerke', 'Fässer', 'Kandierter Apfel', 'Lebkuchen', 'Mehl', 'Sirup',
    'Süßes Brot', 'Äpfel', 'Beeren', 'Birnen', 'Kirschen', 'Nüsse', 'Trauben',
    'Gänsebraten', 'Pökelfleisch', 'Trockenfleisch', 'Wildbret', 'Bänke',
    'Regale', 'Schränke', 'Stühle', 'Tische', 'Eisenerz', 'Gold', 'Salpeter',
    'Silber', 'Eier', 'Gänse', 'Hühner', 'Milch', 'Pferde', 'Schweine', 'Wild',
    'Wolle', 'Ziegen', 'Arkebusen', 'Hellebarde', 'Lederwams', 'Rüstungen',
    'Schild', 'Schlachtrösser', 'Schwert', 'Daunenbetten', 'Gewänder',
    'Kleidung', 'Leder', 'Netze', 'Schuhe', 'Teppiche', 'Tuch',
  );
  $table = 'kapi_manager_products';
  foreach ($products as $product) {
    $record = new stdClass();
    // TODO use translation function
    // $record->name = t($product);
    $record->name = $product;
    drupal_write_record($table, $record);
  }
}
