#include "Astar.h"


void Astar::setTargetPosition(int x, int y)
{
	//targetPosition.x = x;
	//targetPosition.y = y;
}

//void Astar::getAllNeighbours(int x, int y, int rows, int cols) {
//    // directions for 4 way movement  ( no diagonals becayse i dont want clipping...)
//    int directionX[] = { -1, 1,  0, 0, -1, -1,  1,  1 };
//    int directionY[] = { 0, 0, -1, 1, -1,  1, -1,  1 };
//
//    for (int i = 0; i <= 8; i++) {
//        int newX = x + directionX[i];
//        int newY = y + directionY[i];
//
//        // check the position is in the array
//        if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
//
//            //check space is FREE
//            if (level.house[newY][newX] == 0)
//            {
//                // make sure we are not adding a position which is alreayd in either hte open or closed list!!!!!
//                if (!isInList(openList, Vector2D(newX,newY)) && !isInList(closedList, Vector2D(newX, newY)))
//                {
//                    //if the position is on the array, push it to the list
//                    Vector2D neighbour = Vector2D(newX, newY);
//                    openList.push_back(neighbour);
//
//                    // the first 
//                    openParentList.push_back(Vector2D(x, y));
//                    // calculate the cost and put it in the same position in the cost list! bomba 
//                    costList.push_back(neighbour.diagonalDistance(targetPosition));
//                }
//            }
//        }
//    }
//
//    // MOVING THE CURRENT NODE TO THE CLOSED LIST AND ITS PARENT TO THE CLOSED PARENT LIST!
//    Vector2D removeIt = Vector2D(x, y);
//    int index = getIndex(openList, removeIt);
//    if (index != -1)
//    {
//        // the first node is the starting position and therefore will not have a parent node.
//        if (!openParentList.empty())
//        {
//            //send the parent node linked to the current node being looked at to the closed parent list nodes so we can find them when we need it
//            closedParentList.push_back(openParentList[index]);
//            closedCostList.push_back(costList[index]);
//            costList.erase(costList.begin() + index);
//            openParentList.erase(openParentList.begin() + index);
//
//        }
//        
//    }
//    /*openList.erase(remove(openList.begin(), openList.end(), removeIt), openList.end());*/
//    auto it = std::find(openList.begin(), openList.end(), removeIt);
//    if (it != openList.end()) {
//        openList.erase(it);
//    }
//
//    // the closed list and the parent list indexes should allign together! e.g. 1 in the parent list will be the parent of 1 in the closed list.
//    closedList.push_back(removeIt);
//    
//}

//void Astar::checkOpenList()
//{
//    int minIndex = 0;
//    double minCost = costList[0]; // Assume first element is the smallest
//
//    for (int i = 1; i < costList.size(); i++) {
//        if (costList[i] < minCost) {
//            minCost = costList[i];
//            minIndex = i;
//            /*if (openList[i].x == targetPosition.x && openList[i].y == targetPosition.y)
//            {
//                finalPosition = openList[i];
//                closedList.push_back(finalPosition);
//                closedParentList.push_back(openParentList[i]);
//            }*/
//            if (currentNode.x == targetPosition.x && currentNode.y == targetPosition.y) {
//                finalPosition = currentNode;
//                break; // Stop searching
//            }
//        }
//    }
//    currentNode = openList[minIndex];
//}

//void Astar::search(int currX, int currY, int tarX, int tarY)
//{
//    finalPosition.x = -1;
//    finalPosition.y = -1;
//    pathList.clear();
//
//    currentPosition.x = currX;
//    currentPosition.y = currY;
//
//    setTargetPosition(tarX, tarY);
//
//    
//    searching = true;
//    currentNode = currentPosition;
//    openList.push_back(currentNode);
//    /*while (!openList.empty())
//    {
//        getAllNeighbours(currentNode.x, currentNode.y, 60, 60);
//        checkOpenList();
//        if (finalPosition.x != -1 && finalPosition.y != -1)
//        {
//            buildPath();
//            openList.clear();
//            openParentList.clear();
//            closedParentList.clear();
//            closedList.clear();
//
//        }
//       
//    }*/
//
//    while (!openList.empty()) {
//        getAllNeighbours(currentNode.x, currentNode.y, 60, 60);
//        checkOpenList();
//
//        if (finalPosition.x != -1 && finalPosition.y != -1) {
//            buildPath();
//            openList.clear();
//            openParentList.clear();
//            closedParentList.clear();
//            closedList.clear();
//            break; // Exit loop
//        }
//    }
//
//
//}

