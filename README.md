Bloom-FIiter-C--
================

Implement Bloom Filter in C++, initial version now.

An empty Bloom filter is a bit array of m bits, all set to 0. There must also be k different hash functions defined,
each of which maps or hashes some set element to one of the m array positions with a uniform random distribution.

To add an element, feed it to each of the k hash functions to get k array positions. 
Set the bits at all these positions to 1.

To query for an element (test whether it is in the set), feed it to each of the k hash functions to get k array positions. 
If any of the bits at these positions are 0, the element is definitely not in the set – 
if it were, then all the bits would have been set to 1 when it was inserted. 
If all are 1, then either the element is in the set, or the bits have by chance been set to 1 during the insertion of other elements,
resulting in a false positive. In a simple bloom filter, there is no way to distinguish between the two cases, 
but more advanced techniques can address this problem.
