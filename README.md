# SparseBitmap
The sparse bitmap is an on-disk bitmap structure with an optional
XA capable transaction log, for safe updates against the structure.
XA gives the capability of making changes to multiple bitmaps atomically.

Goals:
The sparse bitmap is designed to be an index structure for mid to low
cardinality columns.  It features random-access RLE compression, thus
it is only effective when there are runs of bits.

An index entry marks a single bit in the index, which must be written
to disk.  In a unique column, only one bit would be marked in each
bitmap index.  By itself this is not a problem but for the fact that
the disk stores data in sectors, which means that between 512 and 4096
bytes are written to disk for that single bit.  Since medium to low
cardinality columns typically have runs of data they will work fine.  
Low cardinality columns, or columns that have long runs work best.

Theory:
Many filesystems support sparse file.  In a sparse file, sections of 
unallocated space use only a small amount of meta data space on disk
instead of zeros.  For example, a sparse file that is 1GB in size, but
contains only 4K of data, will take up only 4K on disk.  Any data read
from the sparse area is read as zeros, and when data is written to a
sparse area, it automatically materialized as real data in the file.

Modern operating systems make it possible to return a range of bytes
back to the disk using the fallocate() function, and the sparse
bitmaps takes advantage of this.  If a block of bits is set to all
zero values, a hole will be punched for the block if the operating
system has that capability.

## On disk format
The sparse bitmap consists of a sparse file on disk, and a log file.

