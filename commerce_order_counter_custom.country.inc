<?php

/**
 * @file
 * A CommerceOrderCounter which uses separate country-prefixed counters that
 * all begin from 1 in the format EN01 EN02 SE01 FI01 SE02 XX01
 */

/**
 * Default prefix for the CountryPrefixedCommerceOrderCounter class.
 */
define('COMMERCE_ORDER_COUNTER_CUSTOM_DEFAULT_COUNTRY', 'XX');


/**
 * Implements the PrefixedCommerceOrderCounter interface.
 */
class CountryPrefixedCommerceOrderCounter extends PrefixedCommerceOrderCounter {

  /**
   * The getter for the class.
   *
   * @see CommerceOrderCounterInterface
   */
  public static function getPrefixed($country = FALSE) {
    // Use country if specified, otherwise use the default country prefix.
    $prefix = $country ? $country : variable_get('commerce_order_counter_custom_default_country', COMMERCE_ORDER_COUNTER_CUSTOM_DEFAULT_COUNTRY);
    // Allow modules to alter the country prefix.
    drupal_alter('commerce_order_counter_custom_country', $prefix);

    $id = "commerce_order_counter_custom_$prefix";
    $default_counter = $prefix . COMMERCE_ORDER_COUNTER_DEFAULT_BASE_VALUE;
    return variable_get($id, $default_counter);
  }

  public static function get() {
    return self::getPrefixed();
  }

}
