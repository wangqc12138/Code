#ifndef __INTERFERENCE_GRAPH__HPP
#define __INTERFERENCE_GRAPH__HPP

#include <exception>
#include <string>
#include <unordered_set>
#include <map>
class UnknownVertexException : public std::runtime_error
{
public:
    UnknownVertexException(const std::string &v)
        : std::runtime_error("Unknown vertex " + v) {}
};

class UnknownEdgeException : public std::runtime_error
{
public:
    UnknownEdgeException(const std::string &v, const std::string &w)
        : std::runtime_error("Unknown edge " + v + " - " + w) {}
};

// InterferenceGraph
//
// This is a class representing an interference graph
// as described in "Part 1: Interference Graph" of the README.md
// file.
template <typename T>
class InterferenceGraph
{
public:
    // Custom type used to represent edges. This is mainly
    // used in the utility function for reading and writing
    // the graph structure to/from files. You don't need to use it.
    using EdgeTy = std::pair<T, T>;

    InterferenceGraph();

    ~InterferenceGraph();

    void addEdge(const T &v, const T &w);

    void addVertex(const T &vertex) noexcept;

    void removeEdge(const T &v, const T &w);

    void removeVertex(const T &vertex);

    std::unordered_set<T> vertices() const noexcept;

    std::unordered_set<T> neighbors(const T &vertex) const;

    unsigned numVertices() const noexcept;

    unsigned numEdges() const noexcept;

    bool interferes(const T &v, const T &w) const;

    unsigned degree(const T &v) const;

private:
    // Private member variables here.
    unordered_set<T> ver;
    map<T, unordered_set<T>> next;
    int edgenum = 0;
};

template <typename T>
InterferenceGraph<T>::InterferenceGraph()
{
    ver.clear();
    next.clear();
    edgenum = 0;
}

template <typename T>
InterferenceGraph<T>::~InterferenceGraph() {}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::neighbors(const T &vertex) const
{
    return next[vertex];
    return {};
}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::vertices() const noexcept
{
    return ver;
    return {};
}

template <typename T>
unsigned InterferenceGraph<T>::numVertices() const noexcept
{
    return ver.size();
    return 0;
}

template <typename T>
unsigned InterferenceGraph<T>::numEdges() const noexcept
{
    return edgenum;
    return 0;
}

template <typename T>
void InterferenceGraph<T>::addEdge(const T &v, const T &w)
{
    next[v].emplace(w);
    next[w].emplace(v);
    // 原来没有这个点需不需要加？
    if (!ver.count(v))
    {
        ver.emplace(v);
    }
    if (!ver.count(w))
    {
        ver.emplace(w);
    }
    edgenum++;
}

template <typename T>
void InterferenceGraph<T>::removeEdge(const T &v, const T &w)
{
    next[v].erase(w);
    next[w].erase(v);
    // 这个点关联的边不存在了，需不需要删？
    if (next[v].empty())
    {
        ver.erase(v);
        next.erase(v);
    }
    if (next[w].empty())
    {
        ver.erase(w);
        next.erase(w);
    }
    edgenum--;
}

template <typename T>
void InterferenceGraph<T>::addVertex(const T &vertex) noexcept
{
    ver.emplace(vertex);
}

template <typename T>
void InterferenceGraph<T>::removeVertex(const T &vertex)
{
    ver.erase(vertex);
    if (next.count(vertex))
    {
        next.erase(vertex);
    }
}

template <typename T>
bool InterferenceGraph<T>::interferes(const T &v, const T &w) const { return false; }

template <typename T>
unsigned InterferenceGraph<T>::degree(const T &v) const { return next[v].size(); }

#endif
