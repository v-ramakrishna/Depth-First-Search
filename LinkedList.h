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
//              This is the header/implementation file for the Linked List class, used throughout the Adjacency Graph.

#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include <iostream> //to use cout
#include <iomanip> //to format output
#include <string> //to use strings
#include <stdlib.h> //to use dynamic memory allocation

using namespace std;

// TeamNode represents some Team information
struct TeamNode
{
    string name;
    string score;
    TeamNode * next;
};
//class LinkedList will contain a linked list of TeamNodes and store vertex information
class LinkedList
{
    private:
        string alphaKey;
        TeamNode * head;
        LinkedList * parent;
        int discoverTime;
        int finishTime;
        char color;

    public:
        LinkedList(string name);
        void deleteList();
        void graphParseNodes(string newEntry);
        void graphInsertNode(string newEntry);
        void graphInsertEdge(string newEntry);
        void removeTeam(string someName);
        void printList();
        void printParent();
        void printDiscoverTime();
        void printFinishTime();
        TeamNode * getHead();
        string getName();
        void setColor(char mColor);
        char getColor();
        void nullifyParent();
        void setParent(LinkedList * newParent);
        void setDiscoverTime(int time);
        void setFinishTime(int time);
};
// Linked List Constructor
// Description: Constructor to initialize a Linked List
LinkedList::LinkedList(string name)
{
    head = NULL;
    alphaKey = name;
}

