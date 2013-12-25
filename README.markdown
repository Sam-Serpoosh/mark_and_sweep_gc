## Mark and Sweep Garbage Collection Algorithm

This is a simple piece of code in *C* which is implementing the famous Mark and Sweep Garbage Collection algorithm invented by **John McCarthy**.

This whole thing was inspired by [this amazing blog post](http://journal.stuffwithstuff.com/2013/12/08/babys-first-garbage-collector/) by [Bob Nystrom](https://twitter.com/i/connect)

He even wrote the code for that blog post which can be found in his GitHub repo [here](https://github.com/munificent/mark-sweep).


### Re-used parts of Bob's Code

I used Bob's **data structures** pretty much exactly as they are. I also re-used his **test cases** in order to make sure my final result is working as it should. Since I read his blog post twice (as I do for almost every blog post) and Mark and Sweep has well-defined phases/steps, the rest of the code of course look a lot similar to Bob's code as well but I swear I didn't cheat from his code while I was implementing the algorithm :) **BUT** one main difference in the code that can be found is the sweep implementation details.

Personally I'm not a huge fan of *Pointer-to-Pointer* cause they increase the confusion in the code. I'm not saying it's a bad thing, not at all, but if I can implement something without using them, I'll try to do that. Bob's implementation for **sweep** phase is using *Pointer-to-Pointer* and mine does **NOT** with some differences in the implementation details.

### Why did I wrote it

For the same reason I write almost everything:

```
* Fun :)
* Practicing and improviing programming and thinking muscles
* Getting rid of the pointer-to-pointer confusion in the sweep code
```

### SYNOPSIS

Just run:

```
make
```

and that'll run all the tests and let you know if something fails.

### Final Note

I strongly recommend you to read Bob's blog post on this. I've raed a lot of blogs/articles on garbage collection algorithms and approaches but hands down this one had the **SIMPLICITY** factor in its explanation and implementation nicely.

Thanks to Bob for motivating this piece of code :)
