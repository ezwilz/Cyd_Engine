#include "Graphs.h"

void Graphs::addVertex(int vertex)
{
	m_graph[vertex] = {};
}

void Graphs::addEdge(int v1, int v2)
{
	m_graph[v1].push_back(v2);
	m_graph[v2].push_back(v1);
}

void Graphs::removeVertex(int vertex)
{
	if (m_graph.find(vertex) == m_graph.end())
	{
		return;
	}

	m_graph.erase(vertex);

	for (auto& element : m_graph)
	{
		auto& value = element.second;
		value.erase(remove(value.begin(), value.end(), vertex), value.end());
	}
}

vector<int> Graphs::getVertices()
{
	cout << "Vectices: ";
	vector<int> vertices;

	for (const auto& element : m_graph)
	{
		vertices.push_back(element.first);
		cout << element.first << " ";
	}
	cout << "\n";

	return vertices;
}

vector<int> Graphs::getEgdes(int vertex)
{
	if (m_graph.find(vertex) == m_graph.end())
	{
		cout << "Invalid Vertex\n";
		return{};
	}

	cout << "Edges: ";
	for (const auto& i : m_graph[vertex])
	{
		cout << i << " ";
	}
	cout << "\n";
	return m_graph[vertex];
}

void Graphs::printGraph()
{
	cout << "Current Graph: \n";
	for (const auto& element : m_graph)
	{
		std::cout << element.first << " : ";
		for (const auto& curEdge : element.second)
		{
			std::cout << curEdge << " ";
		}
		std::cout << "\n";
	}
}

bool Graphs::CheckConnection(int vertexA, int vertexB) // A is the one we know, B is the one to look for
{

	if (m_graph.find(vertexA) == m_graph.end() || m_graph.find(vertexB) == m_graph.end())
	{
		cout << "Invalid Vertex\n";
		return false;
	}

	for (const auto& curEdge : m_graph[vertexA])
	{
		if (curEdge == vertexB)
		{
			return true;
		}
	}
	return false;
}

bool Graphs::CheckForNeighbour(int vertexA, int vertexB)
{
	if (m_graph.find(vertexA) == m_graph.end() || m_graph.find(vertexB) == m_graph.end())
	{
		cout << "Invalid Vertex\n";
		return NULL;
	}

	for (const auto& edge : m_graph[vertexA])
	{
		for (const auto& edge2 : m_graph[vertexB])
		{
			if (edge == edge2)
			{
				return true;
			}
		}
	}
	return false;
}

bool Graphs::CheckForConnection(int a, int b)
{
	if (m_graph.find(a) == m_graph.end() || m_graph.find(b) == m_graph.end())
	{
		cout << "Invalid Vertex\n";
		return false;
	}

	for (const auto& edge : m_graph[a])
	{
		if (edge == b)
		{
			return true;
		}
	}
	cout << "Invalid Vertex\n";
	return false;
}

/*int getPath(int currentvertex, int targetVertex)
{
	if (currentvertex == targetVertex)
		return 0;

	for (const auto& edge : m_graph[currentvertex])
	{
		if (edge == targetVertex)
		{
			cout << "Path: " << edge << "\n";
			return targetVertex;
		}
		for (const auto& edge2 : m_graph[edge])
		{
			if (edge2 == targetVertex)
			{
				cout << "Path: " << edge << ", " << edge2 << "\n";
				return edge;
			}
			for (const auto& edge3 : m_graph[edge2])
			{
				if (edge3 == targetVertex)
				{
					cout << "Path: " << edge << ", " << edge2 << ", " << edge3 << "\n";
					return edge3;
				}
			}
		}
	}

	printf("Path Not Found \n");
	return 0;
}*/


//bool getPath(int currentVertex, int targetVertex, vector<int>& path)
//{
//	// Add the current vertex to the path
//	path.push_back(currentVertex);

//	// Check if the target vertex is reached
//	if (currentVertex == targetVertex)
//		return true;

//	// Traverse the adjacent vertices
//	for (const auto& neighbor : m_graph[currentVertex])
//	{
//		if (getPath(neighbor, targetVertex, path))
//			return true;
//	}

//	// Backtrack if no path is found
//	path.pop_back();
//	return false;
//}

vector<int> Graphs::returnPath(int currentVertex, int targetVertex)
{
	vector<int> path;
	vector<int> checkedVertices;
	if (currentVertex == targetVertex)
		return path;

	for (const auto& edge : m_graph[currentVertex])
	{
		if (edge == targetVertex)
		{
			path.push_back(edge);
			return path;
		}
		for (const auto& edge2 : m_graph[edge])
		{
			if (edge2 == targetVertex)
			{
				if (edge2 != currentVertex)
				{
					cout << "Path: " << edge << ", " << edge2 << "\n";
					path.push_back(edge & edge2);
					return path;
				}
			}

			for (const auto& edge3 : m_graph[edge2])
			{
				if (edge3 == targetVertex)
				{
					if (edge2 != currentVertex)
					{
						cout << "Path: " << edge << ", " << edge2 << ", " << edge3 << "\n";
						path.push_back(edge & edge2 & edge3);
						return path;
					}
				}

				for (const auto& edge4 : m_graph[edge3])
				{
					if (edge4 == targetVertex)
					{
						if (edge2 != currentVertex)
						{
							cout << "Path: " << edge << ", " << edge2 << ", " << edge3 << ", " << edge4 << "\n";
							path.push_back(edge & edge2 & edge3 & edge4);
							return path;
						}
					}
				}
			}
		}
	}

	printf("Path Not Found \n");
	return path;
}

bool Graphs::CheckForVertexPresence(int x)
{
	if (m_graph.find(x) == m_graph.end())
		return false;
	else
		return true;
}

map<int, vector<int>>  Graphs::GetGraph()
{
	return m_graph;
}

void Graphs::CopyVertices(int vertex, map<int, vector<int>> graphOG)
{
	// add each edge from the vertex to the memory graph.
	for (const auto& el : graphOG[vertex])
	{
		// If the vertex doesn't exist yet, add it to the memory graph.
		if (m_graph.find(el) == m_graph.end())
		{
			addVertex(el);

			// if the vertex is new, add a new struct version of the node on the graph. 
			for (int i = 0; i < 60; ++i) {
				for (int j = 0; j < 60; ++j) {
					if (level.rooms[i][j] == el)
					{
						Vector2D pos = Vector2D(j, i);
						double id = el;
						createANewSpace(id, pos);
					}
				}
			}


		}
		// add the connection between the vertex and the adjacent
		addEdge(vertex, el);
	}
}

int Graphs::MovingThroughDoor(int curr, int last, map<int, vector<int>>  graphOG)
{
	// all doors are less than 200, IN THIS INSTANCE!
	if ((curr - 200) < 0)
	{
		for (const auto& e : graphOG[curr])
		{
			if (e != last)
				cout << "FBNAJDNLKDANd " << e;
			return e;

		}
	}
	cout << "Return " << curr << endl;
	return curr;
}

void Graphs::createANewSpace(double i, Vector2D p)
{
	Space newSpace = Space(i, p);
	roomsNDoorsList.push_back(newSpace);
}