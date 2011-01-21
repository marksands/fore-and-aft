#pragma once

#include <list>
#include <stack>
#include <queue>

#pragma mark -
#pragma mark GEdge

  /*
  * @class GEdge
  *   Programmer - Mark Sands
  *   date - January 20, 2011
  */
  template <class N, class E> class GNode;
  template <class N, class E>
  class GEdge {
    public:
      /*
      * @variables
      *   node - GNode<E, E> *
      *   weight - E
      */
      GNode<N, E> *node;
      E weight;
  };

#pragma mark -
#pragma mark GNode

  /*
  * @class GNode
  *   Programmer - Mark Sands
  *   date - January 20, 2011
  */
  template <class N, class E>
  class GNode {
    public:
      /*
      * @variables
      *   data - N
      *   edgelist - std::list<GEdge<N, E> >
      *   visited - bool
      */
      typedef GEdge<N, E> Edge;
      typedef GNode<N, E> Node;

      N data;
      std::list<Edge> edgelist;
      bool visited;

      /*
      * @methods
      *   GNode(N data, bool visited) - contstructor
      */
      GNode( N data, bool visited ) : data(data), visited(visited) {
        ;
      }

      /*
      * @methods
      *   setEdge(Node *node, E weight) - add edge to edgelist 
      */
      void addEdge( Node* node, E weight )
      {
        Edge e;
        e.node = node;
        e.weight = weight;
        edgelist.push_back(e);
      }

      /*
      * @methods
      *   getEdge(Node* node) - returns an edge that points to the node
      */
      Edge* getEdge( Node* node )
      {
        typename std::list<Edge>::iterator iter;
        for ( iter = edgelist.begin(); iter != edgelist.end(); iter++ ) {
          if ( iter->node == node )
            return &iter;
        }
        return NULL;
      }

      /*
      * @methods
      *   removeEdge(Node* node) - removes an edge that points to the node
      */
      void removeEdge( Node* node )
      {
        typename std::list<Edge>::iterator iter;
        for ( iter = edgelist.begin(); iter != edgelist.end(); iter++ ) {
          if ( iter->node == node )
            edgelist.remove(iter);
        }
      }
  };

#pragma mark -
#pragma mark Graph

  /*
  * @class Graph
  *  Programmer - Mark Sands
  *  date - January 20, 2011
  */
  template <class N, class E>
  class Graph
  {
    public:
      /*
      * @variables
      *   data - N
      *   nodes - std::list<GNode<N, E> >
      *   count - unsigned int 
      */
      typedef GNode<N, E> Node;
      typedef GEdge<N, E> Edge;

      std::list<Node*> nodes;
      unsigned int count;

      /*
      * @methods
      *   Graph(int size) - constructor sets nodes to 0
      */
      Graph( int size ) : nodes(size) , count(0)
      {
        for( int i = 0; i < size; i++ )
          nodes[i] = 0;
      }

      /*
      * @methods
      *   ~Graph() - destructor deletes the nodes
      */
      virtual ~Graph()
      {
        for( int i = 0; i < nodes.size; i++ ) {
          if( nodes[i] != NULL )
            delete nodes[i];
        }
      }

      /*
      * @methods
      *   addNode(N data, int index) - adds a node to the adjacencylist
      */
      bool addNode( N data, int index )
      {
        if( nodes[index] != NULL )
          return false;

        nodes[index] = new Node(data, false);
        count++;

        return true;
      }

      /*
      * @methods
      *   removeNode(int index) - removes a node and its connected edges
      */
      void RemoveNode( int index )
      {
        if (nodes[index] != NULL)
        {
          Edge *edge;

          for( int i = 0; i < nodes.size(); i++ )
          {
            if( nodes[i] != NULL )
            {
              edge = nodes[i]->getEdge(nodes[i]);
              if ( edge != NULL )
                removeEdge(i, index);
            }
          }

          delete nodes[index];
          nodes[index] = NULL;
          count--;
        }
      }

      /*
      * @methods
      *   addEdge(int fromIndex, int toIndex, E weight) - adds an edge to the graph
      */
      bool addEdge( int fromIndex, int toIndex, E weight )
      {
        bool flag = true;

        if( nodes[fromIndex] == NULL || nodes[toIndex] == NULL )
          flag = false;

        if( nodes[fromIndex]->getEdge(nodes[toIndex]) != NULL )
          flag = false;

        if (flag)
          nodes[fromIndex]->addEdge(nodes[toIndex], weight);

        return flag;
      }

      /*
      * @methods
      *   removeEdge(int fromIndex, int toIndex) - removes an edge from the graph
      */
      void removeEdge( int fromIndex, int toIndex )
      {
        if( nodes[fromIndex] != NULL || nodes[toIndex] !=NULL )
          nodes[fromIndex]->removeEdge(nodes[toIndex]);
      }

      /*
      * @methods
      *   getEdge(int fromIndex, int toIndex) - return an edge from the graph
      */
      Edge* getEdge( int fromIndex, int toIndex )
      {
        if( nodes[fromIndex] != NULL || nodes[toIndex] !=NULL )
          return nodes[fromIndex]->geteEdge(nodes[toIndex]);
        return NULL;
      }

      /*
      * @methods
      *   clearVisits() - clears visits from every node
      */
      void clearVisits()
      {
        for ( int i = 0; i < nodes.size(); i++ ) {
          if( nodes[i] != NULL )
            nodes[i]->visited = false;
        }
      }

#pragma mark -
#pragma mark Algorithms

      /*
      * @methods
      *   DepthFirstSearch() - uses depth first search to traverse the nodes
      */
      void DepthFirstSearch( Node* node )
      {
        if ( node == NULL )
          return;

        node.visited = true;
        std::cout << node.data;

        typename std::list<Edge>::iterator iter = node->edgelist.begin();

        for( ; iter != node->edgelist.end(); iter++ ) {
          if( iter->node.visited == false )
            DepthFirstSearch( iter->node );
        }

        //clearVisits();
      }

      /*
      * @methods
      *   BreadthFirstSearch() - uses breadth first search to traverse the nodes
      */
      void BreadthFirstSearch( Node* node )
      {
        if ( node == NULL )
          return;

        std::queue<Node*> queue;

        typename std::list<Edge>::iterator iter = node->edgelist.begin();
        typename std::list<Edge>::iterator iterEnd;

        queue.push(node);
        node->visited = true;

        while(!queue.empty())
        {
          std::cout << queue.top().data;

          iter = queue.top()->edgelist.begin();
          iterEnd = queue.top()->edgelist.end();

          for( ; iter != iterEnd; iter++ )
          {
            if( iter->node.visited == false ) {
              iter->node.visited = true;
              queue.push( iter->node );
            }
          }

          queue.pop();
        }
      }

  };
