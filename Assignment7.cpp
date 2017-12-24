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
//              This is the Driver file for the program.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "AdjacencyGraph.h"

using namespace std;

void processGraph(string newEntry, AdjacencyGraph * graph);

// Main
// Description: Driver to initialize, populate, and manipulate Adjacency Graph and run the program to issue commands
int main()
{
    ifstream fileReader;
    string newEntry;
    string endMarker = "\r";
    AdjacencyGraph * graph = new AdjacencyGraph();
    // Open File Reader
    fileReader.open("commands1.txt");
    if (!fileReader)
    {
        cout << "Unable to Open File";
        return 1; // if file cannot be found terminate with error
    }
    while (getline(fileReader, newEntry)) //loop until the file ends or a "quit" command is read
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
        // Print latest command to console
        cout << endl << endl << "next command: " << newEntry << endl<<endl;
        if (newEntry.substr(0,5) == "graph")
        {
            processGraph(newEntry, graph); //call Process Graph
        }
        else if (newEntry == "print_graph")
        {
            graph->printGraph(); // call Print Graph
        }
        else if (newEntry == "depth_first_search")
        {
            graph->depthFirstSearch(); // call Depth-First-Search
        }
        else if (newEntry == "end_graph")
        {
            graph->destructor(); // Call Adjacency Graph Destructor
        }
        else if (newEntry == "quit")
        {
            break; // break loop
        }
        else
        {
            cout << "Invalid Command: Skipping Line"<< endl<< endl; // Print error message to console
        }
    }
    // Close File Reader
    fileReader.close();
    return 0;
}
// Process Graph
// Description: Parses, casts to integers, and processes the numerical values contained
// within the "graph,int,int" command in the Command file. Uses the result as arguments in the Generate Graph method
// for the Adjacency Table, to determine which lines to read in the Edges file.
void processGraph(string newEntry, AdjacencyGraph * graph)
{
    // Validate Graph Entry
    int commaCounter = 0;
    // Count the number of commas in the command
    for (int i = 0; i < newEntry.size(); i++)
    {
        if (newEntry.substr(i, 1) == ",")
        {
            commaCounter++;
        }
    }
    // If the number of commas is not 2, print error message to console, and skip the line
    if(commaCounter != 2)
    {
        cout << "Invalid Command: Skipping Line"<< endl<<endl;
        return;
    }

    // Create strings to hold data from commands
    string firstLine;
    string lastLine;
    int firstLineOut = 0;
    int lastLineOut = 0;

    //Create size_t variables to mark comma positions
    size_t graphToken;
    size_t firstLineToken;
    size_t lastLineToken;

    // Find commas in search command
    graphToken = newEntry.find(",");
    firstLineToken = newEntry.find(",", graphToken+1, 1);
    lastLineToken = newEntry.find(",", firstLineToken+1, 1);

    // Assign values to previously created strings, based on comma positions
    firstLine = newEntry.substr(graphToken+ 1, firstLineToken - graphToken - 1);
    lastLine = newEntry.substr(firstLineToken + 1, lastLineToken - firstLineToken - 1);

    // Convert numeric strings from parsed line to integers
    stringstream convert1(firstLine);
    stringstream convert2(lastLine);

    convert1 >> firstLineOut;
    convert2 >> lastLineOut;

    // Validate first and last line to read
    if ((firstLineOut == 0 && firstLine != "0") || (lastLineOut == 0 && lastLine != "0"))
    {
        cout << "Invalid Command: Skipping Line" << endl<<endl;
        return;
    }
    // Call Generate Graph, using the parsed numeric strings, converted to integers, as arguments
    graph->generateGraph(firstLineOut, lastLineOut);
}
