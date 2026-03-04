/**
 * Contains the vertices of a face.
 * i.e the vertex index (v), vertex texture index (vt), and vertex normal index (vn).
 */

#pragma once

class FaceVertex {
    public:
        FaceVertex(int v, int vt, int vn) 
            : m_v { v }, m_vt { vt }, m_vn { vn }
        {}
        
        // Getters
        int getVertexIndex() {
            return m_v;
        }

        int getTextureIndex() {
            return m_vt;
        }

        int getNormalIndex() {
            return m_vn;
        }
    private: 
        int m_v, m_vt, m_vn;
};
