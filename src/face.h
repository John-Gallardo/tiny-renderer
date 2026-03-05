/**
 * This header file defines the data type 'f' of an .obj file.
 */

#pragma once
#include <vector>
#include "facevertex.h"

/**
 * A face simply has 3 face vertices
 */
class Face {
    public:
        Face(FaceVertex v1, FaceVertex v2, FaceVertex v3)
            : m_faceVertices {v1, v2, v3}
        {}

        std::vector<FaceVertex> getFaceVertices() const {
            return m_faceVertices;
        }
    private:
        std::vector<FaceVertex> m_faceVertices;
};
