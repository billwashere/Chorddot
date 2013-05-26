Chorddot
========

Chord DHT Image generation using graphviz's circo

Usage
-----
`chorddot <number of peers> <available peer as number..>`
Example
`./chorddot 32 1 4 9 11 14 18 20 21 28 | circo -Tpng > chord.png`
It will create a Chord size 32 (0...31).
It has node 1, 4, 9, 11, 14, 18, 20, 21, and 28 that has been added.
