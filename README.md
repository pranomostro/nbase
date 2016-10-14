Base utilities for numbers
===========================

nbase contains some programs meant to accompany sbase and ubase with some
utilities meant to deal with numbers.  This includes factoring, checking
primality, leyland numbers, collatz sequences and probably a bit more.

These utilities are built with libzahl, which means they don't have any
arbitrary limits.

For more information, refer to the man-pages.


Aim
---

* no arbitrary limits
* programs as fast as possible

Utilities
---------

Finished:

* collatz [NUMS]: program that prints the collatz sequence for arguments/input
* fac [NUMS]: print the factorial of NUMS/or the input lines
* leyland -l [LIM]: program that prints the leyland numbers, in ascending order

Present:

* factor [NUMS]: like factor(1). To compile it, type `gcc -lpthread -lgmp -o factor factor.c libutil.a`.
	The gmp dependency will be removed

Planned:

* fib [NUMS]: print the nth fibonacci numbers
* goldbach [-a] [NUMS]: accept an even number, prints a of all (if called  with -a)
	primes that add up to the given number. Pairs are separated by " ", lists
	of pairs are separated by ":"
* hamming [-l NUM]: print all/the first NUM hamming numbers, sorted ascending
* isprime [NUMS]: print "prime" and "nonprime" if a number from the arguments/input
* primes [N[-M]]: print all primes up to N or from N to M

Requirements
------------

A standard C99 compiler and a C standard
library, as well as make. That's it.

Installation
------------

	make install

and

	make uninstall

for installation and deinstallation each.

Thanks
======

Thanks to [maandree](https://github.com/maandree) for
[libzahl](http://git.suckless.org/libzahl) that makes it
possible to write something like this in a suckless manner.

License
=======

See the file ./COPYING.
