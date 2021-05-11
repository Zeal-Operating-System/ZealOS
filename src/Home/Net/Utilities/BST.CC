/***************************************************

Binary Search Tree (BST) Implementation

***************************************************/

class CBST
{
	CBST	*left;
	CBST	*right;
	I64		 value;
};

CBST *BSTInit()
{
	return CAlloc(sizeof(CBST));
}

U0 BSTAdd(CBST *node, CBST *tree)
{ // using temp and last allows avoiding recursion and non-growing stack issues.
	CBST *temp_tree = tree;
	CBST *last_tree = temp_tree;

	while (temp_tree)
	{ // loop ends when temp_tree hits a NULL node.
		if (node->value < temp_tree->value)
		{ // if node smaller, go left
			last_tree = temp_tree;
			temp_tree = temp_tree->left;
		}
		else
		{ // if node equal or larger, go right
			last_tree = temp_tree;
			temp_tree = temp_tree->right;
		}
	}
	// once while loop ends, this results in last_tree
	// being the resulting tree to store the node inside of.

	// recompute the direction and set.
	if (node->value < last_tree->value)// if node smaller, go left
		last_tree->left = node;
	else // if node equal or larger, go right
		last_tree->right = node;
}

CBST *BSTParamAdd(I64 value, CBST *tree)
{ // add a node using params, return pointer to the node
	CBST *result = BSTInit;

	result->value = value;

	BSTAdd(result, tree);

	return result;
}

CBST *BSTParamInit(I64 value)
{
	CBST *result = BSTInit;

	result->value = value;

	return result;
}

CBST *BSTFind(I64 value, CBST *tree)
{
	CBST *temp_tree = tree;

	while (temp_tree)
	{
		if (value < temp_tree->value) // if value smaller, go left
			temp_tree = temp_tree->left;
		else if (value > temp_tree->value) // if value larger, go right
			temp_tree = temp_tree->right;
		else // if value equal, match found.
			break;
	}
	return temp_tree; // ! NULL if not found.
}

CBST *BSTPop(I64 value, CBST *tree)
{ // mimics TreeNodeFind. pops whole sub-tree, original tree loses whole branch.
	CBST	*parent_tree	= tree;
	CBST	*temp_tree		= parent_tree;
	Bool	 is_left		= FALSE;
	Bool	 is_right		= FALSE;

	while (temp_tree)
	{
		if (value < temp_tree->value)
		{
			parent_tree	= temp_tree;
			temp_tree	= temp_tree->left;
			is_right	= FALSE;
			is_left		= TRUE;
		}
		else if (value > temp_tree->value)
		{
			parent_tree	= temp_tree;
			temp_tree	= temp_tree->right;
			is_right	= TRUE;
			is_left		= FALSE;
		}
		else // if value equal, match found.
			break;	
	}

	if (temp_tree)
	{ //if we found it, clear its parents link to the node
		if (is_left)
		{
			parent_tree->left = NULL;
		}
		else if (is_right)
		{
			parent_tree->right = NULL;
		}
	}

	return temp_tree; // NULL if not found.
}

CBST *BSTSinglePop(I64 value, CBST *tree)
{	// pop a tree off, then add back in its sub-trees to main tree.
	// original node sub-trees are cleared.

	CBST *node	= BSTPop(value, tree);
	CBST *left	= node->left;
	CBST *right	= node->right;

	if (node)
	{
		if (left)
		{ // if node has left tree, add the tree
			BSTAdd(left, tree);
			node->left = NULL;
		}
		if (right)
		{ // if node has right tree, add the tree.
			BSTAdd(right, tree);
			node->right = NULL;
		}
	}

	return node;
}