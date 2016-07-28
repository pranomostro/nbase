Base utilities for numbers
===========================

nbase contains some programs meant to
accompany sbase and ubase with some
utilities meant to deal with numbers.
This include factoring, checking primality,
leyland numbers and collatz sequences and
probably a bit more.

These utilities are built with libzahl,
which means they don't have any arbitrary
limits.

For more information, refer to the man-pages.

Roadmap
-------

1. Write all programs as simple as possible, but not optimized.
2. Write the documentation (man-pages).
3. Remove all possible arbitrary limits.
4. Tune the programs (use smarter algorithms, cache results, ...).

At the moment, this is still bare 1.

Utilities
---------

Present:

* collatz: program that prints the collatz sequence for arguments/input
* leyland: program that prints the leyland numbers, in ascending order

Planned:

* leyland does not have to save the z_t's, they are completely unneeded. Also: use queue.h
* primes
* isprime
* hamming
* goldbach
* factor

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
