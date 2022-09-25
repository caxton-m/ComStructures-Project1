// Computing Structures Fall 2022
// DSA 5005
// Project 1 - boilerplate code
// Original editor - Aditya Narasimhan
// Modified by Caxton Muchono

#include <iostream>
#include <string>

using namespace std;

// class node to store one node's details
class Node {
protected:
	int nodeNumber; // field to store node's number
	string nodeInfo; // field to store node's information
public:
	Node() {  // default constructor
		nodeNumber = 0;
		nodeInfo = "";
	} 

	// getters
	string getNodeInfo() {
		return nodeInfo;
	}
	int getNodeNumber() {
		return nodeNumber;
	}


	// setters
	void setNodeInfo(string newInfo) {
		nodeInfo = newInfo;
	}
	void setNodeNumber(int newNum) {
		nodeNumber = newNum;
	}

	// display node details
	void display() {
		cout << getNodeNumber() << ": " << getNodeInfo() << endl;
	} 
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// class to store one edge's details
class Edge {
protected:
	Node* u; // field to store source node pointer
	Node* v; // field to store destination node pointer
	string edgeInfo; // field to store edge information
public:
	Edge() { // default constructor
		u = NULL;
		v = NULL;
		edgeInfo = "";

	} 

	// getters 
	Node& getu() {
		return *u;
	}
	Node& getv() {
		return *v;
	}
	string getEdgeInfo() {
		return edgeInfo;
	}

	// setters
	void setu(Node* newu) {
		u = newu;
	}
	void setv(Node* newv) {
		v = newv;
	}
	void setEdgeInfo(string newInfo) {
		edgeInfo = newInfo;
	}

	// display edge details
	void display() {

		cout << u->getNodeInfo() << " - " << v->getNodeInfo() << " " << edgeInfo << endl;
	}
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// class to store the graph database
class GraphDB {
	protected:
		Node* myNodes; // array of nodes 
		Edge* myEdges; // array of edges
		int numNodes; // number of nodes
		int numEdges; // current number of edges
		int maxEdges; // store the max number of edges (array size)
	public:
		GraphDB(int nNodes, int mEdges) { // non-default constructor
			numNodes = nNodes;
			numEdges = 0;  // start numEdge at 0 and increase index as edges increase 
			maxEdges = mEdges;                  
			myNodes = new Node[nNodes]();
			myEdges = new Edge[mEdges]();       // remove +1
		}

		//setters
		void setNode(Node& newNode) {
			// find the node number of newNode and store in nodeNum
			int nodeNum = newNode.getNodeNumber();

			// set GraphDB node at NodeNum index with the node info
			myNodes[nodeNum].setNodeNumber(nodeNum);
			myNodes[nodeNum].setNodeInfo(newNode.getNodeInfo());
		}
		void setEdge(Edge& newEdge) {

			// increase the numEdge index to go to the next one
			numEdges++;

			if (numEdges >= maxEdges) {

				// create a new temp array
				Edge* temp = new Edge[maxEdges + (maxEdges/2)]();

				// copy old values - deep copy
				for (int i = 0; i < maxEdges; i++) {
					temp[i] = myEdges[i];
				}

				delete[] myEdges;  // delete the pointer to the old values
				myEdges = temp;  // re point the pointer to the new memory location

				maxEdges = maxEdges + (maxEdges / 2);  // update the value of maxEdges

			}
			

			// set GraphDB edge at numEdge index with node u, v and edge info
			myEdges[numEdges - 1].setu(&newEdge.getu());
			myEdges[numEdges - 1].setv(&newEdge.getv());
			myEdges[numEdges - 1].setEdgeInfo(newEdge.getEdgeInfo());

		}
		void setNodeInfo(int u, string newInfo) {

			// loop through the GraphDB nodes
			for (int i = 0; i < numNodes; i++) {

				// if the GraphDB node number is equal to u set new node info
				if (myNodes[i].getNodeNumber() == u) {
					myNodes[i].setNodeInfo(newInfo);
				}
			}

		}
		void setEdgeInfo(int u, int v, string newInfo) {

			// loop through the GraphDB edges
			for (int i = 0; i < numEdges; i++) {

				// If the edge u node number is equal to u and 
				//    if the edge v node number is equal to v set new info
				if (myEdges[i].getu().getNodeNumber() == u && myEdges[i].getv().getNodeNumber() == v) {
					myEdges[i].setEdgeInfo(newInfo);
				}
			}
		}

		// getters
		Node* getNode(int nodeNum) {          
			return &myNodes[nodeNum];
		}
		string getNodeInfo(int nodeNum) {
			return myNodes[nodeNum].getNodeInfo(); 
		}
		Edge* getEdgeInfo(int u, int v) {

			// loop through the GraphDB edges 
			for (int i = 0; i < numEdges; i++) {

				// If the edge u node number is equal to u and 
				//    if the edge v node number is equal to v return the edge.
				if (myEdges[i].getu().getNodeNumber() == u && myEdges[i].getv().getNodeNumber() == v) {
					return &myEdges[i];
				}
			}

			// If edge is not found 
			return NULL;
		}

		// operations
		bool isAnEdge(int u, int v) { // is this edge existent

			// loop through the GraphDB edges
			for (int i = 0; i < numEdges; i++) {

				// If the edge u node number is equal to u and 
				//    if the edge v node number is equal to v then edge exists
				if (myEdges[i].getu().getNodeNumber() == u && myEdges[i].getv().getNodeNumber() == v) {

					// print out message 
					cout << "Edge exists between " << myEdges[i].getu().getNodeInfo() 
						<< " and " << myEdges[i].getv().getNodeInfo() << endl;

					return true;  // return true when edge is found
				}
			}

			// if edge is not in GraphDB edges it does not exist so print out message
			cout << "No edge exists between " << myNodes[u].getNodeInfo()
				<< " and " << myNodes[v].getNodeInfo() << endl;

			return false;  // return false when edge not found
		}

