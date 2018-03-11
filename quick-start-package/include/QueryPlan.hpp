#pragma once

#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include "Joiner.hpp"

// Keeps the important info/statistics for every column
// needed to build the plan tree
struct ColumnInfo {
    uint64_t min; // Value of the minimum element
    uint64_t max; // Value of the maximum element
    uint64_t size; // Total number of elements
    uint64_t distinct; // Number of distinct elements
};

// Plan Tree's node
struct PlanTreeNode {
    PlanTreeNode* left;
    PlanTreeNode* right;
    PlanTreeNode* parent;

    // The constructor
    PlanTreeNode();
};

// Plan Tree data structure
struct PlanTree {
    PlanTreeNode* rootPtr;

    bool isRightDeepOnly;
    bool isLeftDeepOnly;

    // The constructor
    PlanTree(std::set<table_t*>& tableSet);

    // Merges two join trees into one
    // and return the resulted tree
    PlanTree* mergePlanTrees(PlanTree* left, PlanTree* right);

    // Destoys a Plan Tree properly
    void freePlanTree(PlanTree* planTreePtr);

    // Prints a Plan Tree -- for debugging
    void printPlanTree(PlanTree* planTreePtr);

    // Estimates the cost of a given Plan Tree */
    double costOfPlanTree(PlanTree* planTreePtr);
};

// Query Plan data structure
struct QueryPlan {
    // Keeps the info of every column of every relation
    // Every row represents a relation
    // Every item of a row represents a column of the relation
    std::vector<std::vector<ColumnInfo>> columnInfo;

    PlanTree* planTreePtr; // The plan tree to execute

    // The constructor
    QueryPlan(QueryInfo& queryInfoPtr);

    // Fills the columnInfo matrix with the data of every column
    void fillColumnInfo(QueryInfo& queryInfo);
};

/*
// destruct a Join Tree node properly
void destrJoinTreeNode(JoinTreeNode* joinTreeNodePtr);

// print a Join Tree node -- for debugging
void printJoinTreeNode(JoinTreeNode* joinTreeNodePtr);

// estimate the cost of a given Join Tree node
double joinTreeNodeCost(JoinTreeNode* joinTreeNodePtr);
*/