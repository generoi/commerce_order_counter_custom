<?php

/**
 * @file
 * A CommerceOrderCounter which uses a prefixed number. This is designed so
 * that the prefix can simply be changed and this begin a new counter.
 */

/**
 * Default prefix for the PrefixedCommerceOrderCounter class.
 */
define('COMMERCE_ORDER_COUNTER_CUSTOM_DEFAULT_PREFIX', 'F');

/**
 * Implements the CommerceOrderCounter interface.
 */
class PrefixedCommerceOrderCounter implements CommerceOrderCounter {

  /**
   * The setter for the class.
   *
   * @see CommerceOrderCounterInterface
   */
  public static function set($counter_value) {
    list($counter_prefix, $counter_number) = preg_split('/(?=\d)/', $counter_value, 2);
    $id = "commerce_order_counter_custom_$counter_prefix";

    variable_set($id, self::unique($counter_value));
    // Get the current value after setting it up.
    $default_counter = $counter_prefix . COMMERCE_ORDER_COUNTER_DEFAULT_BASE_VALUE;
    $counter = variable_get($id, $default_counter);

    // Write to the watchdog the setting of the order number.
    watchdog('commerce_order_counter', 'Commerce Order number set to @counter.',
             array('@counter' => $counter)
    );

    return $counter;
  } // commerce_order_counter_set

  /**
   * The getter for the class.
   *
   * @see CommerceOrderCounterInterface
   */
  public static function get() {
    $prefix = variable_get('commerce_order_counter_custom_prefix', COMMERCE_ORDER_COUNTER_CUSTOM_DEFAULT_PREFIX);
    $id = "commerce_order_counter_custom_$prefix";
    $default_counter = $prefix . COMMERCE_ORDER_COUNTER_DEFAULT_BASE_VALUE;
    return variable_get($id, $default_counter);
  } // commerce_order_counter_get

  /**
   * Implementation of the unique operator.
   *
   * @see CommerceOrderCounterInterface
   */
  public static function unique($updated_counter) {
    $counter = $updated_counter;
    // We check the value of the counter and keep incrementing until the value
    // is unique.
    while (
      db_query('SELECT order_number FROM {commerce_order} WHERE order_number = :counter',
               array(':counter' => $counter))
      ->fetchField()) {
      // Remove prefix and increment the number.
      list($counter_prefix, $counter_number) = preg_split('/(?=\d)/', $counter, 2);
      $counter_number++;
      $counter = $counter_prefix . $counter_number;
    }

    return $counter;
  } // unique

}
