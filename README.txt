QSCM
A Smooth Blend of Scheme and C

I am fascinated by systems that are self-sufficients, when I was a kid I wanted to make a lego car that would run by itself but the battery pack was too heavy for the engine that I had. Then I learned about computers, and I became interested in compilers, and more specifically bootstrapped compilers. These compilers are able to ingest their own source code and compile themselves. This page describes my first attempt at writing such a compiler.

As a target for my bootstrapped compiler, I chose C, it's pretty high level, and if I can make the output of my compiler small enough I can probably have a nice entry for the IOCCC! To make the task non-trivial, we need a source language that is not simply a new syntax for C, we need a semantic gap that the compiler will bridge. A functional language is a natural thing to consider at this point, and if we want easy parsing, it is clear that what we need is something that is similar to Scheme.
A Quick (and dirty) Scheme

So our language has 5 keywords, def do fun if let.

The let keyword is a classic, it simply gives a name to an intermediate computation, for example (let x 3 ...) will bind 3 to the variable x and evaluate the body (leaved as an ellipsis) using this fresh binding. The if construct will be our only way to do branching, when the condition evaluates to anything that is not 0, the "then" branch is taken, in all other cases the "else" is used. Computations are sequenced using do, the last computation of a do construct will determine the result of the whole sequence. Functions are created by the fun construct. Finally def sets a gobal variable to a given value. A qscm program can use integer literals in base 10, string literals (which are read-only 0-terminated strings), and character literals like #a #b #c. Here follows the typical factorial example:

(do (def ! (fun (n)
        (if n (* n (! (- n 1))) 1)
    ))
    (! 6)
) → Evaluates to 720

To make the language suitable to do anything more than integer manipulations we garnish it with a "standard library" that includes the following 17 primitves:

    binary comparison operators <= >= < > =;
    standard arithmetic operators + - * /;
    Scheme pair constructor and destructors cons car cdr;
    string allocation (returns a pointer) new;
    pointer access operations get set;
    IO for characters (ASCII) getc putc. 

Here is a simple program that reads one line from the input and prints it backwards. Note how we use pointers just like in C (this is the dirty/fun part of this Scheme). Looping is achieved by simple recursion.

(do (def buf (new 100))
    (def inl (fun (p)
        (let c (getc)
        (if (= c 10)
            (set p 0)
            (do (set p c)
                (inl (+ 1 p)))
        ))
    ))
    (def outl (fun (p)
        (let c (get p)
        (if c
            (do (outl (+ 1 p))
                (putc c))
            0
        ))
    ))
    (inl buf) (outl buf) (putc 10)
)

By now, you might think that it is not going to be easy to bootstrap with so little and you are right. But despite the frugal apparences, this language is actually quite fun to use and I encourage you to write one or two programs in it! If you lack insipration, Quicksort is a fun algorithm to program.

Gotchas. The evaluation order of arguments is unspecified, so if your code depends on this, it will have unpredictable behavior (in my experience, clang as a backend will do what you want, gcc will not). Most of the default functions can be overwritten but not the arithmetic and comparison functions (this is a limitation of the compiler). No proper tail recursion, sorry.
The Compiler

    The compiler in qscm (17.qscm ~7k) and in C (qscm.c ~5k).
    The compilation helper script in bash (comp.sh ~1k).
    BONUS The interpreter I used for the development in Haskell (qscm.hs ~9k). 

$ cc -o comp qscm.c
$ sh comp.sh 17.qscm
$ diff /tmp/qscm.c qscm.c || echo 'bug!'  # they must be the same!
$ ls -l
...
-rwxr-xr-x 1 qcar users   33060 Dec  5 16:29 a.out
...
$ # And a.out is the result of the self compilation!

The above commands show you how to bootstrap! Using the helper script you can also compile the small example I gave in the previous section into a (efficient?) C program. Be careful, because it is so tiny, the compiler will not check the syntax of your input program! It can segfault pretty easily on incorrect inputs. They call it "garbage in, garbage out", I think.
What Makes It Work

To start, you need an interpreter. I wrote mine in Haskell in about one day (some tests included). The hard part in my Haskell interpreter is to model the C strings as supported by qscm. To do this I had to model heap and represent pointers. Following the work on C semantics, my pointers are simply a pair of a block identifier (pointing to the whole string) and an offset in this larger string. All pointer arithmetic operations are checked by the interpreter, and operate on the offset.

Once the interpreter is working, you have to write the compiler. First, get a simple parser/pretty-printer working, this is fairly easy thanks to all the parentheses in Scheme! Then you need to figure out a mapping between your source language constructs and constructs of the destination language, I decided to go really straightforward for basic qscm constructs.

    (do a b ...) is translated by the sequencing operator ,.
    (if a b c) is translated by the ternary operator ?. 

The values of qscm are uniformly represented as numbers of type intptr_t abbreviated as V. Then, depending on the operation that we perform on the value, this number is interpreted either as a signed integer or as a pointer. For example, cons pairs are simply represented as pointers to arrays of two values, as you can see in the implementation for the cons, car, and cdr primitives.

V C(V a,V d){                    /* cons */
    V *p=malloc(2*sizeof*p);
    p[0]=a; p[1]=d;
    return (V)p;
}
V a_(V x){ return *(V*)x; }      /* car */
V d_(V x){ return *((V*)x+1); }  /* cdr */

Remains the core of Scheme, functions and let bindings. These two constructs introduce new names into the local scope. Following standard compilers/interpreters for functional languages, I used an environment to store this information. When some piece of code accesses a local variable, we go and pick it up in the local environment. In the generated code, this is handled by the L_(n, e) function which gets the nth variable in the environment e.

V L_(V n,V e){
    while(--n)
        e=d_(e);
    return a_(e);
}

Since environments are represented as lists, getting the nth variable in e amounts to take the cdr of the environment n-1 times and then return the car. Once we have this environment it is pretty clear what the let construct must do: (1) it must add the value of the bound expression as a new element in the environment, (2) then evaluate the second expression in the new environment, and (3) restore the old environment and return the result of the second evaluation. The step three is fairly tricky to do using only C expressions, so I hacked it by calling a helper function B_ that first pops the top variable off the environment passed as second argument and then returns the value of its first argument. So (let x e1 e2) is compiled as (e = e1, B_(e2, &e)).

The handling of function also involves environments because of the creation of closures values. A closure is simply a cons pair that contains a function pointer and an environment. When the closure is invoked, we retrieve its environment and stack the value of its arguments on top of it, then we call the function pointer with the new environment as argument. All of this is implemented by the Z{1,2,3,4,n} macros and function.

The compiler actually works in two phases, first it does a depth-first pass on the syntax (while parsing) and extracts all the functions into the list fns, then a second pass prints the output C code by first printing the function definitions and then printing the body of the main function (that is the expression resulting from the compilation of the whole program). Internally, expressions are represented as tagged pairs where the car of the pair is a character indicating the type of the expression and the cdr is the actual representation of the expression.

I will not explain all of the inners of the compiler here because it might be a fun game to check it out by yourself and see how such a tiny language can get to compile itself! In particular, you can lookup how I emulate the || and && which are missing in the language, or how I created a kind of printf function for easier pretty printing. I am of course open to any suggestions to improve it! 
