victorcheung

Ex0
Leaked 76427 bytes (in use at exit) 
Also has conditional jumps that depend on uninitialised values.

Ex1
0,1,2 has a conditional based on an uninitialised value
0 is different from 1 and 2 since the conditional is based on an uninitialised value created by a stack allocation. 
After the change the compiler is recognizing the use of an uninitialised variable. 
A static array declaration (int a[SIZE]) prevents Valgrind from doing its job

Ex2
1. x in fun4 is located in the stack, whereas x in fun5 is located in the heap.
2. The bug is write beyond the end of the array.
3. on fun4 the results are cryptic with signal 11 (SIGSEGV) and "Access not within mapped region", whereas with fun5, we have "invalid write of size 4" and "invalid read of size 4", along with the exact line number in fun5 where this invlaid read/write occured. fun5 also uses a dynamically allocated array. 
4. We first write beyond the end of the array, and then read from that same invalid location, hence the invalid read/write.
5. Yes. Valgrind works better with dynamically allocated arrays. 
6. No error was detected when we run valgrind ./vgme. Again, a global static array prevented valgrind from doing its job.

Ex3
1. The block of allocated memory was freed prior to the write. 
2. The words "free", "alloc'd" and "malloc" inform us of the differences. 
3. Valgrind informs you of the size of the invlaid write/read. Since we're writing an int, and valgrind tells us this is an invalid write/read of size 4, then we know that ints are of size 4. 

Ex4
1. Line 88, or   free(same(x)), did not generate an error. 
2.  line 85 corresponds to the heap.
	line 86 corresponds to text. 
	line 87 corresponds to data. 
	line 89 corresponds to the heap. 
3. 
4. Removing same causes the compiler to recognize that we're trying to free non-heap objects. 

Ex5
1. THe bug is that an array of ints was allocated in the heap but never freed.
2. This helps us idenitfy on what line the memory allocation happened. 
