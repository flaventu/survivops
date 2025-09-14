#pragma once

#include <vector>
#include <queue>
#include <unordered_map>

#include <cmath>
#include <limits>
#include <algorithm>

#include <functional>

#include <SFML/Graphics.hpp>

// Hash function for sf::Vector2i so it can be used in unordered_map (using big primes numbers to avoid collisions)
namespace std {
    template<>
    struct hash<sf::Vector2i> {
        std::size_t operator()(const sf::Vector2i& v) const {
            return (std::hash<int>()(v.x) * 73856093) ^ (std::hash<int>()(v.y) * 19349663);
        }
    };
}

// Tile directions for pathfinding
static const std::vector<sf::Vector2i> directions = {
    {0, -1}, {0, 1}, {-1, 0}, {1, 0} // Up, Down, Left, Right
};

// Node structure for A* pathfinding (Tile to explore)
struct Node {
    sf::Vector2i pos;
    float cost;
    float priority; // Cost + Heuristic

    // Comparison operator for priority queue (min-priority)
    bool operator>(const Node& other) const {
        return priority > other.priority;
    }
};

// Heuristic function for A* pathfinding (estimated cost to reach goal)
inline float heuristic(const sf::Vector2i& a, const sf::Vector2i& b) {
    return static_cast<float>(std::abs(a.x - b.x) + std::abs(a.y - b.y)); // Manhattan distance for grid-based movement in 4 directions
}

inline std::vector<sf::Vector2i> aStarPath(
    const sf::Vector2i& start,
    const sf::Vector2i& goal,
    const std::function<bool(const sf::Vector2i&)>& isWalkable,
    const sf::Vector2i& mapSize
) {

    // If we already reached the goal, return an empty path
    if(start == goal) return {};

    // Initialization of data structures
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> open; // Min-priority queue for A* search
    std::unordered_map<sf::Vector2i, sf::Vector2i> cameFrom; // To reconstruct the path
    std::unordered_map<sf::Vector2i, float> costSoFar; // Cost of the cheapest path to each node

    // Initialize the starting node
    open.push({start, 0.0f, heuristic(start, goal)});
    cameFrom[start] = start;
    costSoFar[start] = 0.0f;

    // Main A* loop
    while (!open.empty()) {

        // Get the node with the lowest priority
        Node current = open.top();
        open.pop();

        // If we reached the goal, use cameFrom to reconstruct the path
        if (current.pos == goal) {
            std::vector<sf::Vector2i> path;
            sf::Vector2i curr = goal;
            while (curr != start) {
                path.push_back(curr);
                curr = cameFrom[curr];
            }
            // Reverse the path to get the correct order
            std::reverse(path.begin(), path.end());
            return path;
        }

        // Explore neighboring tiles for each direction
        for (const auto& dir : directions) {
            sf::Vector2i next = current.pos + dir;

            // Check if the next tile is within bounds and walkable (non solid)
            if (next.x < 0 || next.y < 0 || next.x >= mapSize.x || next.y >= mapSize.y)
                continue;
            if (!isWalkable(next))
                continue;

            float newCost = costSoFar[current.pos] + 1.0f; // The cost of moving to a neighbor is always 1

            // IF the neighbor has not been explored or we found a cheaper path to it, update the data structures
            if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next]) {
                costSoFar[next] = newCost;
                float priority = newCost + heuristic(next, goal);
                open.push({next, newCost, priority}); // Add the neighbor to the open list
                cameFrom[next] = current.pos; // Keep track of the best path to each node
            }
        }
    }

    return {};
}
