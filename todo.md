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