void Astar::getAllNeighbours( int rows, int cols) {
    int directionX[] = { -1, 1,  0, 0, -1, -1,  1,  1 };
    int directionY[] = { 0, 0, -1, 1, -1,  1, -1,  1 };

    for (int i = 0; i < 8; i++) {
        int newX = currentNode.position.x + directionX[i];
        int newY = currentNode.position.y + directionY[i];
        cout << "\nGettingDirectional\n";

       // searchLoop += 1;

        if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
            cout << "\nCheckingItsOntheBoard\n";
            if (level.house[newY][newX] == 0)
            { // Ensure it's walkable
                //make sure its not already on the list
                if (!(CheckForItemInList(openList, Vector2D(newX, newY)) && CheckForItemInList(closedList, Vector2D(newX, newY))))
                {
                    double h = diagonalDistance(Vector2D(newX, newY), currentNode.position);
                    Node* newNode = new Node(Vector2D(newX, newY), currentNode.position, 1, h);
                    cout << "\nAddingTheNeighbourToOpenList\n";
                    openList.push_back(newNode); // Store a reference
                }
            }
        }
    }

    cout << "\nFinishedWithTheNode\n";
    double h = diagonalDistance(currentNode.position, targetPosition.position);
  //  if (currentNode.parent != nullptr)
    Node* pushBackNode = new Node(currentNode.position, currentNode.parent, 1, h);
    closedList.push_back(pushBackNode);
    if (currentNode.parent == Vector2D(-1,-1))
    {
        cout << "\n Node: " << currentNode.position << " Parent: " << currentNode.parent << "\n";
    }
     
    int index = getIndex(openList, currentNode.position);
    if (index != -1) { // Ensure index is valid
        openList.erase(openList.begin() + index);
    }

    cout << "\nCurrentNodeMovedToTheClosedList\n";
}


void Astar::checkOpenList()
{
    bool nextNodeFound = false;
    Node nextNode = Node(Vector2D(0, 0), Vector2D(-1,-1), 0, 0);
    cout << "\nCheckingTheOpenList\n";
    if (!openList.empty()) {
        nextNode = *openList[0];
    }
    for (int i = 0; i < openList.size(); i++)
    {
        if (openList[i]->position == targetPosition.position)
        {
            finalNode.position = openList[i]->position;
            finalNode.parent = openList[i]->parent;
            closedList.push_back(&finalNode);
            cout << "\nFoundTheFinalNode\n" << finalNode.position << " , " << targetPosition.position;
        }
        openList[i]->hCost = getDistanceAtoB(*openList[i],targetPosition);
        if (openList[i]->hCost < smallestCost)
        {
            smallestCost = openList[i]->hCost;
            nextNode.position = openList[i]->position;
            nextNode.parent = openList[i]->parent;
            nextNodeFound = true;
            cout << "\nFoundTheNextClosestNode\n";
        }
    }
    //increase the next search
    smallestCost += 1;
    cout << "\nSetTheCurrentNodeToTheNextNode\n";
    currentNode.position = nextNode.position;
    currentNode.parent = nextNode.parent;
    cout << "Current node: " << currentNode.position << "\n";
}

void Astar::search(int currX, int currY, int tarX, int tarY) 
{
        bool targetOnTheBoard;
        cout << "\nResettingLists\n";
        smallestCost = 1000000000000;
        finalNode.position.x = -1;
        finalNode.position.y = -1;


        pathList.clear();
        openList.clear();
        closedList.clear();
    
        currentPosition.position.x = currX;
        currentPosition.position.y = currY;
        targetPosition.position.x = tarX;
        targetPosition.position.y = tarY;

        if ((targetPosition.position.x > 60 || targetPosition.position.x < 0) || (targetPosition.position.y > 60 || targetPosition.position.y < 0))
        {
            printf("\nTarget Is Off the Board\n");
            targetOnTheBoard = false;
        }
        else
        {
            targetOnTheBoard = true;
        }
    
        searching = true;
        startNode = Node(currentPosition.position, Vector2D(-1,-1), 0, 0);
        currentNode = startNode;
        if (targetOnTheBoard)
        {
            getAllNeighbours(60, 60);
            while (!openList.empty()) {

                if (iterationCount > maxIterationCount)
                {
                    searching = false;
                    openList.clear();
                    closedList.clear();
                    pathList.clear();
;                   break;
                }
                if (!CheckForTargetInClosed())
                {
                    cout << (CheckForTargetInClosed());
                    cout << "\nCallingNeighbours\n";
                    getAllNeighbours( 60, 60);
                    cout << "\nCallingCheckOnOpenList\n";
                    checkOpenList();
                    cout << "\nCheckingForTheFinalNode\n";
                    // if the final Node hsa been set, it means it is on the closed list
                    iterationCount += 1;
                }
                else if (CheckForTargetInClosed())
                {
                    printf("\nThe Final Node is in the closed list\n");
                    openList.clear();
                    break;
                }
            }
            printf("\nGot to Step A\n");
            cout << "\nWhileLoopBroken\n";
            
        }
        if (iterationCount < 1000)
        {
            buildPath();
        }
        else
        {
            cout << "PathFinding Cancelled - f to t" << endl;
            pathFindingCancelled = true;
        }
        iterationCount = 0;

        /*for (int i = 0; i < pathList.size(); i++)
        {
            if (pathList[i]->parent == Vector2D(-1,-1))
            {
                cout << "\n Node " << pathList[i]->position << "'s parent returned nullptr.\n";
            }
            else
            {
                cout << "\n Node " << pathList[i]->position << " Parent: " << pathList[i]->parent << "\n";
            }
        }

        if (pathList.empty() && finalNode.position.x == -1)
        {
            cout << "\nPathNotViable\n";
        }*/
}

