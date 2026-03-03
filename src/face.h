/**
 * @brief A face simply contains 3 triangles.
 */

#pragma once
#include <vector>
#include "triangle.h"

class Face {
    public:
        // Constructor
        Face(Triangle t1, Triangle t2, Triangle t3)
            : m_triangles {t1, t2, t3}
        {}

        // Getter
        std::vector<Triangle> getTriangles() {
            return m_triangles;
        }
    private:
        std::vector<Triangle> m_triangles;
};
