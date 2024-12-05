///////////////////////////////////////////////////////////////////////////////
//
// Author: Nate Bliton
// Date: 2024-12-04 (Fall 2024)
//
// This is the implementation of a Markov Chain.
//
// This implementation of a Markov Chain is a square n x n matrix, where n is 
// a number of states (pages in our use-case), and the contents of the matrix 
// are relative probabilities of transitioning from one state to another.
//
// I intend to use this in PA 4, and will likely rework it a little to be more
// robust, perhaps adding thread-saftey features, etc.
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "markov_chain.h"


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
MarkovChain* CreateMarkovChain(int num_pages) {

    // allocate memory for our markov matrix
    MarkovChain *markovChain = (MarkovChain *)malloc(sizeof(MarkovChain));
    if (markovChain == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    
    // initialize our num_pages and allocate space for the matrix
    markovChain->num_pages = num_pages;
    markovChain->matrix = (float **)malloc(num_pages * sizeof(float *));
    if (markovChain->matrix == NULL) {
        printf("Memory allocation for matrix rows failed.\n");
        free(markovChain);
        return NULL;
    }

    // Initialize all entries to 0.0
    // but abort if memory allocation fails at any point
    for (int i = 0; i < num_pages; i++) {
        markovChain->matrix[i] = (float *)calloc(num_pages, sizeof(float));  
        if (markovChain->matrix[i] == NULL) {
            printf("Memory allocation for matrix columns failed.\n");
            for (int j = 0; j < i; j++) {
                free(markovChain->matrix[j]);
            }
            free(markovChain->matrix);
            free(markovChain);
            return NULL;
        }
    }

    return markovChain;
}


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
void DestroyMarkovChain(MarkovChain *markovChain) {
    
    // if it hasn't already been freed, free memory 
    // for each row and then the whole matrix
    if (markovChain != NULL) {
        for (int i = 0; i < markovChain->num_pages; i++) {
            free(markovChain->matrix[i]);
        }
        free(markovChain->matrix);
        free(markovChain);
    }
}


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
// General algorithm:
//     (check input)
//     increment count for this transition
//     evaluate new sum for row
//     normalize row by dividing each cell by new sum for row
//
////////////////////////////////////////////////////////////////////////////////
void UpdateTransition(MarkovChain *markovChain, int prev_page, int next_page) {
    
    // return with no action if markovChain is not initialized
    if(markovChain == NULL) {
        printf("invalid markovChain");
        return;
    }

    // also only update if input is valid
    if (prev_page >= 0 && prev_page < markovChain->num_pages && 
        next_page >= 0 && next_page < markovChain->num_pages) {
        
        // Increment the count for this transition
        markovChain->matrix[prev_page][next_page] += 1.0;  
        
        // Normalize the row to convert counts into probabilities
        float row_sum = 0;
        for (int j = 0; j < markovChain->num_pages; j++) {
            row_sum += markovChain->matrix[prev_page][j];
        }

        // protect from divide by zero
        if (row_sum > 0) { 
            for (int j = 0; j < markovChain->num_pages; j++) {
                // Normaliz: divide each by new sum for row
                markovChain->matrix[prev_page][j] /= row_sum;  
            }
        }
    } else {
        printf("Invalid page indices for update.\n");
    }
}


////////////////////////////////////////////////////////////////////////////////
// PredictNextPage(MarkovChain *matrix, int current_page)
//
// This is a function to predict the next page based on the current page,
// given the contents of the provided markov matrix.
//
// Parameters   : MarkovChain * markovChain - matrix to print the contents of
//                int current_page - current page to query against matrix of 
//                                   probabilities of next page
//
// Return value : int - one of the most probable next pages (returns highest if 
//                      more than one), or -1 if all are uninitialized.
//
////////////////////////////////////////////////////////////////////////////////
int PredictNextPage(MarkovChain *markovChain, int current_page) {

    // return early if markovChain is not initialized
    if(markovChain == NULL) {
        printf("invalid markovChain");
        return -1;
    }
    
    // and check input of current_page to be in range
    if (current_page < 0 || current_page >= markovChain->num_pages) {
        printf("Invalid current page index.\n");
        return -1;
    }

    // initialize our variables for the search across the row for this page
    int predicted_page = -1;
    float max_prob = 0.0;

    // Find the page with the highest transition probability from the current page
    for (int j = 0; j < markovChain->num_pages; j++) {
        if (markovChain->matrix[current_page][j] > max_prob) {
            max_prob = markovChain->matrix[current_page][j];
            predicted_page = j;
        }
    }

    // return that found page, or -1 if none are a particularly good option
    return predicted_page;
}


////////////////////////////////////////////////////////////////////////////////
// PrintMarkovChain(MarkovChain *matrix)
//
// This prints the contents of a given Markov matrix. 
// Note: The probabilities are rounded to two decimal places
//
// Parameters   : MarkovChain * markovChain - provided struct to print the  
//                                            contents of its matrix
//
// Return value : none (but will print to the console)
//
////////////////////////////////////////////////////////////////////////////////
void PrintMarkovChain(MarkovChain *markovChain) {

    // iterate across the markofChain's matrix and print its contents, 
    // rounded to 2 decimal places
    printf("Transition Matrix:\n");
    for (int i = 0; i < markovChain->num_pages; i++) {
        for (int j = 0; j < markovChain->num_pages; j++) {
            printf("%.2f ", markovChain->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
