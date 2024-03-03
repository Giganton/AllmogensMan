/*#pragma once
#include "Trait.h"
#include<vector>

struct TraitTreePath
{
	std::vector<int> indexPath;
	void concatenatePaths(TraitTreePath newPath);
	void removeFirstStep();
	int takeFirstStep();

	bool operator==(const TraitTreePath& rhs) const noexcept
	{
		// logic here
		return this->indexPath.at(0) == rhs.indexPath.at(0); // for example
	}
	bool operator<(const TraitTreePath& rhs) const noexcept
	{
		// logic here
		return this->indexPath.at(0) < rhs.indexPath.at(0); // for example
	}
	bool operator>(const TraitTreePath& rhs) const noexcept
	{
		// logic here
		return this->indexPath.at(0) > rhs.indexPath.at(0); // for example
	}
};

std::vector<TraitTreePath> forkTraitPath(TraitTreePath path1, std::vector<TraitTreePath> fork);

class TraitTreeNode
{
private:
	bool empty = true;
	Trait* traitSlot = nullptr;
	std::vector<TraitTreeNode*> subNodes;
	int level = -1;
	int ID = -1;
public:
	TraitTreeNode() {  };
	TraitTreeNode(int lvl, int id) { level = lvl; ID = id; };
	~TraitTreeNode();
	TraitTreeNode(const TraitTreeNode& cp);
	TraitTreeNode& operator=(const TraitTreeNode as);

	void setTrait(Trait* trait) { traitSlot = trait->clone(); empty = false; };
	Trait* cloneTrait();
	Trait* getTrait() { return traitSlot; };
	bool isEmpty() { return empty; };

	void connect(TraitTreeNode* node) {	subNodes.push_back(node); };
	void clearConnections() { subNodes.clear(); };
	//std::vector<TraitTreePath> findOpenSlots();
	TraitTreeNode* findNode(TraitTreePath address);
	std::vector<TraitTreeNode*> getSubNodes();
	int getID() { return ID; };

	TraitTag getTraitTag();
};*/