		void addEdge(Edge& newEdge) { // add an edge

			if (numEdges < maxEdges) {
				// set GraphDB edge at numEdge index with node u, v and edge info
				myEdges[numEdges].setu(&newEdge.getu());
				myEdges[numEdges].setv(&newEdge.getv());
				myEdges[numEdges].setEdgeInfo(newEdge.getEdgeInfo());

				// increase the numEdge index to go to the next one
				numEdges++;
			}
			else {
				Edge* temp = new Edge[maxEdges + 1]();

				for (int i = 0; i < maxEdges; i++) {
					temp[i] = myEdges[i];
				}

				delete[] myEdges;
				myEdges = temp;

				// set GraphDB edge at numEdge index with node u, v and edge info
				myEdges[numEdges].setu(&newEdge.getu());
				myEdges[numEdges].setv(&newEdge.getv());
				myEdges[numEdges].setEdgeInfo(newEdge.getEdgeInfo());

				// increase the numEdge index to go to the next one
				numEdges++;
			}

		} 

		void deleteEdge(int u, int v) { // delete/remove the edge

			int ind = -1; // temp index to store where index of edge is in the GraphDB
			
			// loop through the GraphDB edges
			for (int i = 0; i < numEdges; i++) {

				// break loop when index with deleted edge is found and store index in ind
				if (myEdges[i].getu().getNodeNumber() == u && myEdges[i].getv().getNodeNumber() == v) {
					ind = i;
					break;
				}
			}

			// loop through the GraphDB edges starting from deleted edge index
			for (int j = ind; j < numEdges - 1; j++)
			{
				myEdges[j] = myEdges[j + 1]; // make the current index edge the next edge from GraphDB edges
			}
			
			// remove the last index of GraphDB edges by setting to constructor values
			myEdges[numEdges - 1].setu(NULL);
			myEdges[numEdges - 1].setv(NULL);
			myEdges[numEdges - 1].setEdgeInfo("");

			// decrease the numEdge index since the number of Edges is one less
			numEdges--;
			
		}

		void displayEdges() { // display the edges 

			// loop through the GraphDB edges and display them
			for (int i = 0; i < numEdges; i++) {
				myEdges[i].display();
			}
		}
};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
	int numNodes; // temp variable to store numNodes from input
	int maxEdges; // temp variable to store maxEdges from input
	int nodeNum; // index of node
	int node1; // temp variable to store 1st node index
	int node2; // temp variable to store 2nd node index

	string nodeInfo; // names or infomation of nodes
	string edgeInfo; // temp variable to store edge information

	char input; // command to do something 
	Node tempNode; // temp node for node insertion 
	Edge tempEdge; // temp edge for edge insertion

	GraphDB* masterGraph; // pointer object of GraphDB class

	cin >> numNodes >> maxEdges; // read the numNodes and maxEdges from redirected input

	// display the values read in
	cout << "numNodes: " << numNodes << endl;
	cout << "maxEdges: " << maxEdges << endl << endl;

	masterGraph = new GraphDB(numNodes, maxEdges); // allocate memory by calling non-default constructor

	// read in the rest of the information from the input 
	

	// input nodes 
	for (int i = 0; i < numNodes;i++) {
		
		cin >> nodeNum >> nodeInfo; // read in the node info

		// Set the node number and info to temp node
		tempNode.setNodeNumber(nodeNum);
		tempNode.setNodeInfo(nodeInfo);

		// store the address of this node to the GraphDB nodes
		masterGraph->setNode(tempNode);

	}                                                


	cin >> input;  // read the next command from input

	// while input is not end of file get next command 
	while (!cin.eof()) {  

		// use switch cases to see the different commands to do next
		switch (input) {

			case 'I': { // insert edge

				// read the node numbers and edge info
				cin >> node1 >> node2 >> edgeInfo;
				cout << "Inserting "<< node1 << " " << node2 << ": " << edgeInfo << endl << endl;

				// Set the tempEdge nodes to the GraphDB nodes with the same node numbers  
				tempEdge.setu(masterGraph->getNode(node1));
				tempEdge.setv(masterGraph->getNode(node2));

				// Set the tempEdge info 
				tempEdge.setEdgeInfo(edgeInfo);

				// store the address of this tempEdge to the GraphDB edges
				masterGraph->setEdge(tempEdge);

				break;
			}
			case 'R': { // remove edge 

				// read the node numbers to be removed
				cin >> node1 >> node2;
				cout << "Removing " << node1 << " " << node2 << endl;

				// remove the edge from the GraphDB byy calling function
				masterGraph->deleteEdge(node1, node2);

				cout << endl;
				break;
			}
			case 'D': { // display the nodes and edges 

				// loop through GraphDB nodes and display them
				cout << "Displaying myNodes:" << endl;
				for (int i = 0; i < numNodes; i++) {
					masterGraph->getNode(i)->display();
				}

				// loop through GraphDB edges and display them
				cout << "Displaying myEdges:" << endl;
				masterGraph->displayEdges();

				cout << endl;
				break;
			}
			case 'E': { // check existence of edges 

				// read the node numbers to be checked for edge existence
				cin >> node1 >> node2;

				// loop through GraphDB edges to see edge existence calling function
				masterGraph->isAnEdge(node1, node2);

				cout << endl;
				break;
			}

			default: cout << "No commands found";   // if no command found
		}

		cin >> input; // read the next command from input 
	}

	delete masterGraph;

	return 0;
}
