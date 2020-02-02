#include <stdio.h>
#include <stdlib.h>
#include "DS_dec.h"

task* create_task(){
	task* new_task = malloc(sizeof(task));
	printf("Enter the name of the task you want to create: ");scanf("%s", new_task->name);
	printf("%s\n", new_task->name);
	printf("Enter time for task to be completed: ");scanf("%d", &new_task->complete_time);
	printf("%d\n", new_task->complete_time);
	new_task->epochs = 0;
	printf("Enter nice value for task: ");scanf("%d", &new_task->nice_value);
	printf("%d\n", new_task->nice_value);
	return new_task;
}

rb_node* create_node(int data){
	rb_node* node = malloc(sizeof(rb_node));
	node->color = RED;
	node->right = NULL;
	node->left = NULL;
	node->parent = NULL;
	node->data = data;
	node->mytask = create_task();
	return node;
}

rb_tree* tree_init(){
	rb_tree* tree = malloc(sizeof(rb_tree));
	tree->root = NULL;
	tree->size = 0;
	return tree;
}

// display
void display(rb_node* root){
	if(root != NULL){
		display(root->left);
		printf("%d:%d ",root->data, root->color);
		display(root->right);
	}
}

// insert

rb_node* BSTinsert(rb_node* parent,rb_node* root,rb_node* node){
	if (root == NULL){
		root = node;
		root->color = RED;
		root->parent = parent;
		return root;
	}
	
	else if (node->data>root->data){
		root->right = BSTinsert(root,root->right,node);
	}
	
	else if (node->data<root->data){
		root->left = BSTinsert(root,root->left,node);
	}

	return root;
}

void recolor(rb_tree* tree, rb_node* node){
	rb_node* parent = NULL;
	rb_node* grandparent = NULL;
	rb_node* uncle = NULL;
	int temp;

	if (node){	
		// no recoloring if node is root
		if (node != tree->root){
			// as there will be no recoloring then
			if(node->parent != tree->root){
				// to see if there's a violation
				if (node->parent->color == RED){
					// initialize parent and grand parent
					parent = node->parent;
					grandparent = node->parent->parent;

					// find out uncle node
					if (parent == grandparent->left){
						uncle = grandparent->right;
					}
					else{
						uncle = grandparent->left;
					}
					
					// check if uncle's red or black

					// if uncle's red
					if((uncle != NULL) && (uncle->color == RED)){
						uncle->color = BLACK;
						parent->color = BLACK;
						grandparent->color = RED;

						// perform recoloring for node's grandparent
						node = grandparent;
						recolor(tree, node);
					}
					
					// uncle's black
					else{
						
						if((parent->left == node) && (grandparent->left == parent)){
							/*
								CASE 1 - LEFT LEFT CASE
										B
									  /   \
									R		B
							  	  /
								R
							*/
							// if the grandparent is root
							//printf("Entered insert case\n");
							if(grandparent == tree->root){
								tree->root = parent;
							}
							else if(grandparent == grandparent->parent->left){
								grandparent->parent->left = parent;
							}
							else{
								grandparent->parent->right = parent;
							}
							grandparent->left = parent->right;
							if (parent->right){
								parent->right->parent = grandparent;
							}
							parent->right = grandparent;
							parent->parent = grandparent->parent;
							grandparent->parent = parent;
							

							// swapping parent and grand parents colors
							temp = parent->color;
							parent->color = grandparent->color;
							grandparent->color = temp;

							node = parent;
							recolor(tree, node);
						}

						else if((parent->right == node) && (grandparent->left == parent)){
							/*
								CASE 1 - LEFT RIGHT CASE
										B
									  /   \
									R		B
							  	     \
										R
							*/
							// if the grandparent is root
							if(grandparent == tree->root){
								tree->root = node;
							}
							else if(grandparent == grandparent->parent->left){
								grandparent->parent->left = node;
							}
							else{
								grandparent->parent->right = node;
							}
							
							parent->right = node->left;
							parent->parent = node;
							node->parent = grandparent->parent;
							grandparent->left = node->right;
							grandparent->parent = node;
							node->left = parent;
							node->right= grandparent;

							// swapping parent and grand parents colors
							temp = node->color;
							node->color = grandparent->color;
							grandparent->color = temp;

							recolor(tree, node);
						}

						else if((parent->right == node) && (grandparent->right == parent)){
							/*
								CASE 1 - RIGHT RIGHT CASE
										B
									  /   \
									B		R
							  	              \
												R
							*/
							// if the grandparent is root
							if(grandparent == tree->root){
								tree->root = parent;
							}
							else if(grandparent == grandparent->parent->left){
								grandparent->parent->left = parent;
							}
							else{
								grandparent->parent->right = parent;
							}
							grandparent->right = parent->left;
							if (parent->left){
								parent->left->parent = grandparent;
							}
							parent->left = grandparent;
							parent->parent = grandparent->parent;
							grandparent->parent = parent;

							// swapping parent and grand parents colors
							temp = parent->color;
							parent->color = grandparent->color;
							grandparent->color = temp;
							
							node = parent;
							recolor(tree, node);
						}

						else if((parent->right == node) && (grandparent->left == parent)){
							/*
								CASE 1 - RIGHT LEFT CASE
										B
									  /   \
									B		R
							  	          /
										R
							*/
							// if the grandparent is root
							if(grandparent == tree->root){
								tree->root = node;
							}
							else if(grandparent == grandparent->parent->left){
								grandparent->parent->left = node;
							}
							else{
								grandparent->parent->right = node;
							}

							node->parent = grandparent->parent;
							grandparent->parent = node;
							parent->parent=node;

							grandparent->right = node->left;
							node->left = grandparent;
							node->right = parent;

							recolor(tree, node);
						}
					}
				}
			}
		}
	}	
	tree->root->color = BLACK;
}

