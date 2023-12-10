#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


const int MAX_DEPTH = 8;

struct Point {
    float x, y, z;

    Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct OctreeNode {
    Point min, max;
    std::vector<Point> points;
    OctreeNode* children[8];

    OctreeNode(const Point& _min, const Point& _max) : min(_min), max(_max) {
        for (int i = 0; i < 8; ++i) {
            children[i] = nullptr;
        }
    }
};

class Octree {
public:
    Octree(const Point& _min, const Point& _max) : root(new OctreeNode(_min, _max)) {}

    void insert(const Point& point) {
        insertRecursive(root, point, 0);
    }

    void searchAll() {
        searchAllRecursive(root);
    }

    

    void exit() {
        // Liberar memoria y otras operaciones de cierre si es necesario
        std::cout << "Exiting the program...\n";
        deleteTree(root);
        std::exit(0);
    }

public:
    OctreeNode* root;

    // ... (métodos privados insertRecursive, createChild, getIndex, searchAllRecursive como antes)

    void deleteTree(OctreeNode* node) {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < 8; ++i) {
            deleteTree(node->children[i]);
        }

        delete node;
    }

    void insertRecursive(OctreeNode* node, const Point& point, int depth) {
        if (depth == MAX_DEPTH) {
            node->points.push_back(point);
            return;
        }

        int index = getIndex(node, point);

        if (node->children[index] == nullptr) {
            createChild(node, index);
        }

        insertRecursive(node->children[index], point, depth + 1);
    }

    void createChild(OctreeNode* node, int index) {
        Point newMin = node->min;
        Point newMax = node->max;

        float midX = (node->min.x + node->max.x) / 2.0f;
        float midY = (node->min.y + node->max.y) / 2.0f;
        float midZ = (node->min.z + node->max.z) / 2.0f;

        if (index & 1) newMin.x = midX;
        else newMax.x = midX;

        if (index & 2) newMin.y = midY;
        else newMax.y = midY;

        if (index & 4) newMin.z = midZ;
        else newMax.z = midZ;

        node->children[index] = new OctreeNode(newMin, newMax);
    }

    int getIndex(OctreeNode* node, const Point& point) {
        int index = 0;
        if (point.x > (node->min.x + node->max.x) / 2.0f) index |= 1;
        if (point.y > (node->min.y + node->max.y) / 2.0f) index |= 2;
        if (point.z > (node->min.z + node->max.z) / 2.0f) index |= 4;
        return index;
    }

    void searchAllRecursive(OctreeNode* node) {
        if (node == nullptr) {
            return;
        }

        for (const auto& point : node->points) {
            std::cout << "Point: (" << point.x << ", " << point.y << ", " << point.z << ")\n";
        }

        for (int i = 0; i < 8; ++i) {
            searchAllRecursive(node->children[i]);
        }
    }

    
};

