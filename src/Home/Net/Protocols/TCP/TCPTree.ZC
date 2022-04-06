/***************************************************

TCP Bound/Connected Socket Tree Functions

***************************************************/

CTCPTreeNode *TCPTreeNodeInit()
{ // init new empty tree/node. Init socket queue head links.
	CTCPTreeNode *tree_node = CAlloc(sizeof(CTCPTreeNode));

	tree_node->queue = CAlloc(sizeof(CTCPTreeQueue)); // CQueue vs CTCPTreeQueue ?...
	QueueInit(tree_node->queue);

	return tree_node;
}

U0 TCPTreeNodeAdd(CTCPTreeNode *node, CTCPTreeNode *tree)
{ // using temp and last allows avoiding recursion and non-growing stack issues.
	BSTAdd(node, tree);
}

CTCPTreeNode *TCPTreeNodeParamAdd(I64 port, CTCPTreeNode *tree)
{ // add a node using params, return pointer to the node
	CTCPTreeNode *result = TCPTreeNodeInit;

	result->value = port;

	TCPTreeNodeAdd(result, tree);

	return result;
}

CTCPTreeNode *TCPTreeNodeParamInit(I64 port)
{
	CTCPTreeNode *result = TCPTreeNodeInit;

	result->value = port;

	return result;
}

CTCPTreeNode *TCPTreeNodeFind(I64 port, CTCPTreeNode *tree)
{
	return BSTFind(port, tree);
}

CTCPTreeNode *TCPTreeNodePop(I64 port, CTCPTreeNode *tree)
{ // Pops whole sub-tree, original tree loses whole branch.
	return BSTPop(port, tree);
}

CTCPTreeNode *TCPTreeNodeSinglePop(I64 port, CTCPTreeNode *tree)
{	// Pop a tree off, then add back in its sub-trees to main tree.
	// Original node sub-tree links are cleared.

	return BSTSinglePop(port, tree);
}

U0 TCPTreeNodeQueueAdd(CTCPSocket *socket, CTCPTreeNode *node)
{
	CTCPTreeQueue *new_entry = CAlloc(sizeof(CTCPTreeQueue));

	new_entry->socket = socket;

	QueueInsert(new_entry, node->queue->last);
}

CTCPTreeQueue *TCPTreeNodeQueueSocketFind(CTCPSocket *socket, CTCPTreeNode *node)
{
	CTCPTreeQueue *temp_queue;

	temp_queue = node->queue->next;
	while (temp_queue != node->queue)
	{
		if (temp_queue->socket == socket)
			return temp_queue;
		temp_queue = temp_queue->next;
	}

	return NULL;
}

CTCPTreeQueue *TCPTreeNodeQueueSocketSinglePop(CTCPSocket *socket, CTCPTreeNode *node)
{ // search by socket, pop a single TCPTreeQueue off the node, return popped queue.
	CTCPTreeQueue *temp_queue = TCPTreeNodeQueueSocketFind(socket, node);

	if (temp_queue)
	{
		QueueRemove(temp_queue);

	}

	return temp_queue; // if not found, NULL.
}

CTCPTreeQueue *TCPTreeNodeQueueIPV4Find(U32 address, CTCPTreeNode *node, Bool specific=FALSE)
{	// address should be pulled from an instance of CIPV4Address (TODO... double check what bit order we're in ?)
	// use TRUE or FALSE in specific arg to dictate how to handle INADDR_ANY.

	CTCPTreeQueue		*temp_queue = node->queue->next;
	CSocketAddressIPV4	*temp_ip;

	while (temp_queue != node->queue)
	{
		if (temp_queue->socket->destination_address.family == AF_INET)
		{
			temp_ip = &temp_queue->socket->destination_address;
			NetLog("TCPTreeNodeQueueIPV4Find: Comparing:     addr, nodequeue addr: %08X, %08X",
					address, temp_ip->address.address);

			if (temp_ip->address.address == address)
			{
				NetLog("TCPTreeNodeQueueIPV4Find: Address match: addr, nodequeue addr: %08X, %08X ",
						address, temp_ip->address.address);

				return temp_queue;
			}
		}
		else
			NetErr("TCPTreeNodeQueueIPV4Find: Skipped iteration of a non AF_INET family: %0X",
					temp_queue->socket->destination_address.family);

		temp_queue = temp_queue->next;
	}

	if (!specific)
	{
		temp_queue = node->queue->next;
		NetDebug("TCPTreeNodeQueueIPV4Find: Exact match not found, looking for an INADDR_ANY address.");

		while (temp_queue != node->queue)
		{
			if (temp_queue->socket->destination_address.family == AF_INET)
			{
				temp_ip = &temp_queue->socket->destination_address;
				NetLog("TCPTreeNodeQueueIPV4Find: Comparing:     addr, nodequeue addr: %08X, %08X",
						address, temp_ip->address.address);

				if (temp_ip->address.address == INADDR_ANY)
				{
					NetLog("TCPTreeNodeQueueIPV4Find: Address match: addr, nodequeue addr: %08X, %08X ",
							address, temp_ip->address.address);

					return temp_queue;
				}
			}
			else
				NetErr("TCPTreeNodeQueueIPV4Find: Skipped iteration of a non AF_INET family: %0X",
						temp_queue->socket->destination_address.family);

			temp_queue = temp_queue->next;
		}
	}


	return NULL;
}

