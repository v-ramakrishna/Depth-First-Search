// Name of Author: Vijay Ramakrishna
// ASU ID: 1202948495
// Homework Number: 7
// Description: The program take commands from a file, "command1.txt," parses these commands, and calls a
//              corresponding method. Commands which can be called are "graph,[some int],[some int]" which generates
//              a new Adjacency Graph and Adjacency List from a second file, "edges1.txt", based on what lines are specified
//              to read from, "print_graph", which prints the Adjacency Graph's
//              Adjacency List, if the Graph exists, "depth_first_search", which runs through a Depth First Search of
//              an existing Adjacency Graph and prints the results to the console, "end_graph", which calls the
//              destructor for an existing Adjacency Table, deleting everything in it and setting it to be NULL,
//              and "quit", which exits the program. Any other commands will cause an error message to print to the console.
//              This is the header/implementation file for the Adjacency Graph, which the user interacts with via Driver
//              commands.

#ifndef ADJACENCYGRAPH_H_INCLUDED
#define ADJACENCYGRAPH_H_INCLUDED

#include <iostream> //to use cout
#include <iomanip> //to format output
#include <string> //to use strings
#include <fstream>
#include "LinkedList.h" // to use LinkedLists

// class AdjacencyGraph will contains an array of LinkedLists
class AdjacencyGraph
{
    private:
        LinkedList **aGraph;
        int tableSize;
        int time;