// Delete List
// Description: Destructor for the Linked List. While the root of the Red-Black Tree is not null, will call
// the Tree Delete method on the root of the tree.
void LinkedList::deleteList()
{
    struct TeamNode * removerPointer = NULL;
    struct TeamNode * holderPointer = NULL;
    string nameHolder;
    // Find head of list
    if (head != NULL)
    {
            removerPointer = head;
            holderPointer = head;
    }
    if (removerPointer != NULL)
    {
        //Delete items until list is empty by extracting names and calling Remove Team
        while (removerPointer != NULL)
        {
                removerPointer = holderPointer->next;
                nameHolder = holderPointer->name;
                removeTeam(nameHolder);
                holderPointer = removerPointer;
        }
    }
    //Set head and alphaKey to NULL
    head = NULL;
    alphaKey = "";
}
// Graph Parse Nodes
// Description: Parses data to be passed to Graph Insert Node, and calls this method for each of the two nodes
// that each line from the Edges file should contain.
void LinkedList::graphParseNodes(string newEntry)
{
    // Validate Entry
    int commaCounter = 0;
    // Count the number of commas in the command
    for (int i = 0; i < newEntry.size(); i++)
    {
        if (newEntry.substr(i, 1) == ",")
        {
            commaCounter++;
        }
    }
    // If the number of commas is not 3, immediately end the search and return false
    if(commaCounter != 3)
    {
        cout << "Invalid Edge: Skipping Line";
        return;
    }
    // Create string variables to hold data from lines
    string mTeam1 = "";
    string mTeam1Score = "";
    string mTeam2 = "";
    string mTeam2Score = "";
    //Create size_t variables to mark comma positions
    size_t Team1Token;
    size_t Team1ScoreToken;
    size_t Team2Token;
    size_t Team2ScoreToken;
    // Find commas in edge
    Team1Token = newEntry.find(",");
    Team1ScoreToken = newEntry.find(",", Team1Token+1, 1);
    Team2Token = newEntry.find(",", Team1ScoreToken+1, 1);
    Team2ScoreToken = newEntry.find(",", Team2ScoreToken+1, 1);

    // Assign values to previously created strings, based on comma positions
    mTeam1 = newEntry.substr(0, Team1Token);
    mTeam1Score = newEntry.substr(Team1Token + 1, Team1ScoreToken - Team1Token - 1);
    mTeam2 = newEntry.substr(Team1ScoreToken + 1, Team2Token - Team1ScoreToken - 1);
    mTeam2Score = newEntry.substr(Team2Token+1, Team2ScoreToken-Team2Token-1);

    // Call Graph Insert Node for both team names which were extracted
    graphInsertNode(mTeam1);
    graphInsertNode(mTeam2);
    return;
}
// Graph Insert Node
// Description: Inserts Nodes into original preparatory Linked List, used to generate additional Linked Lists
// for every node. Will only add nodes to the list if they do not already exist in the list. Adds nodes in alphabetical
// order.
void LinkedList::graphInsertNode(string newEntry)
{
    struct TeamNode * newTeam = new TeamNode;
    // Memory Checking
    if (newTeam == NULL)
    {
        cout << "Insufficient Memory for New Vertex"<< endl<< endl;
        return;
    }
    //Initialize variables
    struct TeamNode * currentOnList = NULL;
    string currentName;
    struct TeamNode * savePosition = NULL;
    string previousName;
    string mName = newEntry;
    newTeam->name = mName; // Set name for new node
    // If head is NULL, make the new node the head
    if (head == NULL)
    {
        head = newTeam;
        head->next = NULL;
        return;
    }
    // Extract information on head
    currentOnList = head;
    currentName = head->name;
    savePosition = head;
    previousName = head->name;

    if (head != NULL && head->next == NULL)
    {
        // If head is the only item in the list
        int shortComparator = currentName.compare(mName);
        if (shortComparator == 0)
        {
            // If the node already exists, do nothing to the list and return
            return;
        }
        else if (shortComparator < 0)
        {
            // if the new node's name is after the head alphabetically
            currentOnList->next = newTeam;
            newTeam->next = NULL;
            return;
        }
        else
        {
            // if the new node's name is before the head alphabetically
            head = newTeam;
            newTeam->next = currentOnList;
            currentOnList->next = NULL;
            return;
         }
    }
    else if (head != NULL && head->next != NULL)
    {
        // If the Linked List has at least 2 nodes
        int firstComparator = currentName.compare(mName);
        if (firstComparator > 0)
    	{
    	    // If new node comes first alphabetically, make it the head
    		newTeam->next = currentOnList;
    		head = newTeam;
    		return;
    	}
    	else if (firstComparator == 0)
        {
            // If the new node already exists in the Linked List, do nothing to the list and return
            return;
        }
    	else
        {
            // if the new node comes after the head alphabetically, set pointer to the node following the head
            currentOnList = currentOnList->next;
            currentName = currentOnList->name;
        }
    	while (currentOnList->next != NULL)
    	{
    	    // Loop until the pointer reaches the end of the list or until the appropriate place is found. Insert the node in the latter case.
    		int firstComparator = currentName.compare(mName);
    		if (firstComparator > 0)
    		{
    		    // if new node comes before current node alphabetically, insert it prior to it.
    			savePosition->next = newTeam;
    			newTeam->next = currentOnList;
    			return;
    		}
    		else if (firstComparator < 0)
    		{
    		    // if the new node comes after the current node alphabetically, get the next node
    		    savePosition = currentOnList;
    			currentOnList = currentOnList->next;
    			currentName = currentOnList->name;
    		}
    		else if (firstComparator == 0)
            {
                // If the new node already exists in the Linked List, do nothing to the list and return
                return;
            }
    	}
    	if (currentOnList->next == NULL)
        {
            // Special Procedure for the end of the list, if the node has not yet been inserted
            int firstComparator = currentName.compare(mName);
            if (firstComparator > 0)
            {
    		    // if new node comes before last node alphabetically, insert it prior to it.
                newTeam->next = currentOnList;
                savePosition->next = newTeam;
                return;
            }
            else if (firstComparator < 0)
            {
                // if the new node comes after the last node alphabetically, insert it as the end of the list
                currentOnList->next = newTeam;
                newTeam->next = NULL;
                return;
            }
            else if (firstComparator == 0)
            {
                // If the new node already exists in the Linked List, do nothing to the list and return
                return;
            }
        }
    }
    return;
}
// Graph Insert Edge
// Description: Inserts Edges into appropriate Linked List corresponding with a node. Will only add
// edges to the list if they do not already exist in the list. Adds nodes in alphabetical order. The
// determination of which Linked List to insert the edge into is determined by the method which calls this method,
// Generate Graph
void LinkedList::graphInsertEdge(string newEntry)
{
    // Create new node to represent Graph edge
    struct TeamNode * newTeam = new TeamNode;
    // Memory Checking
    if (newTeam == NULL)
    {
        cout << "Insufficient Memory for New Edge"<< endl<< endl;
        return;
    }
    // Validate Entry
    int commaCounter = 0;
    // Count the number of commas in the command
    for (int i = 0; i < newEntry.size(); i++)
    {
        if (newEntry.substr(i, 1) == ",")
        {
            commaCounter++;
        }
    }
    // If the number of commas is not 3, immediately end the search and return false
    if(commaCounter != 3)
    {
        cout << "Invalid Edge: Skipping Line";
        return;
    }
    // Create string variables to hold data from lines
    string mTeam1 = "";
    string mTeam1Score = "";
    string mTeam2 = "";
    string mTeam2Score = "";
    //Create size_t variables to mark comma positions
    size_t Team1Token;
    size_t Team1ScoreToken;
    size_t Team2Token;
    size_t Team2ScoreToken;
    // Find commas in edge
    Team1Token = newEntry.find(",");
    Team1ScoreToken = newEntry.find(",", Team1Token+1, 1);
    Team2Token = newEntry.find(",", Team1ScoreToken+1, 1);
    Team2ScoreToken = newEntry.find(",", Team2ScoreToken+1, 1);
    // Assign values to previously created strings, based on comma positions
    mTeam1 = newEntry.substr(0, Team1Token);
    mTeam1Score = newEntry.substr(Team1Token + 1, Team1ScoreToken - Team1Token - 1);
    mTeam2 = newEntry.substr(Team1ScoreToken + 1, Team2Token - Team1ScoreToken - 1);
    mTeam2Score = newEntry.substr(Team2Token+1, Team2ScoreToken-Team2Token-1);
    // Generate score by appending "(", Team 1's score, "-", Team 2's score, and ")"
    string mScore;
    mScore.append("(");
    mScore.append(mTeam1Score);
    mScore.append("-");
    mScore.append(mTeam2Score);
    mScore.append(")");
    // Assign name of Team 2 and score to new node
    newTeam->name = mTeam2;
    newTeam->score = mScore;
    // Initialize Variables
    struct TeamNode * currentOnList = NULL;
    string currentName;
    struct TeamNode * savePosition = NULL;
    string previousName;
    // If Linked List's head is null, insert new node as head
    if (head == NULL)
    {
        head = newTeam;
        head->next = NULL;
        return;
    }
    // Extract information on head
    currentOnList = head;
    currentName = head->name;
    savePosition = head;
    previousName = head->name;

    if (head != NULL && head->next == NULL)
    {
        // If head is the only item in the list
        int shortComparator = currentName.compare(mTeam2);
        if(shortComparator == 0)
        {
            // If the edge already exists, do nothing to the list and return
            return;
        }
        else if (shortComparator < 0)
        {
            // if the new edge's name is after the head alphabetically
            currentOnList->next = newTeam;
            newTeam->next = NULL;
            return;
        }
        else
        {
            // if the new edges's name is before the head alphabetically
            head = newTeam;
            newTeam->next = currentOnList;
            currentOnList->next = NULL;
            return;
         }
    }
    else if (head != NULL && head->next != NULL)
    {
        // If the Linked List has at least 2 nodes
        int firstComparator = currentName.compare(mTeam2);

        if (firstComparator > 0)
    	{
    	    // If new edge comes first alphabetically, make it the head
    		newTeam->next = currentOnList;
    		head = newTeam;
    		return;
    	}
        else if (firstComparator == 0)
        {
            // If the new edge already exists in the Linked List, do nothing to the list and return
            return;
        }
    	else
        {
            // if the new edge comes after the head alphabetically, set pointer to the node following the head
            currentOnList = currentOnList->next;
            currentName = currentOnList->name;
        }
    	while (currentOnList->next != NULL)
    	{
    	    // Loop until the pointer reaches the end of the list or until the appropriate place is found. Insert the node in the latter case.
    		int firstComparator = currentName.compare(mTeam2);
    		if (firstComparator > 0)
    		{
    		    // if new edge comes before current node alphabetically, insert it prior to it.
    			savePosition->next = newTeam;
    			newTeam->next = currentOnList;
    			return;
    		}
    		else if (firstComparator < 0)
    		{
    		    // if the new edge comes after the current node alphabetically, get the next node
    		    savePosition = currentOnList;
    			currentOnList = currentOnList->next;
    			currentName = currentOnList->name;
    		}
            else if (firstComparator == 0)
            {
                // If the new edge already exists in the Linked List, do nothing to the list and return
                return;
            }
    	}
    	if (currentOnList->next == NULL)
        {
            // Special Procedure for the end of the list, if the edge has not yet been inserted
            int firstComparator = currentName.compare(mTeam2);
            if (firstComparator > 0)
            {
    		    // if new edge comes before last node alphabetically, insert it prior to it.
                newTeam->next = currentOnList;
                savePosition->next = newTeam;
                return;
            }
            else if (firstComparator < 0)
            {
                // if the new edge comes after the last node alphabetically, insert it as the end of the list
                currentOnList->next = newTeam;
                newTeam->next = NULL;
                return;
            }
            else if (firstComparator == 0)
            {
                // If the new edge already exists in the Linked List, do nothing to the list and return
                return;
            }
        }
    }
    return;
}
// Remove Team
// Description: Searches for a node corresponding with a given name in the Linked List. If the
// node is found, will delete it from the list, and modify other node's pointers to make the list
// still work.
void LinkedList::removeTeam(string someName)
{
    // Initialize Variables
    string findTeamName = someName;
    struct TeamNode * currentOnList = NULL;
    struct TeamNode * nextOnList = NULL;
    string saveHeadName;
    string extractNextName;
    if (head == NULL) // If Linked List is empty, print error message and return
    {
        cout << "Deletion of node " << findTeamName << " failed."<< endl<< endl;
        return;
    }
    // Get information on head and following node, if it exists
    currentOnList = head;
    nextOnList = head->next;
    saveHeadName = head->name;
    if (head != NULL && head->next != NULL)
    {
        extractNextName = nextOnList->name;
    }
    if (head != NULL && head-> next == NULL)
    {
        // if list only contains head
        if (saveHeadName == findTeamName)
        {
            // if head name matches name of node to delete, delete the node and set head to NULL
            free(head);
            head = NULL;
            return;
        }
        else
        {
            // if head does not match name of node to delete, print error message and return
            cout << "Deletion of node " << findTeamName << " failed."<< endl<< endl;
            return;
        }
    }
    while(currentOnList->next != NULL)
    {
        // Loop to last node
        if(saveHeadName == findTeamName)
        {
            // if node to be deleted is the head, delete the head and set the following node to be the head
            free(head);
            head = nextOnList;
            return;
        }
        else if (extractNextName == findTeamName)
        {
            // if name of nextOnList is equal to the name of the node to be deleted, delete that node, and set its next to be the previous node's next.
            currentOnList->next = nextOnList->next;
            free(nextOnList);
            return;
        }
        else
        {
            // if name is not found, go to next node
            currentOnList = nextOnList;
            if (currentOnList->next == NULL)
            {
                // If correct node is not found by the last node, print error message and return
                cout << "Deletion of node " << findTeamName << " failed."<< endl<< endl;
                return;
            }
            nextOnList = currentOnList->next;
            extractNextName = nextOnList->name;
        }
    }
    return;
}
// Print List
// Description: Prints the contents (name and score) for each node in the Linked List.
void LinkedList::printList()
{
    struct TeamNode * currentPointer = NULL;
    if (head != NULL)
    {
        currentPointer = head;
        currentPointer->next = head->next;

    }
    cout << alphaKey << " beat: "; // Print team name and "beat "
    if (currentPointer == NULL)
	{
		cout << "none" <<endl<<endl; // If no items in the Linked List, print "none"
	}
    else if (currentPointer != NULL && currentPointer->next == NULL)
    {
       cout << currentPointer->name << currentPointer->score<<endl<<endl; // If only 1 item in the Linked List, print the name and score for the node
    }
    else
    {
        do
        {
            // loop until loop-end condition of currentPointer is NULL
            if (currentPointer->next == NULL)
            {
                // if last item on the list, print the name and score for the node
                cout << currentPointer->name << currentPointer->score;
                currentPointer = currentPointer->next;
            }
            else
            {
                // if not last item on the list, print the name and score for the node, followed by a comma
                cout << currentPointer->name << currentPointer->score << ", ";
                currentPointer = currentPointer->next;
            }
        } while (currentPointer != NULL);
        cout << "" <<endl<<endl;
    }
}
// Print Parent
// Description: Prints the Parent's name for the Linked List.
void LinkedList::printParent()
{
    if (parent == NULL)
    {
        cout << "pi[" << alphaKey << "] = None" << endl;
    }
    else
    {
        cout << "pi[" << alphaKey << "] = " << parent->alphaKey << endl;
    }
}
// Print Discover Time
// Description: Prints the Discover Time for the Linked List.
void LinkedList::printDiscoverTime()
{
    cout << "discoverTime[" << alphaKey << "] = number " << discoverTime << endl;
}
// Print Finish Time
// Description: Prints the Finish Time for the Linked List.
void LinkedList::printFinishTime()
{
    cout << "finishTime[" << alphaKey << "] = number " << finishTime << endl;
}
// Get Head
// Description: Getter for the Linked List's head.
TeamNode * LinkedList::getHead()
{
    return head;
}
// Get Name
// Description: Getter for the Linked List's alphaKey.
string LinkedList::getName()
{
    return alphaKey;
}
// Set Color
// Description: Setter for the Linked List's color
void LinkedList::setColor(char mColor)
{
    color = mColor;
}
// Get Color
// Description: Getter for the Linked List's color.
char LinkedList::getColor()
{
    return color;
}
// Nullify Parent
// Description: Set's the Linked List's parent to NULL
void LinkedList::nullifyParent()
{
    parent = NULL;
}
// Set Parent
// Description: Setter for the Linked List's Parent
void LinkedList::setParent(LinkedList * newParent)
{
    parent = newParent;
}
// Set Discover Time
// Description: Setter for the Linked List's Discover Time
void LinkedList::setDiscoverTime(int time)
{
    discoverTime = time;
}
// Set Finish Time
// Description: Setter for the Linked List's Finish Time
void LinkedList::setFinishTime(int time)
{
    finishTime = time;
}
#endif // LINKEDLIST_H_INCLUDED
