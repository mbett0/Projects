#ifndef JUG_H
#define JUG_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility> // pair
#include <queue>
#include <limits> // to set ints to the max value more easily
#include <stack>
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


class Edge {
    friend class Jug;
    friend class Vertex;
    public:
        Edge(std::string,int);
    private:
        std::string action;
        int cost;
    
};

class Vertex {
    friend class Jug;
    friend class Edge;
    public:
        Vertex(int,int);
        Vertex();
    private:
        int jugAqty, jugBqty;
        std::list< std::pair<int,Edge> > neighbors;
        int distance;
        int previous;
        int next;
        int index;
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        int solve(std::string &solution);
        void makeGraph();
        int searchExisting(Vertex);
    private:
        int cA, cB, N, cfA, cfB, ceA, ceB, cpAB, cpBA;
        std::vector<Vertex> verticies;
        int numVerticies;
        void dijkstra(int);
        void updateindicies();
        bool invalid;
};

#endif
