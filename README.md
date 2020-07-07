# SparseBitmap
The sparse bitmap is an on-disk bitmap structure with an optional
XA capable transaction log, for safe updates against the structure.
XA gives the capability of making changes to multiple bitmaps atomically.

The simple sparse bitmap is designed to be an index structure for mid to low
cardinality columns.  It features random-access RLE compression, thus
it is only effective when there are long runs of bits.

Many filesystems support sparse file.  In a sparse file, sections of 
unallocated space use only a small amount of meta data space on disk
instead of zeros.  For example, a sparse file that is 1GB in size, but
contains only 4K of data, will take up only 4K on disk.  Any data read
from the sparse area is read as zeros, and when data is written to a
sparse area, it automatically materialized as real data in the file.

## On disk format
The sparse bitmap consists of a sparse file on disk, and a log file.

