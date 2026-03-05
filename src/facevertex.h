/**
 * This header file defines the face vertex.
 */

#pragma once

/**
 * A face vertex simply holds the vertex index (v), the vertex texture index (vt),
 * and the vertex normal index (vn).
 */
class FaceVertex {
    public:
        FaceVertex(int v, int vt, int vn) 
            : m_v { v }, m_vt { vt }, m_vn { vn }
        {}
        
        // Getters
        int getVertexIndex() const {
            return m_v;
        }

        int getTextureIndex() const {
            return m_vt;
        }

        int getNormalIndex() const {
            return m_vn;
        }
    private: 
        int m_v, m_vt, m_vn;
};