void Astar::buildPath() {
    printf("\nGot to Step B\n");

    if (finalNode.parent == Vector2D(-1,-1)) {
        cout << "Error: finalNode has no parent! A* did not link nodes correctly.\n";
        return;
    }

    //THIS PRINTS OUT THE PARENTS CORRECTLY
    for (int i = 0; i < closedList.size(); i++)
    {
        if (closedList[i]->parent == Vector2D(-1, -1))
        {
            cout << "\nClosed Node: " << closedList[i]->position << " Closed Parent Node: NULL"<< "\n";
        }
        else
        {
            cout << "\nClosed Node: " << closedList[i]->position << " Closed Parent Node: " << closedList[i]->parent << "\n";

        }
    }

    currentNode.position = finalNode.position;
    currentNode.parent = finalNode.parent;
    cout << "\nReconstructing Path\n";
    cout << "\n Target Position: " << targetPosition.position << "\nCurrentPosition: " << currentPosition.position << endl;
    cout << "Final Node: (" << finalNode.position.x << ", " << finalNode.position.y << ")\n";

    //THIS STOPS AT THE PENULTIMATE NODE AND SAYS THAT NODE IS ITS OWN PARENT
    while (!(currentNode.parent == Vector2D(-1, -1))) { // Stop when reaching the start node
        cout << "Backtracking - Current Node: (" << currentNode.position.x << ", " << currentNode.position.y << ")\n Parent Node: (" << currentNode.parent.x << ", " << currentNode.parent.y << ")\n Final Node: (" << finalNode.position.x << ", " << finalNode.position.y << ")\n";

        // Move to the parent node
        pathList.push_back(new Node(currentNode));
        int index = getIndex(closedList, currentNode.parent);
        Node* nextStep = new Node(currentNode.parent, closedList[index]->parent, currentNode.gCost, currentNode.hCost);
        cout << "\nNextStep Position: " << nextStep->position << " NextStep Parent: " << nextStep->parent << "\n";
        currentNode.position = nextStep->position;
        currentNode.parent = nextStep->parent;
        

        if (currentNode.position == startNode.position) {
            cout << "\nPath Complete! Reached Start Node\n";
            break;
        }

        if (currentNode.position == currentNode.parent)
        {
            cout << "\nBuild Path is a loop, parent not stored correctly.\n";
            break;
        }
    }

    // the list is full of starting node and not the actual path? 
    cout << "\nAdded Start Node to Path\n";


    for (int i = 0; i < pathList.size();i++)
    {
        cout << "\n Final path position " << i << ": " << pathList[i]->position << "Parent: " << pathList[i]->parent << "\n";
    }

    searching = false;

}


//int Astar::getIndex(const std::vector<Node*>& list, const Node* target) {
//    auto it = std::find(list.begin(), list.end(), target);
//
//    if (it != list.end()) {
//        return std::distance(list.begin(), it); // Get index
//    }
//    return -1; // Not found
//}

int Astar::getIndex(const std::vector<Node*>& list, const Vector2D target) {
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i]->position == target)
        {
            return i;
        }
    }
    return -1; // Not found
}

//void Astar::buildPath()
//{
//    
//    currentNode = targetPosition;
//
//    while (currentNode.x != currentPosition.x && currentNode.y != currentPosition.y)
//    {
//        pathList.push_back(currentNode);
//
//        int nxtIndex = getIndex(closedList, currentNode);
//        if (nxtIndex == -1) { // Ensure node exists
//            std::cout << "Error: currentNode not found in closedList!\n";
//            break;
//        }
//
//        currentNode = closedParentList[nxtIndex];
//    }
//
//    searching = false;
//}


//
//vector<Node> Astar::getPath()
//{
//    return pathList;
//}
double Astar::diagonalDistance(Vector2D a, Vector2D b) {
    return std::max(std::abs(a.x - b.x), std::abs(a.y - b.y));
}

bool Astar::CheckForItemInList(vector<Node*> nodeList, Vector2D node)
{
    for (int i = 0; i < nodeList.size(); i++)
    {
        if (nodeList[i]->position.x == node.x)
        {
            if (nodeList[i]->position.y == node.y)
            {
                return true;
            }
        }
    }
    return false;
}

bool Astar::CheckForTargetInClosed()
{
    for (int i = 0; i < closedList.size(); i++)
    {
        if (closedList[i]->position.x == targetPosition.position.x)
        {
            if (closedList[i]->position.y == targetPosition.position.y)
            {
                return true;
            }
        }
    }
    return false;
}

double Astar::getDistanceAtoB(Node a, Node b)
{
    double x = max(abs(a.position.x - b.position.x),abs(a.position.y - b.position.y));
    return x;
}