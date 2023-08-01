

#include "Jug.h"
#include <climits>
using namespace std;

Vertex::Vertex(int A, int B) {
    this->jugAqty = A;
    this->jugBqty = B;
    this->previous = std::numeric_limits<int>::max();;
    this->distance = std::numeric_limits<int>::max();;
    this->next = -1;
}

Vertex::Vertex() {
    
}

Edge::Edge(string string, int cost) {
    this->action = string;
    this->cost = cost;
}

Jug::Jug(int cA, int cB, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) {
 
    this->cA = cA;
    this->cB = cB;
    this->N = N;
    this->cfA = cfA;
    this->cfB = cfB;
    this->ceA = ceA;
    this->ceB = ceB;
    this->cpAB = cpAB;
    this->cpBA = cpBA;
    
    
    if (cA > cB || cA < 0 || N > cB || cB > 1000) {
     
        invalid = true;
        this->numVerticies = 0;
    } else {
        makeGraph();
        this->numVerticies = verticies.size();
        invalid = false;
    }
}

Jug::~Jug() {
    
}

void Jug::makeGraph() {
    
    Vertex *newVertex;
    queue<Vertex> Queue;
    int currentjugA, currentjugB, existing, newA, newB;
    
    this->verticies.push_back(Vertex(0,0));
    this->verticies.push_back(Vertex(cA,0));
    verticies.at(0).neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("fill A",cfA)));
    
    this->verticies.push_back(Vertex(0,cB));
    verticies.at(0).neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("fill B",cfB)));
    
   
    
    updateindicies();
    Queue.push(verticies.at(1));
    updateindicies();
    Queue.push(verticies.at(2));
    
   
    while(!Queue.empty()) {
        Vertex curr = Queue.front();
        Queue.pop();
        currentjugA = curr.jugAqty;
        currentjugB = curr.jugBqty;
        
        
        updateindicies();
  
        newVertex = new Vertex(cA,currentjugB);
        existing = searchExisting(*newVertex);
        if (existing != -1) {
          
            curr.neighbors.push_back(pair<int,Edge>(existing,Edge("fill A",cfA)));

        } else {
    
            newVertex->index = verticies.size();
            this->verticies.push_back(*newVertex);
            curr.neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("fill A",cfA)));
          
            Queue.push(verticies.at(verticies.size()-1));
        }
        
        updateindicies();
        
        newVertex = new Vertex(currentjugA,cB);
        existing = searchExisting(*newVertex);
        if (existing != -1) {
        
            curr.neighbors.push_back(pair<int,Edge>(existing,Edge("fill B",cfB)));
       
        } else {
     
            newVertex->index = verticies.size();
            this->verticies.push_back(*newVertex);
            curr.neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("fill B",cfB)));
    
            Queue.push(verticies.at(verticies.size()-1));
        }
        
        updateindicies();
        // ACTION: pourAB
        newA = currentjugA;
        newB = currentjugB;
        newB = newB + newA;
        if (newB > cB) {
            newA = newB - cB;
            newB = cB;
        } else {
            newA = 0;
        }
        newVertex = new Vertex(newA,newB);
        existing = searchExisting(*newVertex);
        if (existing != -1) {
         
            curr.neighbors.push_back(pair<int,Edge>(existing,Edge("pour A B",cpAB)));
            
          
        } else {

            newVertex->index = verticies.size();
            this->verticies.push_back(*newVertex);
            curr.neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("pour A B",cpAB)));
    
            Queue.push(verticies.at(verticies.size()-1));
        }
        
        updateindicies();
       
        newA = currentjugA;
        newB = currentjugB;
        newA = newB + newA;
        if (newA > cA) {
            newB = newA - cA;
            newA = cA;
        } else {
            newB = 0;
        }
        newVertex = new Vertex(newA,newB);
        existing = searchExisting(*newVertex);
        if (existing != -1) {
           
            curr.neighbors.push_back(pair<int,Edge>(existing,Edge("pour B A",cpBA)));
            
         
        } else {
           
            newVertex->index = verticies.size();
            this->verticies.push_back(*newVertex);
            curr.neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("pour B A",cpBA)));
         
            Queue.push(verticies.at(verticies.size()-1));
        }
        
        updateindicies();
       
        newVertex = new Vertex(0,currentjugB);
        existing = searchExisting(*newVertex);
        if (existing != -1) {
       
            curr.neighbors.push_back(pair<int,Edge>(existing,Edge("empty A",ceA)));
            
          
        } else {
           
            newVertex->index = verticies.size();
            this->verticies.push_back(*newVertex);
            curr.neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("empty A",ceA)));
            
            Queue.push(verticies.at(verticies.size()-1));
        }
        
        updateindicies();
     
        newVertex = new Vertex(currentjugA,0);
        existing = searchExisting(*newVertex);
        if (existing != -1) {
            curr.neighbors.push_back(pair<int,Edge>(existing,Edge("empty B",ceB)));
            
          
        } else {
   
            newVertex->index = verticies.size();
            this->verticies.push_back(*newVertex);
            curr.neighbors.push_back(pair<int,Edge>(verticies.size()-1,Edge("empty B",ceB)));
           
            Queue.push(verticies.at(verticies.size()-1));
        }
    
        verticies.at(curr.index).neighbors = curr.neighbors;
    }
   
}

