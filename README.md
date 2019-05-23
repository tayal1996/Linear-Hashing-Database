## Problem

Implement Linear Hashing (paper explained in class) to handle duplicate elimination (explained in
Output section).

## Input ​ : ​ ​ Filename,M,B (explained in Note section)

1. Inputs must be taken as command line arguments
2. Each line in the filename consists one of single integer(x) (-10^9 <= x <= 10^9).

## Output ​:

After reading every line (call it record), If record is not already present in the data structure, print it
and insert it into data structure.

## Note:

1. M denotes the number of buffers and B denotes the buffer size (M>=2 and M*B<=10^6)
2. Out of the M buffers, M-1 Buffers will be used as input buffers (which will hold the records
    from the input file), 1 buffer will be used as output buffer (holds the distinct records). If the
    output buffer gets filled, it should be flushed to the output. If the input buffers get empty, the
    next chunk of records should be read from the input file.
3. The size of B+ tree and hash table is ​ **NOT** ​ included in M.

## Compile

./linear.o filename M B
M >= 2
B >= 4

