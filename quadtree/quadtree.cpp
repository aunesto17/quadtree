//
//  quadtree.cpp
//  quadtree
//
//  Created by Alexander Baylon on 4/25/21.
//  Copyright © 2021 Alexander Baylon. All rights reserved.
//

#include "quadtree.hpp"


QuadTree::QuadTree(const Rectangle& _extent, const vector<Point>& _lp)
{
    m_extent = _extent;
    m_count = _lp.size();
    m_lp = _lp;
    initQuadTree();
    addNode();
}
 
bool QuadTree::initQuadTree()
{
    m_root = new QuadTreeNode();
    m_root->extent = m_extent;
    return true;
}
 
bool QuadTree::addNode()
{
    for (int i = 0; i < m_count; i++)
    {
        addNode(m_root, m_lp[i]);
    }
    return true;
}


void QuadTree::addNode(QuadTreeNode * &node, Point & lp)
{
    if (!node->isLeaf)
    {
        int quadrant = node->extent.getQuadrant(lp.x, lp.y);
        addNode(node->childNode[quadrant], lp);
    }
    else
    {
        if (!node->hasData)
        {
            node->hasData = true;
            node->val = lp;
            return;
        }
        else
        {
            node->isLeaf = false;
            for (int i = 0; i < 4; i++)
            {
                node->childNode[i] = new QuadTreeNode(node->extent.getSubExtent(i), node->level + 1);
            }
            m_depth = max(m_depth, node->level + 1);
            addNode(node->childNode[node->extent.getQuadrant(node->val.x, node->val.y)], node->val);
            addNode(node->childNode[node->extent.getQuadrant(lp.x, lp.y)], lp);
            node->val = Point();
            node->hasData = false;
        }
    }
}

QuadTree::~QuadTree()
{
    cout << "QuadTree destroyed..." << endl;
}
