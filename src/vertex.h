/**
 * This header file defines my vertex implementation.
 */

#pragma once

/**
 * A vertex holds normalized coordinates in the 3D plane
 * i.e (x, y, z), which all have a range [-1, 1]
 */
class Vertex {
    public:
        Vertex(float x, float y, float z) 
            : m_x { x }, m_y { y }, m_z { z }
        {}

        // Getters
        float getX() const {
            return m_x;
        }

        float getY() const {
            return m_y;
        }

        float getZ() const {
            return m_z;
        }
    private:
        float m_x, m_y, m_z;
};
