///////////////////////////////////////////////////////////////////////////////
//
// Author: Nate Bliton
// Date: 2024-12-04 (Fall 2024)
//
// This is a file to demonstrate the features of the implemented markov_chain.
//
// First, it makes a MarkovChain to store probabilities for 4 states or pages,
// queries to demonstrate a miss, then adds values, queries, adds more values,
// and demonstrates how the returned next page changes.
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "markov_chain.h"


///////////////////////////////////////////////////////////////////////////////
// main(int argc,char **argv)
//
// This is the main function, demonstrating using a markov matrix with 4 pages.
// 
//  Parameters  : (none)
//
//  Return value: int - return status code: 
//                      0 if succesful, or a different int if there were a problem
//
///////////////////////////////////////////////////////////////////////////////
int main() {

    // Create a Markov matrix for 4 pages (states)
    int num_pages = 4;
    MarkovChain *markovChain = CreateMarkovChain(num_pages);
    
    PrintMarkovChain(markovChain);
    int predicted_page = PredictNextPage(markovChain, 1);
    // should print -1
    printf("Predicted next page after accessing page 1: %d\n\n", predicted_page);

    // Simulate some page transitions (e.g., queried page 1 after page 0, page 2 after page 0, etc.)
    UpdateTransition(markovChain, 0, 1);
    UpdateTransition(markovChain, 0, 2);
    UpdateTransition(markovChain, 1, 2);
    UpdateTransition(markovChain, 1, 3);
    UpdateTransition(markovChain, 2, 3);
    UpdateTransition(markovChain, 3, 0);

    // Print the transition matrix
    PrintMarkovChain(markovChain);

    // Predict the next page after accessing page 1
    predicted_page = PredictNextPage(markovChain, 1);
    // should print 2
    printf("Predicted next page after accessing page 1: %d\n\n", predicted_page);

    // add more transitions to change the weights
    UpdateTransition(markovChain, 1, 0);
    UpdateTransition(markovChain, 1, 0);
    // Print the transition matrix
    PrintMarkovChain(markovChain);

    // Predict the next page after accessing page 1 again, returns different result now
    predicted_page = PredictNextPage(markovChain, 1);
    // should print 0
    printf("Predicted next page after accessing page 1: %d\n\n", predicted_page);

    // Clean up memory
    DestroyMarkovChain(markovChain);

    return 0;
}