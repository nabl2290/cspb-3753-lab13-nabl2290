///////////////////////////////////////////////////////////////////////////////
//
// Author: Nate Bliton
// Date: 2024-12-04 (Fall 2024)
//
// This is the header file for the Markov Chain implementation.
//
// This implementation of a Markov Chain is a square n x n matrix, where n is 
// a number of states (pages in our use-case), and the contents of the matrix 
// are relative probabilities of transitioning from one state to another.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

// Define the MarkovChain structure
typedef struct {
    int num_pages;  // Number of pages/states
    float **matrix;  // Transition matrix, storing probabilities as floats
} MarkovChain;


////////////////////////////////////////////////////////////////////////////////
// CreateMarkovChain(int num_pages)
//
// This creates and returns a Markov Chain
//
// Parameters   : int num_pages - number of pages, dimension of square matrix
//
// Return value : MarkovChain * - pointer to created Markov Chain
//
////////////////////////////////////////////////////////////////////////////////
MarkovChain* CreateMarkovChain(int num_pages);


////////////////////////////////////////////////////////////////////////////////
// DestroyMarkovChain(MarkovChain *matrix)
//
// This destroys a provided Markov Chain.
//
// Parameters   : MarkovChain * markovChain - matrix to destroy and cleanup its memory
//
// Return value : none
//
////////////////////////////////////////////////////////////////////////////////
void DestroyMarkovChain(MarkovChain *markovChain);


////////////////////////////////////////////////////////////////////////////////
// UpdateTransition(MarkovChain *matrix, int prev_page, int next_page)
//
// This updates a given Markov matrix. 
// We will use this to record an observed page transition
//
// Parameters   : MarkovChain * matrix - matrix to update
//
// Return value : none
//
////////////////////////////////////////////////////////////////////////////////
void UpdateTransition(MarkovChain *markovChain, int prev_page, int next_page);


////////////////////////////////////////////////////////////////////////////////
// PredictNextPage(MarkovChain *matrix, int current_page)
//
// This is a function to predict the next page based on the current page,
// given the contents of the provided markov matrix.
//
// Parameters   : MarkovChain * markovChain - matrix to print the contents of
//
// Return value : none (but will print to the console)
//
////////////////////////////////////////////////////////////////////////////////
int PredictNextPage(MarkovChain *markovChain, int current_page);


////////////////////////////////////////////////////////////////////////////////
// PrintMarkovChain(MarkovChain *matrix)
//
// This prints the contents of a given Markov matrix. 
// Note: The probabilities are rounded to two decimal places
//
// Parameters   : MarkovChain * markovChain - matrix to print the contents of
//
// Return value : none (but will print to the console)
//
////////////////////////////////////////////////////////////////////////////////
void PrintMarkovChain(MarkovChain *markovChain);

#endif // MARKOV_CHAIN_H
