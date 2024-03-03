#pragma once
/*#include "TraitTreeNode.h"

#define MAX_NODES 10

enum class TraitTreeType { none, triangle };

class TraitTagTree
{
public:
	TraitTreeType type = TraitTreeType::none;
	TraitTag allNodes[MAX_NODES];
};

class TraitTree
{
private:
	TraitTreeNode allNodes[MAX_NODES];
	int nrOfNodes = -1;
	std::vector<TraitTreeNode*> nodeHeads;
	TraitTreeType treeShape = TraitTreeType::none;

	std::vector<int> getAllOpenSlots();
	std::vector<std::pair<int, TraitTreePath>> zipIDPath(std::vector<int> ids, std::vector<TraitTreePath> paths);
	std::pair<std::vector<int>, std::vector<TraitTreePath>> unzipIDPath(std::vector<std::pair<int, TraitTreePath>> zipped);

	TraitTreeNode* findNode(int id);
	void createEmptyTriangleTree();
	void addressTree();
	void addressTriangleTree();
	void clearConnections();
public:
	TraitTree() {};
	TraitTree(TraitTreeType type);
	TraitTree(const TraitTree& cp);
	TraitTree& operator=(const TraitTree as);


	void addTrait(Trait* trait, int nodeID);

	int getLevelupSlot();
	TraitTreeNode* getTreeNode(TraitTreePath address);
	int getNrOfNodes() { return nrOfNodes; };
	std::vector<Trait*> copyAllTraits();
	std::vector<Trait*> getAllTraits();
	TraitTagTree getVisualTree();
};
*/