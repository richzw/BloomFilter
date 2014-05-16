Bloom_Filter
================

Implement Bloom Filter in C++, initial version now.

##Introduction
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

For details, please refer to http://en.wikipedia.org/wiki/Bloom_filter

User need to determine the number of element n that stored in bloom filter and misjudgment rate p.
then the bit number m of bit array can be computed by m = -(n*lnp)/(ln2)^2, 
also the number of hash functions k = (ln2*m)/n.

## Usage

+ `Web cache sharing`. Collaborating Web caches use Bloom filters as compact representations for the local set of cached files.  Each cache periodically broadcasts its summary to all other members of the distributed cache.  Using all summaries received, a cache node has a (partially outdated, partially wrong) global image about the set of files stored in the aggregated cache. 
+ `Query filtering and routing`. Bloom filters are used as summaries for the set of services offered by a node.  Summaries are sent upwards in the hierarchy and aggregated.  A query is a description for a specific service, also represented as a Bloom filter.  Thus, when a member node of the hierarchy generates/receives a query, it has enough information at hand to decide where to forward the query: downward, to one of its descendants (if a solution to the query is present in the filter for the corresponding node), or upward, toward its parent.
+ `Compact representation of a differential file`.  A differential file contains a batch of database records to be updated.  For performance reasons the database is updated only periodically or when the differential file grows above a certain threshold.  However, in order to preserve integrity, each reference/query to the database has to access the differential file to see if a particular record is scheduled to be updated.  To speed-up this process, with little memory and computational overhead, the differential file is represented as a Bloom filter.
+ `Free text searching`.  Basically, the set of words that appear in a text is succinctly represented using a Bloom filter


##TODO list:

so the hash function is the key part of bloom filter. what I am going to do as following:

1. Use MD5 hash function.    (Done)
2. Use MPQ hash function.    (Done)  
3. Counting bloom filter.
4. Add test.
5. 


##Reference:

 * [http://wiki.devklog.net/index.php?title=The_MoPaQ_Archive_Format]
 * [http://en.wikipedia.org/wiki/MPQ]
 * [http://en.wikipedia.org/wiki/Bloom_filter]
    
