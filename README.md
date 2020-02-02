# Completely Fair Scheduler
In this project, I try to build the completly fair scheduler used to schedule CPU processes in the linux kernel using a Red Black tree - gives `O(log(n))` time for insertion, deletion and search operations.

The project aims to simulate the working of the Completely fair scheduler in the linux kernel, which primarily schedules Tasks (processes) for execution in the CPU.

It works on the concept of Ideal fair scheduler with priorities implemented using a parameter called `virtual runtime`. Each task has a `virtual runtime`, which updates each time after a task has been run by the CPU, according to the `nice value` of the task, which is multiplied to the task’s virtual runtime to update it.

To run the file, download the code, navigate to the directory the files are in the commnand line, run command `make` in the directory that it is situated.
Then run the generated `test` file and follow the instructions for the simulation.
