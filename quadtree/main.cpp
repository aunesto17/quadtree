//
//  main.cpp
//  quadtree
//
//  Created by Alexander Baylon on 4/25/21.
//  Copyright © 2021 Alexander Baylon. All rights reserved.
//

#include "quadtree.hpp"

int main(int argc, const char * argv[]) {
    
    int cap = 10000;
    vector<Point> lp(cap);
    srand((unsigned)time(NULL));
    int i = 0;
    for_each(lp.begin(), lp.end(), [&](Point &ilp) \
       {ilp = Point(4 * rand() / (double)(RAND_MAX), 4 * rand() / (double)(RAND_MAX), i); i++; });

    Rectangle totalExtent = Rectangle(0, 0, 4, 4);

    //Construction tree
    clock_t  clockBegin, clockEnd;
    clockBegin = clock();
    QuadTree qt = QuadTree(totalExtent, lp);
    clockEnd = clock();
    cout << "Time to build a tree = "<< clockEnd-clockBegin <<" ms" << endl;
    cout << "Points = "<< qt.getCount() << endl;
    cout << "Tree depth = "<< qt.geDepth() << endl;
    cout << endl;
    
    
    return 0;
}
