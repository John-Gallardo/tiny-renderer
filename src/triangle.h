/**
 * @brief A triangle simply contains the 3 indices of a vertex.
 */
#pragma once
#include <vector>

class Triangle {
    public:
        // Constructor
        Triangle(int i, int j, int k)
            : m_indices {i, j, k}
        {}

        // Getters
        std::vector<int> getIndices() {
            return m_indices;
        }
    private:
        std::vector<int> m_indices;
};
