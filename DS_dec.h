enum Color {RED, BLACK};

typedef struct rb_node rb_node;

typedef struct task{
	char name[15];
	int complete_time;
	int epochs;
	int nice_value;
}task;

struct rb_node{
	int color;
	struct rb_node* right;
	struct rb_node* left;
	struct rb_node* parent;
	task* mytask;
	int data;
};

typedef struct rb_tree{
	rb_node* root;
	int size;
}rb_tree;

// creates task for CFS
task* create_task();

// creates node to be added to tree 
rb_node* create_node(int data);

// initializes the tree
rb_tree* tree_init();

// prints tree inorder
void display(rb_node* root);

// insert funtions

// performs BST insertion
rb_node* BSTinsert(rb_node* parent,rb_node* root,rb_node* node);

// recolors and restructues the tree after insertion as BST
void recolor(rb_tree* tree, rb_node* node);

// wrapper function for above 2 insertion functions
void insert(rb_tree* tree, rb_node* node);

// delete

// BST search
rb_node* BSTsearch(rb_node* root, int data);

// BST inorder successor
rb_node* minValueNode(rb_node* node);

// fixes tree, when a double black node is entered
rb_node* fixDoubleBlack(rb_tree* tree, rb_node* root);

// restunctures treeafter BST Deletion
rb_node* restructure(rb_tree* tree, rb_node* root);

// wrapper function for delete
rb_node* delete(rb_tree* tree, rb_node* root, int data);