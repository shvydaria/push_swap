### TODO:
1. explain k-sort
2. implement errors
3. check visualiser
4. checker_OS
5. update gitignore:
# Executables
*.exe
*.out
*.app
*.i*86
*.x86_64
*.hex

# Debug files
*.dSYM/
*.su
*.idb
*.pdb

# General
.DS_Store
.AppleDouble
.LSOverride
.gitignore

# VS Code
.vscode/*
!.vscode/settings.json
!.vscode/tasks.json
!.vscode/launch.json
!.vscode/extensions.json
!.vscode/*.code-snippets

# Local History for Visual Studio Code
.history/

# Built Visual Studio Code Extensions
*.vsix




### k_sort

1. Normalize the numbers
Convert each number in Stack A to its rank (position if sorted), ranging from 1 to N.
2. Initialize counters
Set count_B = 0 to track the number of elements in Stack B.
3. Push elements from A to B
Iterate through Stack A and apply the following rules:
- If the top element of A (v) is less than or equal to count_B, push it to B and rotate B (pb + rb).
- If v is greater than count_B but less than or equal to count_B + chunk_size, push it to B without rotating B (pb).
- Otherwise, rotate A (ra) to examine the next element.
4. Adjust chunk size dynamically
After each push to Stack B, increment count_B. Optionally, adjust chunk_size to control the size of each chunk being pushed.
5. Form the K-shape
This chunking strategy naturally creates a K-shaped distribution in Stack B: smaller numbers accumulate in the middle, and larger numbers are at the ends.
6. Push elements back to A
To sort Stack A:
- Identify the largest element in Stack B.
- Rotate Stack B (rb or rrb) to bring this element to the top.
- Push it to Stack A (pa).
- Repeat until Stack B is empty.

### STRUCTURE:
- push_swap.c can focus on the high-level flow: main calls init_stack, then sort_stack, and then cleans up. It doesn't need to know the messy details of how the stack is built.
- init.c specializes in one job: creating and validating stack_a.
- utils.c contains small, reusable helper functions (ft_error, is_numeric, etc.) that can be used by any other file.
- sort.c: This is the brain of the operation. It contains all the sorting intelligence. It decides which algorithm to use based on the number of elements and implements your efficient k_sort logic to handle larger stacks.
- operations_*.c files: (e.g., operations_push.c, operations_rotate.c, etc.) These files are specialists. Each one implements a specific stack operation (pa, ra, etc.), printing the operation name to standard output. This keeps the code clean and modular.

### LOGIC FLOW
The program executes in a clear, sequential order:

1. Startup (in push_swap.c):
	- The program begins in main.
	- It validates and parses the input arguments, preparing them for processing. It correctly handles both a single quoted string of numbers and multiple separate numbers.

2. Initialization and Normalization (in init.c):
	- init_stack is called to build stack_a. It validates that all inputs are numeric and within integer limits.
	- It checks for any duplicate numbers, which are forbidden.
	- assign_index is then called. This is a critical step where each number is given a "rank" or index based on its final sorted position. This simplifies the sorting logic immensely.

3. Pre-Sort Check (in utils.c):
	- The program calls is_sorted to check if the work is already done. If so, it exits cleanly.

4. Sorting (in sort.c):
	- sort_stack acts as a dispatcher.
	- For 2 or 3 numbers, it uses simple, hard-coded solutions (sa or sort_three).
	- For more numbers, it calls your preferred k_sort function.
	- k_sort intelligently pushes elements to stack_b until only three remain in a.
	- sort_three quickly sorts the remaining elements in a.
	- push_back_to_a then begins its work, efficiently finding the next-highest number in b, rotating it to the top, and pushing it back to a until b is empty.

5. Cleanup (in push_swap.c):
	- Once stack_a is sorted, main performs the final cleanup, calling free_split and free_stack to prevent any memory leaks before exiting.


### Walkthough
Your Push_Swap: A Code Walk-through
Here is a simple, step-by-step explanation of your project that you can use to explain it to others.

Part 1: The Setup - Getting the Numbers Ready
Our program's journey begins in main.c.

Read Input: The program first checks how the numbers are given. It can handle them as separate arguments (./push_swap 1 2 3) or as a single string (./push_swap "1 2 3").
Error Checking (init.c, utils.c): Before we do anything, we must validate the input.
Is it actually a number? (is_numeric)
Is it a duplicate of another number? (check_duplicates)
Is it within the integer limit? (The ft_atol check).
If any check fails, the program prints "Error" and stops.
Create Stack A: Valid numbers are used to build our initial stack, "Stack A," which is a doubly linked list.
The "Magic" Index (assign_index): This is a key step. Instead of working with potentially large or random numbers like 87 or -10, we give each number a simple rank or "index" based on its sorted position. The smallest number gets index 0, the next smallest gets 1, and so on. This makes our sorting logic much simpler.

Part 2: The Sorting Strategy - The "Dispatcher"
Now we move to sort.c, the brain of the operation. The sort_stack function acts as a smart "dispatcher." It looks at the size of the stack and chooses the best algorithm.
If 2 numbers: It just swaps them if needed (sa).
If 3 numbers: It calls sort_three, a simple and efficient function that can sort any three numbers in a maximum of two moves.
If 4 or 5 numbers: It calls sort_small. This function is smart: it finds the smallest numbers, pushes them to Stack B to get them out of the way, sorts the three remaining in Stack A, and then pushes the first ones back.
If more than 5 numbers: It uses our main algorithm, K-Sort.

Part 3: The Main Algorithm - K-Sort (Chunking)
This is the algorithm for large lists. The goal is to move numbers from Stack A to Stack B in an organized way.

Push to B: We loop through Stack A and push every element to Stack B. We use a "chunking" method to decide how to push them.

We imagine the numbers in "chunks" (e.g., the first 20, the next 20, etc.).
If a number belongs to a chunk we've already processed, we push it to B and do an extra rb (rotate B). This sends the smaller numbers deeper into Stack B.
If a number belongs to the current chunk, we just push it to B (pb).
If a number is too large for the current chunk, we rotate Stack A (ra) to deal with it later.
This process naturally creates a semi-organized "K-shape" in Stack B, with the smallest numbers in the middle and the largest at the ends.
Push Back to A: Once Stack A is empty, the final phase begins.

We repeatedly find the number with the highest index (the largest number) in Stack B.
We use the cheapest rotation (rb or rrb) to bring it to the top of Stack B.
We push it to Stack A (pa).
Since we always push the largest remaining number, Stack A is perfectly sorted by the time Stack B is empty.

----------------------------

Double Pointers for ADHD Brains (The Analogy)
Imagine you want me to find a treasure for you.

Scenario 1: Single Pointer (Doesn't Work for This Problem)

You have a piece of paper called stack_a. It's blank (NULL) because you don't know where the treasure is yet.
You give me a photocopy of your blank paper. My copy is called stack.
I go find the treasure (I create a new_node). I write the treasure's location on my photocopy.
I go home. My photocopy is thrown away.
You look at your original paper, stack_a. It's still blank. You still don't know where the treasure is.
This is what happens if stack_add_end takes a single pointer (t_stack *stack). It can't change your original stack_a.

Scenario 2: Double Pointer (This is what we are doing!)

You have a piece of paper called stack_a. It's blank (NULL).
Instead of giving me a copy of the paper, you give me the GPS coordinates to your desk where the paper is sitting. This is the double pointer. My GPS is called stack.
I go find the treasure (new_node).
I use your GPS coordinates (stack) to go to your desk. I find your original piece of paper (*stack).
I write the treasure's location on your original paper. (*stack = new_node;)
I go home.
You look at your paper, stack_a. It now has the treasure's location written on it! You've successfully found the first piece of treasure.
Tying the Analogy to the Code
t_stack *stack_a = NULL;

This is your blank piece of paper in main.
init_stack(&stack_a, ...)

&stack_a is you giving me the GPS coordinates to your paper.
static void stack_add_end(t_stack **stack, ...)

t_stack **stack is my GPS device that holds the coordinates to your paper.
if (!*stack)

*stack means "go to the GPS coordinates and look at the paper".
This line asks: "Is the paper at those coordinates blank?"
*stack = new_node;

This means: "Go to the GPS coordinates, find the paper, and write the new node's address on it."
The double pointer lets the function permanently change the original pointer from main, which is absolutely necessary to build the list starting from an empty state.
