/**
 * Vertex implementation.
 * In practice, this is only used with normalized 3D points (x, y, z all with range [-1, 1])
 */

class Vertex {
    public:
        Vertex(float x, float y, float z) 
            : m_x { x }, m_y { y }, m_z { z }
        {}

        // Getters
        float getX() {
            return m_x;
        }

        float getY() {
            return m_y;
        }

        float getZ() {
            return m_z;
        }
    private:
        float m_x, m_y, m_z;
};
