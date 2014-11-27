Commerce Order Counter Custom
==============================

> Provide custom counters for [Commerce Order Counter](https://www.drupal.org/project/commerce_order_counter).

**WARNING** This is not modular yet, it's tightly set to CountryPrefixed and
hardcoded to use shipping address country. Feel free to improve :)

## Counters

- PrefixedCommerceOrderCounter, a prefixed counter which uses `F` as the default (F1, F2).
- CountryPrefixedCommerceOrderCounter, a country code prefixed counter (EN1,
  EN2, SE1). Determined by the order shipping address.

## Installation

Enable the module and set the `CommerceOrderCounterClass` variable to use the
class you desire in `settings.php`.

```
$conf['CommerceOrderCounterClass'] = 'CountryPrefixedCommerceOrderCounter';
```

## FAQ

### Can I use an order number as an invoice id?

Yes, you should disable the _Increment the order counter upon checkout
completion_ rule created by _Commerce Order Counter_ and instead create your
own rule which is triggered on _When an order is first paid in full_. This way
the invoice id isn't incremented for purchases never completed.

### I want to restrict country code to certain countries

Check `commerce_order_counter_custom.api.php`.

### I want to change the default prefixes, how?

Check the source, there are `variable_get`s you can configure with `$conf` in
your `settings.php`.

