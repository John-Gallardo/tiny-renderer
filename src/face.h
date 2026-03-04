/**
 * A face simply contains 3 face vertices.
 */

#pragma once
#include <vector>
#include "facevertex.h"

class Face {
    public:
        Face(FaceVertex v1, FaceVertex v2, FaceVertex v3)
            : m_faceVertices {v1, v2, v3}
        {}

        std::vector<FaceVertex> getFaceVertices() {
            return m_faceVertices;
        }
    private:
        std::vector<FaceVertex> m_faceVertices;
};
