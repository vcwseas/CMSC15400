victorcheung
1. Threads run at arbitrary times and we can't predict the order in which they run. 
2. Data is passed to the start routine via the fourth argument of pthread_create, which is always a void *. The parameter in the start routine is also a void *. 
3. Through a void **. More precisely, pthread_join takes an argument that is the address of a void * for threads to return data to.
4. pthread_exit takes a pointer to return values, and in this we had to fix a leak that came from not freeing the mallced objected pointed to by pthread_exit's argument. 

Ex1
Parent thread and child thread are racing to increment the global variable var 10000 first.Helgrind tells you about possible read and write conflicts; it also gives you the address of the variable from which the conflict arises. 

Ex2 
There is an implied order of having to acquire odd.lock before even.lock. Therefore all threads must try for the locks in that order or else risk deadlocks. This is because pthread_mutex_lock() will block until the mutex becomes available if it's already locked. Hence the mutual deadlock herein.

==20544== 
starting counting (^C if not finished in a second) ...
 ... &(odd.lock)=0x6010c0; &(even.lock)=0x601080 ...
==20544== ---Thread-Announcement------------------------------------------
==20544== 
==20544== Thread #3 was created
==20544==    at 0x51453BE: clone (clone.S:77)
==20544==    by 0x4E3AF6F: do_clone.constprop.4 (createthread.c:75)
==20544==    by 0x4E3C57F: pthread_create@@GLIBC_2.2.5 (createthread.c:256)
==20544==    by 0x4C2DAAD: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20544==    by 0x40093E: main (main.c:66)
==20544== 
==20544== ----------------------------------------------------------------
==20544== 
==20544== Thread #3: lock order "0x6010C0 before 0x601080" violated
==20544== 
==20544== Observed (incorrect) order is: acquisition of lock at 0x601080
==20544==    at 0x4C2E0ED: pthread_mutex_lock (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20544==    by 0x400855: lower_fn (main.c:36)
==20544==    by 0x4C2DC3D: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20544==    by 0x4E3BE99: start_thread (pthread_create.c:308)
==20544== 
==20544==  followed by a later acquisition of lock at 0x6010C0
==20544==    at 0x4C2E0ED: pthread_mutex_lock (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20544==    by 0x40087A: lower_fn (main.c:41)
==20544==    by 0x4C2DC3D: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20544==    by 0x4E3BE99: start_thread (pthread_create.c:308)
==20544== 
==20544== Required order was established by acquisition of lock at 0x6010C0
==20544==    at 0x4C2E0ED: pthread_mutex_lock (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20544==    by 0x4007C4: upper_fn (main.c:16)
==20544==    by 0x4C2DC3D: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20544==    by 0x4E3BE99: start_thread (pthread_create.c:308)
==20544== 
==20544==  followed by a later acquisition of lock at 0x601080
==20544==    at 0x4C2E0ED: pthread_mutex_lock (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20544==    by 0x4007F6: upper_fn (main.c:21)
==20544==    by 0x4C2DC3D: ??? (in /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so)
==20544==    by 0x4E3BE99: start_thread (pthread_create.c:308)
==20544== 
... 200 odds, 200 evens
==20544== 
==20544== For counts of detected and suppressed errors, rerun with: -v
==20544== Use --history-level=approx or =none to gain increased speed, at
==20544== the cost of reduced accuracy of conflicting-access information
==20544== ERROR SUMMARY: 100 errors from 1 contexts (suppressed: 709 from 16)
