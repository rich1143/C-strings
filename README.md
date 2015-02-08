Lab 3 starter 
=============

The starter code for Lab 3: C and memory management. This includes the
starter code, tests, and the necessary CMockery include file (in
```include```) and library file (in ```lib```).

The CMockery files come from [building the library from Google
Code](<https://code.google.com/p/cmockery/>) and were built 64-bit FC18
Linux boxes. If you want to use these tests on a different architecture
you'll need to download and build the library for your gear.

---

# Background

This lab is a collection of several C programming exercises with an
emphasis on arrays, pointers, and memory management. The first is an
introduction to a tool for finding memory leaks, the second is a simple
exercise on 1-D arrays of characters, and the last is a more complex
array-of-array problem where I give you much less to begin with.

I used essentially the same lab in previous years, and [posted some
comments](UMMCSci.CLabNotes) based on the work they turned in. Some of
these might be helpful, so you might want to have a look. They tend to
come down to "don't forget how to program cleanly just because you're
writing C". So don't!

For more information (including information on how to use ```valgrind```), see
the [Lab3 pre-lab](Lab3Prelab).

## Testing and the CMockery framework

Each of these exercises comes with a set of tests implemented using [the
CMockery testing framework for C](http://code.google.com/p/cmockery/).
You won't have to learn anything about the CMockery framework, but you
will need to add some components to your compilation instructions to
include the CMockery library so the tests actually run.

I think the tests are pretty reasonable, but I make **no** promises that
they are in any way complete. Obviously you want your code to pass at
least these tests, but you shouldn't assume that passing these tests
guarantees any kind of correctness. You're welcome to read the tests (I
think the basics of CMockery are pretty readable) and extend them if
you'd like. I wouldn't change the tests I gave you, though; we'll test
your code against *those* tests, and if they don't pass that's a Bad
Thing.

On a related note, don't over focus on the tests. CMockery frankly
doesn't give you super useful error messages or info when things fail.
You can get more information using the ```gdb``` debugger, but
that's not trivial to use. In many cases it will be as or more useful to
write little bits of code that print out useful information from your
code to help with debugging. You'll eventually want to remove all that,
but it may be *awfully* useful while you're exploring.

## Getting started

Your group should choose a team name and add it to the list of groups
below. You should then fork [the starter repo on
Github](https://github.com/UMM-CSci-3401-F13/Lab_3_starter) to get the
starter code for all four projects. There are several directories there,
one for each project. We would recommend doing them in the order listed
below; there's no overwhelming reason that you need to do them in any
particular order, however, and it would be far better to move on to the
next one rather than get buried in one and not make any progress.

The basic structure for each project is (for an imaginary project
`foo`):

-   `foo.h`, which specifies the name, arguments, and return
    type of the function you're supposed to write.
    -   In every case we wrote one or more helper functions, but these
        don't have to be included in the `.h` file unless you
        want to include them in the tests.
-   `foo_test.c`, which is the test file we wrote using
    CMockery.

There are also top level `include` and `lib`
directories that contain:

-   `include/cmockery.h`, which is the CMockery include file
    that the test file includes.
-   `lib/libcmockery_la-cmockery.o`, which is the object file
    containing the compiled versions of all the CMockery routines.

Your job then is typically to write `foo.c`, which provides
the implementation of the function listed in `foo.h`. To
compile the test code (with all the CMockery stuff) use the following:
```bash 
gcc -Wall -g -o foo_test foo.c foo_test.c ../lib/libcmockery_la-cmockery.o 
``` 
(where you replace `foo` with the appropriate name for the project you're working
on). The `-g` flag is something we haven't talked about and
not strictly necessary; it causes a variety of useful debugging
information to be included in the executable, however, which can be
*extremely* helpful when using tools like `valgrind` or the
`gdb` debugger.

:bangbang: You'll get one or more (possibly several) warnings of the
form 
``` 
foo_test.c:52: warning: initialization from incompatible pointer type 
``` 
These are due to an issue in CMockery that isn't
easy to work around, so just ignore them. This is not a license to
ignore all warnings! Just ignore these from the code that you've been
given.

---

# The problems

## Fixing palindromes

Before you start writing your own C code, we'll start by using valgrind
to identify memory leaks in an existing program. In the
`palindrome` directory there is a program that
determines (in sort of a dumb way) if a string is a palindrome. The file
`palindrome.c` has the code that checks for palindromes and (instead of
doing the more obvious thing of returning a boolean) returns the string
"Yes" or "No". The file `palindrome_test.c` uses the CMockery library
mentioned above to test that the `palindrome` function works. You should
go into that `palindrome` directory in your project and compile the
program: 
```bash
gcc -Wall -g -o palindrome_test palindrome.c palindrome_test.c ../lib/libcmockery_la-cmockery.o
```
Run the resulting executable and
verify that all six tests pass.

Look at the code a little and see if you can spot any obvious memory
leaks. Then run `valgrind` on your executable and see what it tells you
about memory leaks in this code. Then go through and fix the memory
leaks so that `valgrind` is happy (and the tests still pass).

## Disemvowel

"Disemvoweling" is the act of removing all the vowels (a, e, i, o, and
u, both upper and lowercase) from a piece of text. Your task here is to
write a function
```C
char* disemvowel(char* str);
```
that takes a null-terminated string, and returns a new null-terminated
string (i.e., it doesn't mangle the original one) that contains the same
characters in the same order, minus all the vowels. Note that resulting
array of characters will need to be allocated, and will typically be
shorter than the input string. It would be desirable to not waste memory
and only allocate what you actually need for the return string; you
might find valgrind useful for helping check for leaks.

We've provided a `main.c` which you can compile instead of
`disemvowel_test.c` if you want to try out disemvoweling different
strings from the command line. :bangbang: You
need to make sure you only compile one of `main.c` and
`disemvowel_test.c`, otherwise you'll get a compiler error about trying to define `main()`
twice.

## Mergesort

Your task here is to implement a well known sorting algorithm in C,
e.g.,
```C
void mergesort(int size, int values[]);
```
This is a
destructive sorting operation, and should alter the array that it's
given. Note that since C doesn't know how large arrays are, we pass in
the size as an argument.

To simplify the process, I've provided you with [Java implementations of
Quicksort and
Mergesort](NicMcPhee.JavaImplementationsOfQuicksortAndMergesort) that
you can use as models. I strongly
recommend you take advantage of these both because it will help ensure
that you focus on the C issues on these problems and because it'll make
them easier to grade. (Having to figure out some crazy, unexpected
approach is much more time consuming than reading a "standard"
solution.)

Common approaches to Mergesort require allocating temporary arrays; you
should make a point of freeing these up when they're no longer needed,
as you certainly wouldn't want a common operation like sorting to leak a
bunch of memory every time it's called. Again, valgrind should be your
friend.

## Array merge

Your task here is to implement <span class="twiki-macro CODE">C</span>
int\* array\_merge(int num\_arrays, int\* sizes, int\*\* values); <span
class="twiki-macro ENDCODE"></span> Here `values` is an array of arrays
of integers, where each of the sub-arrays can have different length (so
it's not really a standard 2-D array). Because C doesn't know the size
of arrays, we need to provide all that information in the arguments:
`num_arrays` is the number of arrays in `values`, and `sizes` is an
array of ints that should also have `num_arrays` entries, each of which
is the length of the corresponding sub-array in `values`. If
`sizes[3]=10`, for example, then `values[3]` will be an array of 10
integers.

*Note how inherently icky it is to have to pass all this bookkeeping
information around, and how many wonderfully unpleasant errors can
result from doing this incorrectly. It's a **lot** safer if arrays know
how big they are.*

`array_merge` should then generate a sorted list (small to large) of the
unique values (i.e., no duplicates) in `values`. Since we haven't yet
learned how to return multiple values in C, we're going to use a
slightly cheesy hack and return the `k` unique values in an array of
size `k+1`, where the first element will hold the value `k`. If, for
example, there were 3 unique values (5, 8, and 9), then the result array
would contain [3, 5, 8, 9]. The caller can then use the first element of
the array to determine how long the array actually is.

As a more complete example, consider the following input:

-   =num\_arrays = 3=
-   =sizes = [4, 2, 5]=
-   =values = [[3, 2, 0, 5], [8, 9], [6, 3, 2, 0, 5]]=

Then the result should be `[7, 0, 2, 3, 5, 6, 8, 9]`.

There are ways to write this that waste a lot of memory when the set of
unique values is much smaller than the number of entries in =values=;
your solution should make a point of freeing up any unused memory.

You might also find your sorting algorithm from above useful in sorting
your results. With a little care, you can put the results in an unsorted
array, and then ask your sorting algorithm to sort the desired bit of
the array without messing with that important first element.

---

-- Main.NicMcPhee - 19 Sep 2011\<br\> -- Main.VincentBorchardt - 21 Jun
2012\<br\> -- Main.lamberty - 18 Sep 2012
