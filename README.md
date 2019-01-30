Base utilities for numbers
===========================

nbase contains some programs meant to accompany sbase and ubase with some
utilities meant to deal with numbers, using libzahl. This includes factoring, checking
primality, leyland numbers, collatz sequences and more.

For more information on individual utilities, refer to the man-pages.

Utilities
---------

* collatz: print collatz sequences
* fact: compute factorials
* fib: compute fibonacci numbers
* leyland: print the leyland numbers
* isprime: check primality of the input

Installation
------------

	make install

and

	make uninstall

for installation and deinstallation each.

Thanks
======

Thanks to [maandree](https://github.com/maandree) for
[libzahl](http://git.suckless.org/libzahl) that makes it possible to
write something like this in a suckless manner.

License
=======

The [MIT/X11 license](./LICENSE).
