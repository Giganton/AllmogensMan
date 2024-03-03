/*#include "TraitTree.h"
#include <time.h>

TraitTree::TraitTree(TraitTreeType type)
{
	treeShape = type;
	switch (type)
	{
	case TraitTreeType::triangle:
		createEmptyTriangleTree();
		break;
	}
}

TraitTree::TraitTree(const TraitTree& cp)
{
	unsigned int i;
	nrOfNodes = cp.nrOfNodes;
	treeShape = cp.treeShape;
	if (nrOfNodes > 0)
	{
		for (i = 0; i < nrOfNodes; i++)
		{
			allNodes[i] = cp.allNodes[i];
		}
		addressTree();
	}
}

TraitTree& TraitTree::operator=(const TraitTree as)
{
	unsigned int i;
	nrOfNodes = as.nrOfNodes;
	treeShape = as.treeShape;
	if (nrOfNodes > 0)
	{
		for (i = 0; i < nrOfNodes; i++)
		{
			allNodes[i] = as.allNodes[i];
		}
		addressTree();
	}

	return *this;
}

void TraitTree::createEmptyTriangleTree()
{
	TraitTreeNode bottomNode1(1,3), bottomNode2(1,4), bottomNode3(1,5);
	TraitTreeNode middleNode1(2,1), middleNode2(2,2);
	TraitTreeNode topNode(3,0);

	allNodes[0] = topNode;
	allNodes[1] = middleNode1;
	allNodes[2] = middleNode2;
	allNodes[3] = bottomNode1;
	allNodes[4] = bottomNode2;
	allNodes[5] = bottomNode3;

	nrOfNodes = 6;

	addressTriangleTree();
}

void TraitTree::addressTree()
{
	switch (treeShape)
	{
	case TraitTreeType::triangle:
		addressTriangleTree();
		break;
	default:
		throw new std::exception();
	}
}

void TraitTree::clearConnections()
{
	unsigned int i;
	for (i = 0; i < nrOfNodes; i++)
	{
		allNodes[i].clearConnections();
	}
}

void TraitTree::addressTriangleTree()
{
	nodeHeads.clear();
	clearConnections();

	allNodes[1].connect(&allNodes[3]);
	allNodes[1].connect(&allNodes[4]);
	allNodes[2].connect(&allNodes[4]);
	allNodes[2].connect(&allNodes[5]);

	allNodes[0].connect(&allNodes[1]);
	allNodes[0].connect(&allNodes[2]);

	nodeHeads.push_back(&allNodes[0]);

}

std::vector<Trait*> TraitTree::copyAllTraits() //farlig funktion
{
	unsigned int i;
	std::vector<Trait*> retVal;
	for (i = 0; i < nrOfNodes; i++)
	{
		if (!allNodes[i].isEmpty())
		{
			retVal.push_back(allNodes[i].cloneTrait());
		}
	}
	return retVal;
}
std::vector<Trait*> TraitTree::getAllTraits() //farlig funktion (om adresser ändras)
{
	unsigned int i;
	std::vector<Trait*> retVal;
	for (i = 0; i < nrOfNodes; i++)
	{
		if (!allNodes[i].isEmpty())
		{
			retVal.push_back(allNodes[i].cloneTrait());
		}
	}
	return retVal;
}

TraitTagTree TraitTree::getVisualTree()
{
	unsigned int i;
	TraitTagTree retVal;
	retVal.type = treeShape;
	for (i = 0; i < MAX_NODES; i++)
	{
		retVal.allNodes[i] = allNodes[i].getTraitTag();
	}
	return retVal;
}

void TraitTree::addTrait(Trait* trait, int nodeID)
{
	findNode(nodeID)->setTrait(trait);
}

int TraitTree::getLevelupSlot()
{
	std::vector<int> allOpenSlots = getAllOpenSlots();
	int randIndex = rand() % allOpenSlots.size();
	return allOpenSlots.at(randIndex);
}

/*std::vector<TraitTreePath> TraitTree::getAllOpenSlots()
{
	unsigned int i;
	std::vector<TraitTreePath> paths;
	std::vector<int> slotIDs;
	for (i = 0; i < nodeHeads.size(); i++)
	{
		TraitTreePath headNr = TraitTreePath();
		headNr.indexPath.push_back(i);

		std::vector<TraitTreePath> tempPaths = forkTraitPath(headNr, nodeHeads.at(i)->findOpenSlots());

		paths.insert(paths.end(), tempPaths.begin(), tempPaths.end());
	}
	for (i = 0; i < paths.size(); i++)
	{
		slotIDs.push_back(getTreeNode(paths.at(i))->getID());
	}

	std::vector<std::pair<int, TraitTreePath>> zippedPath = zipIDPath(slotIDs, paths);
	std::sort(zippedPath.begin(), zippedPath.end());
	zippedPath.erase( std::unique(zippedPath.begin(), zippedPath.end()) , zippedPath.end());

	std::pair<std::vector<int>, std::vector<TraitTreePath>> idPaths = unzipIDPath(zippedPath);
	return idPaths.second;
}*//*
std::vector<int> TraitTree::getAllOpenSlots()
{
	std::vector<int> retVal;
	unsigned int i, j;
	for (i = 0; i < nrOfNodes; i++)
	{
		if (allNodes[i].isEmpty())
		{
			std::vector<TraitTreeNode*> subNodes = allNodes[i].getSubNodes();
			bool allSubsFilled = true;
			for (j = 0; j < subNodes.size(); j++)
			{
				allSubsFilled = allSubsFilled & !subNodes.at(j)->isEmpty();
			}
			if (allSubsFilled)
			{
				retVal.push_back(allNodes[i].getID());
			}
		}
	}
	return retVal;
}


TraitTreeNode* TraitTree::findNode(int id)
{
	unsigned int i;
	for (i = 0; i < nrOfNodes; i++)
	{
		if (allNodes[i].getID() == id)
		{
			return &allNodes[i];
		}
	}
}

TraitTreeNode* TraitTree::getTreeNode(TraitTreePath address)
{
	int index = address.takeFirstStep();
	return nodeHeads.at(index)->findNode(address);
}

std::vector<std::pair<int, TraitTreePath>> TraitTree::zipIDPath(std::vector<int> ids, std::vector<TraitTreePath> paths)
{
	std::vector<std::pair<int, TraitTreePath>> retVal;
	unsigned int i;
	for (i = 0; i < ids.size(); i++)
	{
		retVal.push_back(std::make_pair( ids.at(i) , paths.at(i)));
	}
	return retVal;
}

std::pair<std::vector<int>, std::vector<TraitTreePath>> TraitTree::unzipIDPath(std::vector<std::pair<int, TraitTreePath>> zipped)
{
	std::vector<int> ids;
	std::vector<TraitTreePath> paths;
	unsigned int i;
	for (i = 0; i < zipped.size(); i++)
	{
		ids.push_back(zipped.at(i).first);
		paths.push_back(zipped.at(i).second);
	}
	return std::make_pair(ids, paths);
}*/