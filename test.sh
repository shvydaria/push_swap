#!/bin/bash

# --- Configuration ---
# Check if an argument is provided
if [ -z "$1" ]; then
	echo "Usage: $0 [number_of_elements]"
	echo "Example: $0 100"
	exit 1
fi

NUM_COUNT=$1
NUM_TESTS=5 # Number of runs to average

# --- Project Requirements ---
LIMIT=0
if [ "$NUM_COUNT" -eq 100 ]; then
	LIMIT=700 # Aiming for a good average score
elif [ "$NUM_COUNT" -eq 500 ]; then
	LIMIT=5500 # Aiming for a good average score
else
	echo "Testing for $NUM_COUNT numbers (no specific limit defined)."
fi

# --- Colors ---
GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[1;33m"
NC="\033[0m"

# Function to generate random unique numbers
# Uses 'jot' on macOS and 'shuf' on Linux
generate_numbers() {
	local count=$1
	if [[ "$(uname)" == "Darwin" ]]; then
		jot -r -w %d "$count" -2147483648 2147483647 | tr '\n' ' '
	else
		shuf -i -2147483648-2147483647 -n "$count" | tr '\n' ' '
	fi
}

# --- Main Test Logic ---
echo "--- Testing with $NUM_COUNT numbers ($NUM_TESTS runs) ---"

total_moves=0
max_moves=0

for i in $(seq 1 $NUM_TESTS); do
	echo -n "Run $i: "
	# Generate a new set of random numbers for each run
	ARG=$(generate_numbers $NUM_COUNT)
	
	# Execute push_swap and count the lines (moves)
	# 2>/dev/null suppresses any error messages from push_swap itself
	MOVES=$(./push_swap $ARG 2>/dev/null | wc -l | tr -d ' ')

	# Check if MOVES is a valid number
	if ! [[ "$MOVES" =~ ^[0-9]+$ ]]; then
		echo -e "${RED}Error running push_swap. No moves counted.${NC}"
		continue
	fi

	if [ $MOVES -gt $max_moves ]; then
		max_moves=$MOVES
	fi
	total_moves=$((total_moves + MOVES))

	echo "Moves: $MOVES"
done

if [ $NUM_TESTS -gt 0 ] && [ $total_moves -gt 0 ]; then
	average_moves=$((total_moves / NUM_TESTS))
	echo "-------------------------------------"
	echo "Max moves:     $max_moves"
	echo "Average moves: $average_moves"

	if [ $LIMIT -gt 0 ]; then
		if [ $average_moves -lt $LIMIT ]; then
			echo -e "${GREEN}SUCCESS: Average is below the limit of $LIMIT.${NC}"
		else
			echo -e "${RED}FAILURE: Average is over the limit of $LIMIT.${NC}"
		fi
	fi
else
	echo "Could not complete tests."
fi