    public:
        AdjacencyGraph();
        void generateGraph(int firstLine, int lastLine);
        void destructor();
        void printGraph();
        void depthFirstSearch();
        void depthFirstSearchVisit(LinkedList * vertex);
        void depthFirstSearchPrint();
};
// Adjacency Graph Constructor
// Description: Constructor to initialize an Adjacency Graph
AdjacencyGraph::AdjacencyGraph()
{
    aGraph = NULL;
    tableSize = 0;
    time = 0;

}
// Generate Graph
// Description: Generates the vertexes and edges of the graph, based on input from
// the Edges file. First, reads from the file to generate a Linked List of all the
// vertexes in the graph. Then, generates a new array of Linked Lists, the size of the
// length of the Linked List; each Linked List is assigned the name of one of the vertexes.
// Then, re-opens and re-reads from the file to create edges and generate Adjacency Lists.
void AdjacencyGraph::generateGraph(int firstLine, int lastLine)
{
    int lineNumberTotal = lastLine-firstLine+1;
    if (lineNumberTotal <= 0)
    {
        cout << "Invalid Command: Skipping Line"<<endl<<endl;
        return;

    }
    // Open Edges file
    ifstream vertexReader;
    vertexReader.open("edges1.txt");
    if (!vertexReader)
    {
        cout << "Unable to Open File";
        return; // terminate with error message if file cannot be found
    }
    // Create LinkedList to store vertexes
    string initial = "0";
    LinkedList * initialList = new LinkedList(initial);
    string newEntry;
    string trash;
    string endMarker = "\r";
    // Skip lines in the Edges file until firstLine is reached
    for (int k = 0; k < firstLine; k++)
    {
        getline(vertexReader, trash);
    }
    // Read each line from Edges file, and add new nodes to LinkedList in alphabetical order up to lastLine
    int linecounter = 0;
    while((getline(vertexReader, newEntry))&&(linecounter<lineNumberTotal))
    {
        // Ensure Compatibility of text files generated on both Windows and Unix machines by removing endline characters
        int saveLastPosition = newEntry.size()-1;
        if (saveLastPosition >= 0)
        {
            string analyzeCommand = newEntry.substr(saveLastPosition, 1);
            if (analyzeCommand.compare(endMarker) == 0)
            {
                newEntry.erase(newEntry.size()-1);
            }
        }
        // Call Graph Parse Nodes for the new line input
        initialList->graphParseNodes(newEntry);
        linecounter++; // increment linecounter by 1
    }
    // Count number of total nodes in initial Linked List, and set tableSize to be equal to it
    TeamNode * counter = initialList->getHead();
    int listSize = 0;
    while (counter != NULL)
    {
        counter = counter->next;
        listSize++;
    }
    tableSize = listSize;
    struct TeamNode * currentPointer = initialList->getHead();
    // initialize the array of Linked Lists and create a new Linked List for every node in thee linked list, saving the node's name in its corresponding Linked List
    aGraph = new LinkedList* [tableSize];
    for (int index = 0; index < tableSize; index++)
    {
        aGraph[index] = new LinkedList(currentPointer->name);
        currentPointer = currentPointer->next;
    }
    // Re-open Edges file
    ifstream edgeReader;
    edgeReader.open("edges1.txt");
    if (!edgeReader)
    {
        cout << "Unable to Open File";
        return; // terminate with error message if file cannot be found
    }
    // Skip lines in the Edges file until firstLine is reached
    for (int m = 0; m < firstLine; m++)
    {
        getline(edgeReader, trash);
    }
    // Read each line from Edges file, and add new nodes to appropriate LinkedList in alphabetical order up to lastLine
    linecounter = 0;
    while((getline(edgeReader, newEntry)) && (linecounter<lineNumberTotal))
    {
         // Ensure Compatibility of text files generated on both Windows and Unix machines by removing endline characters
        int saveLastPosition = newEntry.size()-1;
        if (saveLastPosition >= 0)
        {
            string analyzeCommand = newEntry.substr(saveLastPosition, 1);
            if (analyzeCommand.compare(endMarker) == 0)
            {
                newEntry.erase(newEntry.size()-1);
            }
        }
        // Parse From Vertex name from last read line in Edges file
        string mName = "";
        size_t nameToken;
        nameToken = newEntry.find(",");
        mName = newEntry.substr(0, nameToken);

        // Find Linked List with matching name to name parsed from Edges file
        int listIndex = 0;
        string comparator = aGraph[listIndex]->getName();
        while (comparator != mName)
        {
            listIndex++;
            comparator = aGraph[listIndex]->getName();
        }
        // Insert new node in correct Linked List
        aGraph[listIndex]->graphInsertEdge(newEntry); // Call Graph Insert Edge for appropriate Linked List
        linecounter++; // increment linecounter by 1
    }
    // Close file readers
    vertexReader.close();
    edgeReader.close();
}
// Print Graph
// Description: Prints the Adjacency List for the graph. Does this by calling Print List
// for every existing list.
void AdjacencyGraph::printGraph()
{
    if (aGraph != NULL)
    {
        // Call Print List for every Linked List in the Adjacency Graph
        cout << "Graph (Adjacency List) content"<< endl<<endl;
        for (int i = 0; i < tableSize; i++)
        {
            aGraph[i]->printList();
        }
    }
    else
    {
        // Print that Graph is empty
        cout << "Graph is Empty" << endl<<endl;
    }
}
// Adjacency Graph Destructor
// Description: Destructor for the Adjacency Graph class. Calls Delete List for every list in the
// Adjacency Graph and then sets the Adjacency Graph itself to be NULL
void AdjacencyGraph::destructor()
{
    if (aGraph != NULL)
    {
        // Call Delete List for every Linked List in the Adjacency Graph and set aGraph to NULL
        for (int i = 0; i < tableSize; i++)
        {
            aGraph[i]->deleteList();
        }
        aGraph = NULL;
    }
    else
    {
        // Print that Graph is empty
        cout << "Graph is empty"<< endl<< endl;
    }
}
// Depth First Search
// Description: Initializes all Linked Lists to the color white, and nullifies their parent.
// Then, starting with the first list in alphabetical order, calls Depth First Search Visit on the Linked List
// corresponding with the edge nodes of the first list, if their corresponding Lists are white.
void AdjacencyGraph::depthFirstSearch()
{
    if (aGraph != NULL)
    {
        // Set all vertexes to White color and set all vertex's parent to NULL
        for (int i = 0; i < tableSize; i++)
        {
            aGraph[i]->setColor('W');
            aGraph[i]->nullifyParent();
        }
        // reset time to 0
        time = 0;
        // for every Linked List, if color is White, call Depth First Search Visit
        for (int j = 0; j < tableSize; j++)
        {
            if (aGraph[j]->getColor() == 'W')
            {
                depthFirstSearchVisit(aGraph[j]);
            }
        }
        // Call Depth First Search Print
        depthFirstSearchPrint();
    }
    else
    {
        // Print that Graph is empty
        cout << "Graph is empty"<< endl<< endl;
    }
}
// Depth First Search Visit
// Description: Sets start time for the initial Linked List visited, and then
// visits its children. If the Linked List corresponding with a child is found to
// be White, Depth First Search Visit will be recursively called on its child.
void AdjacencyGraph::depthFirstSearchVisit(LinkedList * vertex)
{
    TeamNode * currentPointer = vertex->getHead();
    time += 1; // time = time + 1
    char white = 'W';
    vertex->setDiscoverTime(time); // set Vertex's discovery time to be equal to time
    vertex->setColor('G'); // Set vertex's color to be Gray
    if (currentPointer != NULL) // if the Linked List has nodes
    {
        while (currentPointer != NULL) // loop to end of Linked List
        {
            string currentPointerName = currentPointer->name; // get name of team in current node
            for (int j = 0; j < tableSize; j++)
            {
                if (currentPointerName.compare(aGraph[j]->getName()) == 0) // find Linked List with matching name to current node
                {
                    if (aGraph[j]->getColor() == white) // if Linked List with matching name has color White, set its Parent to the current vertex, and call Depth First Search Visit on it
                    {
                        aGraph[j]->setParent(vertex);
                        depthFirstSearchVisit(aGraph[j]);
                    }

                }
            }
            currentPointer = currentPointer->next; // go to next node in list
        }
    }
    vertex->setColor('B'); // set Vertex color to Black
    time += 1; // increment time by 1
    vertex->setFinishTime(time); // set vertex finish time to be equal to time
}
// Depth First Search Print
// Description: Calls Linked List methods (Print Parent, Print Discover Time, Print Finish Time) for each Linked List
// in aGraph in order to print the results of the Depth First Search.
void AdjacencyGraph::depthFirstSearchPrint()
{
    // Call Print Parent for each Linked List
    cout << "The array pi content: "<< endl << endl;
    for (int i = 0; i < tableSize; i++)
    {
        aGraph[i]->printParent();
    }
    cout << "" << endl<<endl;
    // Call Print Discover Time for each Linked List
    cout << "The array discoverTime content: "<<endl<<endl;
    for (int j = 0; j < tableSize; j++)
    {
        aGraph[j]->printDiscoverTime();
    }
    cout << "" << endl<<endl;
    // Call Print Finish Time for each Linked List
    cout << "The array finishTime content: " << endl<<endl;
    for (int k = 0; k < tableSize; k++)
    {
        aGraph[k]->printFinishTime();
    }
    cout <<""<<endl<<endl;
}
#endif // ADJACENCYGRAPH_H_INCLUDED
