# Author: Nate Bliton
# Date: 2024-12-04 (Fall 2024)
# Time spent so far: 4

all: markov_tester

markov_tester: markov_tester.c markov_chain.c
	gcc markov_tester.c markov_chain.c -o markov_tester

clean:
	rm -f markov_tester

test:
	./markov_tester