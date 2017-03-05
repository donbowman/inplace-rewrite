* Inplace Re-Write

SSD storage has a problem called 'read-disturb errors'.
The controller typically tries to mitigate this by
counting the number of reads to a block, and moving it
when it exceeds some target.

I have observed (on more than 20 SSD) a problem where it
does not get this correct.
All of these problems were observed on a Samsung 2TB 950 PRO.

This program is an attempt to 'force' the rewrite. It opens
a file, and reads it, re-writing it in place.

To compile:
```gcc -o inplace-rewrite inplace-rewrite.c```