void insert(rb_tree* tree, rb_node* node){
	if (tree->root == NULL){
		tree->root = node;
		tree->root->color = BLACK;
	}

	else{
		tree->root = BSTinsert(NULL, tree->root, node);
		recolor(tree, node);
	}
} 

// -----------------------------------------------------------------------------------------------------------------------------

// delete

// BST search

rb_node* BSTsearch(rb_node* root, int data){
	if(root == NULL || root->data == data){
		return root;
	}

	else if(root->data < data){
		//printf("gone right\n");
		return BSTsearch(root->right, data);
	}

	//printf("gone left\n");
	return BSTsearch(root->left, data);
}

// BST inorder successor

rb_node* minValueNode(rb_node* node) 
{ 
    rb_node* current = node; 
  
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL) 
        current = current->left; 
  
    return current; 
}

rb_node* fixDoubleBlack(rb_tree* tree, rb_node* root){
	rb_node* temp = root;
	//printf("--------------------------------------------------------------------------------\n");
	if (root != tree->root){
		rb_node *sibling, *parent, *r;
		
		// first find whether root is left or right child, then assign sibbling accordingly	
		// if root is left child
		parent = root->parent;
		if (root == root->parent->left){
			sibling = root->parent->right;
			//printf("sibling is right child.\n");
		}
		else{
			sibling = root->parent->left;
		}

		// printf("parent->data: %d.\n", parent->data);
		// printf("sibling->data: %d.\n", sibling	->data);
		// printf("root->data: %d.\n", root->data);

		// WORKS !!
		// sibling is red color
		if (sibling != NULL && sibling->color == RED){
			
			//printf("Sibling is red.\n");
			sibling->color = BLACK;
			parent->color = RED;

			// if parent is tree->root
			if (parent == tree->root){
				tree->root = sibling;
				//printf("assigned tree->root to sibling.\n");
			}
			//if parent is left node
			else if (parent->parent->left == parent){
				parent->parent->left = sibling;
			}
			// if parent is right node
			else{
				parent->parent->right = sibling;
			}
			//printf("%d\n",tree->root->data);

			// if sibbling is left node, the RIGHT CASE
			if (sibling->parent->left == sibling){
				//printf("Sibling is left node.\n");
				sibling->right->parent = parent;
				parent->left = sibling->right;
				sibling->right = parent;
			}

			// if sibbling is right node, then LEFT CASE
			else{
				//printf("Sibling is right node.\n");
				sibling->left->parent = parent;
				parent->right = sibling->left;
				sibling->left = parent;
			}
			
			sibling->parent = parent->parent;
			parent->parent = sibling;
			//printf("Done.\n");
			
			
			//printf("sibling->left->data: %d.\n", sibling->left->data);
			//printf("parent->parent->data: %d.\n", parent->parent->data);
			//printf("parent->right->data: %d.\n", parent->right->data);

			//root = sibling;
			temp = NULL;

			tree->root = fixDoubleBlack(tree, root);
			// display(tree->root);
			// printf("\n");
			// printf("tree->root->data: %d.\n", tree->root->data);
		}

		// if black sibbling
		else if (sibling!= NULL && sibling->color == BLACK){
			// printf("Now sibling is black.\n");
			// printf("sibling -> data: %d.\n", sibling->data);
			// printf("parent->data: %d.\n", parent->data);
			// printf("parent->color: %d.\n", parent->color);
			// printf("tree->root->data: %d.\n", tree->root->data);
			// printf("tree->root->left->data: %d.\n", tree->root->left->data);
			// printf("tree->root->right->data: %d.\n", tree->root->right->data);
			//printf("tree->root->right->right->color: %d\n", tree->root->right->right->color);
			//printf("tree->root->right->left->color: %d\n", tree->root->right->left->color);
			
			// if sibling is black and both it's children are black
			// WORKS !!
 			if ((sibling->left == NULL || sibling->left->color == BLACK) && (sibling->right == NULL || sibling->right->color == BLACK)){
 				//printf("Both the childern of siblings are black.\n");
				
				// WORKS !!
				// if parent is red, make it black
 				if(parent->color == RED){
					//printf("changed parent color to black.\n");
 					parent->color = BLACK;
					//printf("done.\n");
 				}
 				
				// WORKS !!
				// if parent is black, make it double black and fix it
 				else{
 					sibling->color = RED;
					//printf("parent is now double black, sibling is red.\n");
					tree->root = fixDoubleBlack(tree, parent);
 				}
			}
			//printf("out1.\n");
			// if 1 of siblings children is red
			// WORKS!!
			if((sibling->left != NULL && sibling->left->color == RED) || (sibling->right != NULL && sibling->right->color == RED)){
				
				//printf("Entered if one of the children is red.\n");	
				rb_node *nearChild, *farChild;
				// if sibbling is left node
				// WORKS !!
				if (sibling->parent->left == sibling){
					nearChild = sibling->right;
					farChild = sibling->left;
				}

				// if sibbling is right node
				// WORKS !!
				else{
					nearChild = sibling->left;
					farChild = sibling->right;
				}

				//printf("Now sibling is black.\n");
				// printf("sibling -> data: %d.\n", sibling->data);
				// printf("parent->data: %d.\n", parent->data);
				// printf("parent->color: %d.\n", parent->color);
				// printf("tree->root->data: %d.\n", tree->root->data);
				// printf("tree->root->left->data: %d.\n", tree->root->left->data);
				// printf("tree->root->right->data: %d.\n", tree->root->right->data);
				// printf("nearChild->data: %d\n", nearChild->data);
				// printf("farChild->data: %d\n", farChild->data);
				// printf("nearChild->color: %d\n", nearChild->color);
				// printf("farChild->color: %d\n", farChild->color);

				// WORKS !!
				// if sibling is black, sibling's child far from DB is black, near to DB is red
				if ((farChild == NULL || farChild->color == BLACK) && (nearChild && nearChild->color == RED)){
					//printf("gone in // if sibling is black, sibling's child far from DB is black, near to DB is red\n");
					sibling->color = RED;
					nearChild->color = BLACK;

					// rotate away from DB
					// if sibling is right node, rotate right
					nearChild->parent = sibling->parent;
					sibling->parent = nearChild;
						
					
					if (sibling == sibling->parent->right){
						sibling->left = nearChild->right;
						nearChild->right = sibling;
						sibling = nearChild;
						farChild = sibling->right;
						nearChild = sibling->left;
					}

					// if sibling is left node, rotate left
					else{
						sibling->right = nearChild->left;
						nearChild->left = sibling;
						sibling = nearChild;
						farChild = sibling->left;
						nearChild = sibling->right;
					}
					// rest is same a if sibling black and far child is red, applying next case

				}

				// WORKS !!
				// if sibling is black, far child is red
				if (farChild && farChild->color == RED){
					//printf("Gone in sibling is black, far child is red case\n");
					// swap color of parent and sibling
					int temp_color = parent->color;
					parent->color = sibling->color;
					sibling->color = temp_color;

					// change child's color to black
					farChild->color = BLACK;
					
					// rotate parent in DB's direction

					// printf("parent->data: %d\n", parent->data);
					// printf("sibling->data: %d\n", sibling->data);
					// printf("root->data: %d\n", root->data);
					// printf("farchild->data: %d\n", farChild->data);

					if (parent == tree->root){
						tree->root = sibling;
					}
					else if (parent->parent->left == parent){
						parent->parent->left = sibling;
					}
					else{
						parent->parent->right = sibling;
					}

					sibling->parent = parent->parent;
					parent->parent = sibling;
					if (nearChild){
						nearChild->parent = parent;
					}

					// if sibling is left node
					if (sibling == parent->left){
						parent->left = nearChild;
						sibling->right = parent;
					}

					else{
						parent->right = nearChild;
						sibling->left = parent;
					}
					display(tree->root);

				}

			}
			//printf("out2.\n");
		}
		//printf("out3.\n");
	}
	//printf("returned.\n");
	//printf("--------------------------------------------------------------------------------\n");
	return tree->root;
}


