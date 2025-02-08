#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class Graph
{
private:
	map<int, vector<int>> m_graph;

public:

	Graph() {}

	void addVertex(int vertex)
	{
		m_graph[vertex] = {};
	}

	void addEdge(int v1, int v2)
	{
		m_graph[v1].push_back(v2);
		m_graph[v2].push_back(v1);
	}

	void removeVertex(int vertex)
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

	vector<int> getVertices()
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

	vector<int> getEgdes(int vertex)
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

};