void Jug::dijkstra(int source) {
    queue<Vertex*> Queue;
    Vertex *curr;
    list< pair<int,Edge> >::iterator it;
    for (int i=0; i<numVerticies; i++) {
        verticies.at(i).distance = INT_MAX;
    }
    verticies.at(source).distance = 0;
    verticies.at(source).previous = -1;
    for (int i=0; i<numVerticies; i++) {
        Queue.push(&verticies.at(i));
    }
    while (!Queue.empty()) {
        curr = Queue.front();
        Queue.pop();
       
        for (it=curr->neighbors.begin(); it!=curr->neighbors.end(); ++it) {
            int old_dist = verticies.at(it->first).distance;
            int new_dist = curr->distance + it->second.cost;
           
            if (old_dist > new_dist) {
               
                verticies.at(it->first).previous = curr->index;
                verticies.at(it->first).distance = new_dist;
      
            }
        }
    }
}

int Jug::searchExisting(Vertex current) {
    for (unsigned i=0; i<verticies.size(); i++) {
        if ((verticies.at(i).jugAqty == current.jugAqty) && (verticies.at(i).jugBqty == current.jugBqty)) {
            return i;
        }
    }

    return -1;
}

void Jug::updateindicies() {
    for (unsigned i=0; i<verticies.size(); i++) {
        verticies.at(i).index = i;
    }
}

int Jug::solve(string &solution) {
    if (this->invalid) {
    
        solution.empty();
        return -1;
    }
    dijkstra(0);
    Vertex finalVertex(0,N);
    int index = searchExisting(finalVertex);
    if (index == -1) {
        
        solution.empty();
        return 0;
    }
    int nextIndex = verticies.at(index).previous;
    list< pair<int,Edge> >::iterator it;
    stack<string> solnstack;
    string str;
    str.clear();
    str.append("success ");
    str.append(SSTR(verticies.at(index).distance));
    solnstack.push(str);
    str.clear();

    while (nextIndex != -1) {
       
        for (it=verticies.at(nextIndex).neighbors.begin(); it!=verticies.at(nextIndex).neighbors.end(); it++) {
            if (it->first == index) {
             
                solnstack.push(it->second.action);
            }
        }
        index = nextIndex;
        nextIndex = verticies.at(index).previous;
        
    }
    solution.clear();
    while(!solnstack.empty()) {
        solution.append(solnstack.top());
        solnstack.pop();
        if (!solnstack.empty()) {solution.append("\n");}
    }
    
    return 1;
}
