# Completely Fair Scheduler

In this project, I try to build the completly fair scheduler used to schedule CPU processes in the linux kernel using a Red Black tree - gives `O(log(n))` time for insertion, deletion and search operations.


The project aims to simulate the working of the Completely fair scheduler in the linux kernel, which primarily schedules Tasks (processes) for execution in the CPU.


It works on the concept of Ideal fair scheduler with priorities implemented using a parameter called `virtual runtime`. Each task has a `virtual runtime`, which updates each time after a task has been run by the CPU, according to the `nice value` of the task, which is multiplied to the task’s virtual runtime to update it.


To run the file, download the code, navigate to the directory the files are in the commnand line, run command `make` in the directory that it is situated.
Then run the generated `test` file and follow the instructions for the simulation.


An example: 

```
$ make
cc    -c -o DS_main.o DS_main.c
cc    -c -o DS_def.o DS_def.c
gcc -o test DS_main.o DS_def.o

$ ./test
inorder:
Enter the number of tasks you're going to enter: 3
---------------- NEW TASK ENTRY ------------------
Enter virual runtime of new task: 1200
Enter the name of the task you want to create: first_task
first_task
Enter time for task to be completed: 1200
1200
Enter nice value for task: 1
1
```

Similarly, you enter the other tasks.
The output displays each CPU timer interrupt and the status of the tree until all tasks are completed, this is how the last timer interrupt looks:

```
-------------------TIMER INTERRUPT--------------------
Before insert:

After insert:
100:1
tree->size: 1
minVruntime entered root
time slice computed: 4000
Ran task: third_task, for 4000 time
Updated runtime in task
Upadated complete time in task: -3900
minVruntime->data: 8100
8100:1
Displaying from end of restructure.
deleted task with minVruntime from tree

completed All tasks.
```
