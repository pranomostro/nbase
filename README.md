Base utilities for numbers
===========================

nbase contains some programs meant to accompany sbase and ubase with some
utilities meant to deal with numbers, using libzahl. This includes factoring, checking
primality, leyland numbers, collatz sequences and more.

For more information on individual utilities, refer to the man-pages.

Utilities
---------

Finished:

* collatz
* fact
* fib
* leyland
* isprime

Planned:

* goldbach [-a] [NUMS]: accept an even number, prints a of all (if called with -a)
	primes that add up to the given number. Pairs are separated by " ", lists
	of pairs are separated by ":"
* hamming [-l NUM]: print all/the first NUM hamming numbers, sorted ascending
* primes [N[-M]]: print all primes up to N or from N to M
* factor [NUMS]: print the prime factors of a given number
* deterministic prime-checking methods: sieve of eratosthenes (with bit-field and list), brute force checking, sieve of atkin

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
write something like this in a suckless manner. He is also the author
of factor.c and factor.1.

License
=======

The [MIT/X11 license](./LICENSE).
