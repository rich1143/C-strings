* [Background](#background)
 * [Testing and the CMockery framework](#testing-and-the-cmockery-framework)
 * [Fixing memory problems](#fixing-memory-problems)
 * [Getting started](#getting-started)
* [The problems](#the-problems)
 * [Fixing palindromes](#fixing-palindromes)
 * [Disemvowel](#disemvowel)
 * [Mergesort](#mergesort)
 * [Array merge](#array-merge)

---

# Background

This lab is a collection of several C programming exercises with an
emphasis on arrays, pointers, and memory management. The first is an
introduction to a tool for finding memory leaks, the second is a simple
exercise on 1-D arrays of characters, and the last is a more complex
array-of-array problem where I give you much less to begin with.

For more information (including information on how to use ```valgrind```), see
the [Lab3 pre-lab](https://wiki.umn.edu/UMMCSci/CSci3401f13/Lab3Prelab).

## Testing and the CMockery framework

Each of these exercises comes with a set of tests implemented using [the
CMockery testing framework for C](http://code.google.com/p/cmockery/).
You won't have to learn anything about the CMockery framework, but you
will need to add some components to your compilation instructions to
include the CMockery library so the tests actually run. 
The CMockery files in the `lib` directory
were built for 64-bit
Linux boxes (FC18). If you want to use these tests on a different architecture
you'll need to download and build the library for your gear.

We think the tests are pretty reasonable, but make **no** promises that
they are in any way complete. Obviously you want your code to pass at
least these tests, but you shouldn't assume that passing these tests
guarantees any kind of correctness. You're welcome to read the tests 
and extend them if
you'd like. Don't change any of the given tests, though; we'll test
your code against *those* tests, and it's a Bad
Thing if they don't pass those.

On a related note, don't over focus on the tests. CMockery frankly
doesn't give you super useful error messages or info when things fail.
You can get more information using the ```gdb``` debugger, but
that's not trivial to use. In many cases it will be as or more useful to
write little bits of code that print out useful information from your
code to help with debugging. You'll eventually want to remove all that,
but it may be *awfully* useful while you're exploring.

## Fixing memory problems

Passing the tests is arguably just the first half of each of these problems,
as it's entirely possible to pass the tests but still have substantial memory
management problems. You could, for example, have an illegal memory access
that passes the tests through happenstance, because the right value happens
to be in the necessary location. Or you could have memory leaks because you
never free up any of the memory you allocate while solving the problem in a
manner that is otherwise entirely correct. This is where `valgrind` is extremely
helpful, as it will identify these kinds
of memory problems even if the tests pass. 

:bangbang: One non-obvious, but important, place to look for memory leaks is 
in the test code. If the test code calls some function `f()` that returns an
array or string that is allocated somewhere in `f` (or a function `f` calls),
then that memory is lost if the test code doesn't free up that returned array.
So if `valgrind` says there's a leak where some memory is allocated in a function
and then returned to the test code, then the fix is _in the test code_. In general
we _don't_ encourage/want you to be changing the test code (you could always
just change the test code to say everything passes!), but if the memory leaks
to the test code, then that's where the fix has to be made.

## Getting started

You should then fork this repo to get the
starter code.
There are several directories there,
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

---

# The problems

:bangbang: Remember: For each problem you should at a minimum
* Pass our tests, and 
* Have _no_ memory leaks, as confirmed by `valgrind`.
* Remove any print statements that you used to debug your code before you turn it in.

Also, please don't lose your brains and forget good programming practices just because you're working in a new language. C can be quite difficult to read under the best of circumstances, and using miserable names like `res`, `res2`, and `res3` doesn't help. *Use functions* to break up complicated bits of logic; it's really not fun when a group turns in a solution that is one huge function, especially when there are several instances of repeated logic.

Some things to watch our for:
* In the past there has been strong inverse correlation between length
and correctness on these problem. If you find yourself wandering off into 2
or (especially!) 3 pages of code for any of these, you've likely lost the plot
and should probably ask for some help.
* Make sure you initialize all variables (including variables used to index arrays in loops). C won't give you an error if you fail to initialize something, and sometimes you can get lucky and your tests will accidentally pass because, at least that one time, you happened to get the "right" initial value. That doesn't mean your code is correct, though.
* Make sure you allocate space for the null terminator `\0` when allocating space for strings.

[There are more comprehensive tips and suggestions here.](https://github.umn.edu/UMM-CSci-Systems/C-Lab-Starter/blob/master/Tips_and_suggestions.md)

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

To simplify the process, we've provided you with [Java implementations of
Quicksort and
Mergesort](https://github.umn.edu/gist/mcphee/83e9818b21ef9cb3cde4) that
you can use as models. We strongly
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

Your task here is to implement 
```C
int* array_merge(int num_arrays, int* sizes, int** values);
```
Here `values` is an array of arrays
of integers, where each of the sub-arrays can have different length (so
it's not really a standard 2-D array). Because C doesn't know the size
of arrays, we need to provide all that information in the arguments:
`num_arrays` is the number of arrays in `values`, and `sizes` is an
array of ints that should also have `num_arrays` entries, each of which
is the length of the corresponding sub-array in `values`. If
`sizes[3]==10`, for example, then `values[3]` will be an array of 10
integers.

_Note how inherently icky it is to have to pass all this bookkeeping
information around, and how many wonderfully unpleasant errors can
result from doing this incorrectly. It's a **lot** safer if arrays know
how big they are._

`array_merge` should then generate a sorted list (small to large) of the
unique values (i.e., no duplicates) in `values`. Since we haven't yet
learned how to return multiple values in C, we're going to use a
slightly cheesy hack and return the `k` unique values in an array of
size `k+1`, where the first element will hold the value `k`. If, for
example, there were 3 unique values (5, 8, and 9), then the result array
would contain [3, 5, 8, 9]. The caller can then use the first element of
the array to determine how long the array actually is.

As a more complete example, consider the following input:

-   `num_arrays = 3`
-   `sizes = [4, 2, 5]`
-   `values = [[3, 2, 0, 5], [8, 9], [6, 3, 2, 0, 5]]`

Then the result should be `[7, 0, 2, 3, 5, 6, 8, 9]`.

There are ways to write this that waste a lot of memory when the set of
unique values is much smaller than the number of entries in `values`;
your solution should make a point of freeing up any unused memory.

You might also find your sorting algorithm from above useful in sorting
your results. With a little care, you can put the results in an unsorted
array, and then ask your sorting algorithm to sort the desired bit of
the array without messing with that important first element.

---

People that contributed to this write-up before the project was moved
to Github included Nic McPhee, Vincent Borchardt, and KK Lamberty.
