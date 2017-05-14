#include "path.h"
#include "Application2D.h"

//delete all of the nodes
Path::~Path()
{
	size_t nodeSize = nodes.size();

	for (size_t i = 0; i < nodeSize; i++)
	{
		delete nodes[i];
	}
}

//creates nodes and connections by examining a container
void Path::generateNodesRecursive(Container* container, bool subLevel, Node* prevNode)
{
	if (container->leftChild == nullptr || container->rightChild == nullptr)
	{
		return;
	}

	Node* leftNode = new Node{};

	//node goes in the middle of the left sub-container
	leftNode->position.x = floorf((container->leftChild->minX + container->leftChild->maxX) / 2.0f);
	leftNode->position.y = floorf((container->leftChild->minY + container->leftChild->maxY) / 2.0f);

	Node* rightNode = new Node{};

	//node goes in the middle of the right sub-container
	rightNode->position.x = floorf((container->rightChild->minX + container->rightChild->maxX) / 2.0f);
	rightNode->position.y = floorf((container->rightChild->minY + container->rightChild->maxY) / 2.0f);
	
	//connections need to be made to the prevNode if it exists
	if (subLevel)
	{ 
		Connection leftPrev = Connection{}; //connections that go back and forwards
		Connection prevLeft = Connection{};
		Connection rightPrev = Connection{};
		Connection prevRight = Connection{};

		//calulate cost of connections from squaredDistance
		float leftCost = (leftNode->position - prevNode->position).sqrMagnitude();
		leftPrev.destination = prevNode;
		prevLeft.destination = leftNode;

		leftPrev.cost = leftCost;
		prevLeft.cost = leftCost;

		float rightCost = (rightNode->position - prevNode->position).sqrMagnitude();
		rightPrev.destination = prevNode;
		prevRight.destination = rightNode;

		rightPrev.cost = rightCost;
		prevRight.cost = rightCost;

		prevNode->conns.push_back(prevLeft);
		prevNode->conns.push_back(prevRight);

		leftNode->conns.push_back(leftPrev);
		rightNode->conns.push_back(rightPrev);
	}
	else //only connections between the left and right nodes need to be made
	{
		Connection leftRight = Connection{};
		Connection rightLeft = Connection{};

		float cost = (rightNode->position - leftNode->position).sqrMagnitude();
		leftRight.destination = rightNode;
		rightLeft.destination = leftNode;

		leftRight.cost = cost;
		rightLeft.cost = cost;

		leftNode->conns.push_back(leftRight);
		rightNode->conns.push_back(rightLeft);
	}


	nodes.push_back(leftNode);
	nodes.push_back(rightNode);

	//call the function recursively on each sub-container
	generateNodesRecursive(container->leftChild, true, leftNode);
	generateNodesRecursive(container->rightChild, true, rightNode);
	
}

//add an offset to all nodes
void Path::addOffset(Vector2 offset)
{
	size_t nodeSize = nodes.size();

	//iterate through all of the nodes
	for (size_t i = 0; i < nodeSize; i++)
	{
		//add the offset to the node's position
		nodes[i]->position += offset;
	}
}

//scale the path by a certain factor
void Path::scale(float scalar)
{
	size_t nodeSize = nodes.size();

	//iterate through all of the nodes
	for (size_t i = 0; i < nodeSize; i++)
	{
		//multiply the position
		nodes[i]->position = nodes[i]->position * scalar;

		size_t connSize = nodes[i]->conns.size();

		//iterate through all of the connections
		for (size_t j = 0; j < connSize; j++)
		{
			//multiply the cost of the connections
			nodes[i]->conns[j].cost *= scalar;
		}
	}
}

//sets all the nodes as not transversed
void Path::resetNodes()
{
	size_t nodeSize = nodes.size();

	//iterate through all the nodes
	for (size_t i = 0; i < nodeSize; i++)
	{
		nodes[i]->transversed = false;
	}
}

//find the shortest path between two nodes
std::vector<Node*> Path::calculatePath(Node * begin, Node * end)
{

	begin->transversed = true;

	std::vector<Node*> open;

	//add the starting node to be searched
	open.push_back(begin);

	bool foundEnd = false;

	//continue searching nodes as long as there is another node that hasn't been discovered yet
	while (open.size() > 0)
	{

		size_t connSize = open[0]->conns.size();
		
		//iterate through all the connections
		for (size_t i = 0; i < connSize; i++)
		{
			Node* next = open[0]->conns[i].destination;
			float cost = open[0]->carriedScore + open[0]->conns[i].cost;

			//if the node hasn't been searched yet or it's given score is higher than the incoming score
			if (!next->transversed || cost < next->carriedScore)
			{
				next->transversed = true;
				next->carriedScore = cost;

				open.push_back(next);
			}

			//found the end, stop searching for it
			if (next == end)
			{
				foundEnd = true;
				break;
			}
		}

		//break out of this loop if the end is found
		if (foundEnd)
		{
			break;
		}

		open.erase(open.begin());
	}

	//the end was not found, return an empty list
	if (!foundEnd)
	{
		resetNodes();
		return std::vector<Node*>{};
	}

	std::vector<Node*> path;

	Node* back = end;

	path.push_back(back);

	//backtrack to the start
	while (back != begin)
	{
		Node* bestNode = nullptr;
		float smallestScore = std::numeric_limits<float>().max();

		size_t connSize = back->conns.size();

		//iterate through all the connections
		for (size_t i = 0; i < connSize; i++)
		{
			Node* next = back->conns[i].destination;
			float score = next->carriedScore;

			//if the node has been searched and it's score is the lower than the current lowest score
			if (next->transversed && score < smallestScore)
			{
				bestNode = next;
				smallestScore = score;
			}
		}

		back = bestNode;

		//add the node
		path.push_back(back);
	}

	resetNodes();
	return path;
}

void Path::render(Application2D * appPtr)
{
	size_t nodeSize = nodes.size();

	//iterate through all of the nodes
	for (size_t i = 0; i < nodeSize; i++)
	{
		size_t connSize = nodes[i]->conns.size();

		//iterate through all of the connections
		for (size_t j = 0; j < connSize; j++)
		{
			Vector2 start = nodes[i]->position;
			Vector2 end = nodes[i]->conns[j].destination->position;
			appPtr->m_2dRenderer->drawLine(start.x, start.y, end.x, end.y, 2.0f, 0.0f);
		}
	}
}

