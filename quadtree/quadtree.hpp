//
//  quadtree.hpp
//  quadtree
//
//  Created by Alexander Baylon on 4/25/21.
//  Copyright © 2021 Alexander Baylon. All rights reserved.
//

#ifndef quadtree_hpp
#define quadtree_hpp

#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// bounding box
struct Rectangle
{
    double x = 0.f, y = 0.f;
    double width = 0.f, height = 0.f;
    Rectangle() {}
    Rectangle(double _x, double _y, double _width, double _height)
       : x(_x), y(_y), width(_width), height(_height) {}
    Rectangle& operator=(const Rectangle& _recf2)
    {
       this->x = _recf2.x;
       this->y = _recf2.y;
       this->width = _recf2.width;
       this->height = _recf2.height;
       return *this;
    }
    double getMinX() { return x; }
    double getMinY() { return y; }
    double getMaxX() { return x + width; }
    double getMaxY() { return y + height; }
    double getArea() { return width*height; }
    double getCenterX() { return x + width / 2; }
    double getCenterY() { return y + height / 2; }
    int getQuadrant(double _x, double _y) {
        return(_x < getCenterX() ? (_y < getCenterY() ? 2 : 0) : (_y < getCenterY() ? 3 : 1));
    }
    
    Rectangle getSubExtent(int _qd) {
        switch (_qd)
        {
            case 0:return Rectangle(x, y + width / 2, width / 2, height / 2); break;
            case 1:return Rectangle(x + width / 2, y + width / 2, width / 2, height / 2); break;
            case 2: return Rectangle(x, y, width / 2, height / 2); break;
            case 3:return Rectangle(x + width / 2, y, width / 2, height / 2); break;
            default:return Rectangle();break;
        }
    };
    bool isEmpty() { return getArea() < 0.000001f; }
    bool contains(double _x, double _y) { return (x < _x&&_x < x + width) && (y < _y&&_y < y + height); }
};


struct Point
{
    double x, y, z;
    Point() { x = y = z = 0.f; }
    Point(double _x, double _y, double _z)
        : x(_x), y(_y), z(_z) {}
    Point& operator=(const Point& _lp)
    {
        this->x = _lp.x;
        this->y = _lp.y;
        this->z = _lp.z;
        return *this;
    }
};


struct QuadTreeNode
{
    Point val;
    Rectangle extent;
    int level = 1;
    QuadTreeNode *childNode[4] = {NULL};
    bool isLeaf = true;
    bool hasData = false;
    QuadTreeNode() {}
    QuadTreeNode(Rectangle _extent, int _level) : extent(_extent), level(_level) {}
};


class QuadTree
{
public:
    QuadTree();
    ~QuadTree();
    QuadTree(const Rectangle& _extent, const vector<Point>& _lp);
 
    int getCount() { return m_count; };
    int geDepth() { return m_depth; };
    bool initQuadTree();
    bool Insert(Point& lp);
    Point getNearestNeighbor(double x0, double y0);
    vector<Point> getNeighborByDistance(double x0, double y0, double d);
 
private:
    Rectangle m_extent;
    vector<Point> m_lp;
    QuadTreeNode* m_root = NULL;
    int m_count = 0;
    int m_depth = 1;
 

    bool addNode();
    void addNode(QuadTreeNode * &node, Point & lp);
    void getNearest(QuadTreeNode * node, Point &nlp, double x0, double y0, double &d);
    void getNearest(QuadTreeNode * node, vector<Point> &nlp, double x0, double y0, double d);
    void destroyQTree(QuadTreeNode * node);
    double getMDistance(double x1, double y1, double x2, double y2) { return  abs(x2 - x1) + abs(y2 - y1); };
};

#endif /* quadtree_hpp */
