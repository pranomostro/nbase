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
* fac
* fib
* leyland

Present:

* factor: like factor(1). To compile it, type `gcc -lpthread -lgmp -o factor factor.c libutil.a`. The gmp dependency will be removed.

Planned:

* goldbach [-a] [NUMS]: accept an even number, prints a of all (if called with -a)
	primes that add up to the given number. Pairs are separated by " ", lists
	of pairs are separated by ":"
* hamming [-l NUM]: print all/the first NUM hamming numbers, sorted ascending
* isprime [NUMS]: print "prime" and "nonprime" if a number from the arguments/input
* primes [N[-M]]: print all primes up to N or from N to M

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