rb_node* restructure(rb_tree* tree, rb_node* root){
	// we are only dealing with nodes that are leaves or have 1 child
		//if node is red -> leaf, black child
		rb_node* temp;

		// WORKS !!
		//printf("root->color: %d\n", root->color);
		if ((root->color == RED) && (root->left == NULL && root->right == NULL)){
			//printf("enter case where root is red and bot null\n");
			/*
					R -> to be deleted
				  /   \
				N       N
			*/
			if (root->parent->left == root){
				root->parent->left = NULL;
			}
			else{
				root->parent->right = NULL;
			}
			free(root);
			root = NULL;
			temp = NULL;
		}
		
		// WORKS !!
		else if((root->color == RED) && (root->left)){
			/*
					R -> to be deleted
				  /   \
				B       N
			*/
			if (root->parent->left == root){
				root->parent->left = root->left;
			}
			else{
				root->parent->right = root->left;
			}
			//temp = root->left;
			root->left->parent == root->parent;
			free(root);
			root = NULL;
		}
		
		// WORKS !!
		else if((root->color == RED) && (root->right)){
			/*
					R -> to be deleted
				  /   \
				N       B
			*/
			if (root->parent->left == root){
				root->parent->left = root->right;
			}
			else{
				root->parent->right = root->right;
			}
			//temp = root->right;
			root->right->parent == root->parent;
			free(root);
			root = NULL;
		}

		else if (root->color == BLACK){

			rb_node* doubleBlack;

			// WORKS !!
			// first see if the child is red
			if ((root->left) && (root->left->color == RED)){
				/*
						B -> to be deleted
					  /   \
					R       N
				*/
				//printf("In correct case2.\n");
					
				if(root == tree->root){
					tree->root = root->left;
					root->left->parent = root->parent;
					tree->root->color = BLACK;
					free(root);
					root = NULL;
				}
				else{
					if (root->parent->left == root){
						root->parent->left = root->left;
					}
					else{
						root->parent->right = root->left;
					}
					temp = root->left;
					temp->parent == root->parent;
					temp->color = BLACK;
				
					free(root);
					root = NULL;
				}
			}
			
			// WORKS !!
			else if ((root->right) && (root->right->color == RED)){
				/*
						B -> to be deleted
					  /   \
					N       R
				*/
				//printf("In correct case1.\n");
					
				if(root == tree->root){
					tree->root = root->right;
					root->right->parent = root->parent;
					tree->root->color = BLACK;
					free(root);
					root = NULL;
				}
				else{
					if (root->parent->left == root){
						root->parent->left = root->right;
					}
					else{
						root->parent->right = root->right;
					}
					temp = root->right;
					temp->parent == root->parent;
					temp->color = BLACK;
				
					free(root);
					root = NULL;
				}
			}

			// if it's a black leaf or black node with a black child, deciding what is double black
			
			// WORKS?
			else if (root->left == NULL && root->right == NULL){
				/*
						B -> to be deleted
					  /   \
					N       N
				*/
				//printf("Gone to needed case.\n");
				if (root == tree->root){
					tree->root = NULL;
					free(root);
					root = NULL;
				}
				else{
					temp = create_node(0);
					temp->parent = root->parent;
					
					if (root->parent->left == root){
						root->parent->left = temp;
					}
					else{
						root->parent->right = temp;
					}
					
					free(root);
					root = NULL;
					
					tree->root = fixDoubleBlack(tree, temp);

					//printf("After fixDoubleBlack in restructure: ");
					// display(tree->root);
					// printf("\n");
					// printf("tree->root->data: %d\n", tree->root->data);
					
					//temp = NULL;
					//temp = BSTsearch(tree->root, 0);
					//printf("%d\n", temp);
					//printf("temp->data: %d\n", temp->data);

					if (temp->parent->left == temp){
					 	temp->parent->left = NULL;
					}
					else{
					 	temp->parent->right = NULL;
					}
					free(temp);
					temp = NULL;

					//printf("After fixDoubleBlack in restructure: ");
					display(tree->root);
					printf("\n");
					printf("tree->root->data: %d\n", tree->root->data);
				}
			}

			// WORKS !!
			else if (root->left && root->left->color == BLACK){
				/*
						B -> to be deleted
					  /   \
					B       N
				*/
				//printf("Entered 2 Black, Blak left.\n");
				//printf("root->data: %d\n", root->data);
				//printf("tree->root->right->right->color: %d\n", tree->root->right->right->color);
				//printf("tree->root->right->left->color: %d\n", tree->root->right->left->color);
				
				if (root == tree->root){
					tree->root = root->left;
					free(root);
					root = NULL;
				}
				//doubleBlack = root->left;
				else{
					temp = root->left;
					temp->parent = root->parent;
					if (root->parent->left == root){
					 	root->parent->left = temp;
					}
					else{
					 	root->parent->right = temp;
					}
					free(root);
					root = NULL;
					tree->root = fixDoubleBlack(tree, temp);
				}
			}

			// WORKS!!
			else if(root->right && root->right->color == BLACK){
				/*
						B -> to be deleted
					  /   \
					N       B
				*/	
				//printf("Entered 2 Black, Blak right.\n");
				if (root == tree->root){
					tree->root = root->right;
					free(root);
					root = NULL;
				}
				//doubleBlack = root->left;
				else{
					temp = root->right;
					temp->parent = root->parent;
					if (temp->parent->left == root){
					 	temp->parent->left = temp;
					}
					else{
					 	temp->parent->right = temp;
					}
					free(root);
					root = NULL;
					tree->root = fixDoubleBlack(tree, temp);
				}
			}

		}
		printf("Displaying from end of restructure.\n");
		display(tree->root);
		printf("\n");
		return tree->root;
}

rb_node* delete(rb_tree* tree, rb_node* root, int data){
    // base case 
    if (root == NULL) return root; 
  
    // If the key to be deleted is smaller than the root's key, 
    // then it lies in left subtree 
    if (data < root->data) 
        delete(tree, root->left, data); 
  
    // If the key to be deleted is greater than the root's key, 
    // then it lies in right subtree 
    else if (data > root->data) 
        delete(tree, root->right, data); 
  
    // if key is same as root's key, then This is the node 
    // to be deleted 
    else
    { 
        rb_node* temp;
		if (root->left && root->right){
			// node with two children: Get the inorder successor (smallest 
        	// in the right subtree) 
        	temp = minValueNode(root->right); 
  
        	// Copy the inorder successor's content to this node 
        	root->data = temp->data;
  
        	// Delete the inorder successor 
        	delete(tree, root->right, temp->data);
		}

		else{
			tree->root = restructure(tree, root);
		}
    }
    
    return tree->root; 
}