#include <stdio.h>
#include <stdlib.h>
#include "DS_dec.h"

int main(){
    // CFS

    // INC tree->size EACH TIME YOU INSERT
    // DEC tree->size EACH TIME YOU DELETE

    // Each task has an vr_runtime, at each interupt,
    // if there's a new task, if there is - add that task (TASK CAN'T HAVE <= 0 VRUNTIME), compute timeslice, run task with min_vr_runtime, update the runtime
    // if updated runtime >= complete time, delete task, interrupt
    // else vr_time = update runtime
    // else there's no new task - complete all remaining tasks till tree is empty

	// creating and initializing the tree
	rb_tree *tree = tree_init();

	printf("inorder: ");
	display(tree->root);
	printf("\n");
	
	rb_node* minVruntime;
	int timeToRun;
	int n;
	printf("Enter the number of tasks you're going to enter: ");scanf("%d", &n);
	rb_node* arr[n];
	int i;
	int data;
	for (i = 0; i<n; i++){
		printf("\n---------------- NEW TASK ENTRY ------------------\n");
		printf("Enter virual runtime of new task: ");scanf("%d", &data);
		//node = create_node(data);printf("Enter the virtual runtime for the task: ");
		arr[i] = create_node(data);
	}

	i =0;
	do{
		printf("\n-------------------TIMER INTERRUPT--------------------\n");
		
		// search for a new task
		if(i<n){
			printf("Before insert:\n");
			display(tree->root);
			printf("\n");
			insert(tree, arr[i]);
			printf("After insert:\n");
			display(tree->root);
			printf("\n");
			tree->size++;
			printf("tree->size: %d\n",tree->size);
			i++;
		}
		// find task with min_vruntime
		
		if (tree->root){
			if (tree->root->left){
				printf("minVruntime entered left\n");
				minVruntime = minValueNode(tree->root->left);
			}
			else if(tree->root->right){
				printf("minVruntime entered right\n");
				minVruntime = minValueNode(tree->root->right);
			}
			else{
				printf("minVruntime entered root\n");
				minVruntime = tree->root;
			}

			// calculate time minVruntime task should run for = (epoch time)(4ms) / tree->size
			timeToRun = 4000/tree->size;
			printf("time slice computed: %d\n", timeToRun);

			printf("Ran task: %s, for %d time\n", minVruntime->mytask->name, timeToRun);

			// add time to minVruntime
			minVruntime->data += (timeToRun)*(minVruntime->mytask->nice_value);
			printf("Updated runtime in task\n");
			
			// reduce time for completetime
			minVruntime->mytask->complete_time -= timeToRun;
			printf("Upadated complete time in task: %d\n", minVruntime->mytask->complete_time);
			// delete node from tree
			printf("\n");
			printf("minVruntime->data: %d", minVruntime->data);
			printf("\n");
			display(tree->root);
			printf("\n");
			tree->root = delete(tree, tree->root, minVruntime->data);
			printf("\n");
			printf("deleted task with minVruntime from tree\n");
			// reinsert node if task not completed
			if (minVruntime->mytask->complete_time > 0){
				insert(tree, minVruntime);
				printf("inserted task minVruntime");
			}
			else{
				tree->size--;
			}
			printf("\n");
			display(tree->root);
			printf("\n");
		}
	}while(tree->root || i<n);

	printf("completed All tasks.\n");
	return 0;
}