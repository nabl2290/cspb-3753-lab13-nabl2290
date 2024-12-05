# Lab 13 - Markov chains - Nate Bliton, nabl2290, 2024-12-04

## Notes about this Markov Chain implementation

This is my implementation of a Markov chain, which I hope to use in the Paging programming assignment.

A Markov Chain is useful for getting which page would be most likely to be queried after a particular page is queried, and so I have set up this MarkovChain to be able to perform the following functions:

* Create (create a markov chain of a certain size with CreateMarkovChain)
* Destroy (destroy a markov chain with DestroyMarkovChain)
* Predict Next (provide a page and get a predicted next page with PredictNextPage)
* Update (update how page prediction should behave given a new pair of page sequence with UpdateTransition)

This is a basic implementation, as it seemed like that was what was proposed here, but if I use this in the Paging PA 4, I will likely add features like thread-safety if needed at that point.

If you run these commands from the Makefile, it should compile and print a quick demonstration of its functionality, first no good prediction after page 1, then predicting 2 after page 1, then changing its prediction after page 1 after the matrix is updated:

    make
    make test

## Other notes

In case I need to include answers to the questions in the PDF, I am including them here:

### Walks and Matrix Multiplication:

1. What does the $(i, j)$-entry of $A^2$ compute?

    An entry in $A^2$ will indicate if there is a path from $i$ to $j$ that takes two steps, as in from $i$ to $x$ to $j$.

2. For any positive integer $k$, what does the $(i,j)$-entry of $A^k$ compute?

    Generally, it will show if or how many paths there are from $i$ to $j$ that take $k$ edges to arrive at.

### Markov Chains

1. For any positive integer k, is $M^k$ a Markov chain
   
   and

2. What does the $(i,j)$-entry of $M^k$ compute?

    Yes, if $M$ is a Markov chain giving probabilities of going from from $i$ to $j$ in a single step, then $M^k$ gives probabilities of going from $i$ to $j$ in $k$ steps.