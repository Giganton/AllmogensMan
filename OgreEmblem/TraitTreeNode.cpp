/*#include "TraitTreeNode.h"


std::vector<TraitTreePath> forkTraitPath(TraitTreePath path1, std::vector<TraitTreePath> fork)
{
	std::vector<TraitTreePath> retVal;
	if (fork.empty())
	{
		retVal.push_back(path1);
		return retVal;
	}
	unsigned int i;
	for (i = 0; i < fork.size(); i++)
	{
		TraitTreePath tempPath = path1;
		tempPath.concatenatePaths(fork.at(i));
		retVal.push_back(tempPath);
	}
	return retVal;
}

void TraitTreePath::concatenatePaths(TraitTreePath newPath)
{
	indexPath.insert(indexPath.end(), newPath.indexPath.begin(), newPath.indexPath.end());
}

void TraitTreePath::removeFirstStep()
{
	if (indexPath.empty())
	{
		throw new std::exception();
	}
	else
	{
		indexPath.erase(indexPath.begin());
	}
}

int TraitTreePath::takeFirstStep()
{
	int retVal = indexPath.at(0);
	removeFirstStep();
	return retVal;
}

TraitTreeNode::~TraitTreeNode()
{
	delete traitSlot;
}

TraitTreeNode::TraitTreeNode(const TraitTreeNode& cp)
{
	empty = cp.empty;
	delete(traitSlot);
	if (!empty)
	{
		traitSlot = cp.traitSlot->clone();
	}
	else
	{
		traitSlot = nullptr;
	}
	subNodes = cp.subNodes;
	level = cp.level;
	ID = cp.ID;
}

TraitTreeNode& TraitTreeNode::operator=(const TraitTreeNode as)
{
	empty = as.empty;
	delete(traitSlot);
	if (!empty)
	{
		traitSlot = as.traitSlot->clone();
	}
	else
	{
		traitSlot = nullptr;
	}
	subNodes = as.subNodes;
	level = as.level;
	ID = as.ID;

	return *this;
}
/*
std::vector<TraitTreePath> TraitTreeNode::findOpenSlots()
{
	std::vector<TraitTreePath> retVal;
	unsigned int i;
	if (empty)
	{
		bool allFilled = true;
		for (i = 0; i < subNodes.size(); i++)
		{
			if (subNodes.at(i)->isEmpty())
			{
				allFilled = false;
				TraitTreePath ongoingPath;
				ongoingPath.indexPath.push_back(i);
				std::vector<TraitTreePath> forkedPaths = forkTraitPath(ongoingPath, subNodes.at(i)->findOpenSlots());
				
				retVal.insert(retVal.end() , forkedPaths.begin() , forkedPaths.end());
			}
		}
		if (allFilled)
		{
			return retVal;
		}
	}
	else
	{
		throw new std::exception();
	}
}
*//*
TraitTreeNode* TraitTreeNode::findNode(TraitTreePath address)
{
	if (address.indexPath.empty())
	{
		return this;
	}
	else
	{
		int index = address.takeFirstStep();
		return subNodes.at(index)->findNode(address);
	}
}

Trait* TraitTreeNode::cloneTrait() //farlig funktion
{
	if (empty)
	{
		throw new std::exception();
	}
	return traitSlot->clone();
}

std::vector<TraitTreeNode*> TraitTreeNode::getSubNodes() 
{ 
	return subNodes; 
}

TraitTag TraitTreeNode::getTraitTag()
{
	if (empty)
	{
		return TraitTag::enumTraitNone;
	}
	else
	{
		return traitSlot->getTag();
	}
}*/