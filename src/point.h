/********************************************************************************************
 * This file defines 2 classes: Point2D (x & y coordinates) & Point3D (x, y & z coordinates)
 * Implementation details are below.
 ********************************************************************************************/

#pragma once

/**
 * @brief Point2D represents a point in a 2D space (x, y)
 *
 * This class holds an x & y coordinate.
 * Has getters & setters.
 */
class Point2D {
    public:
        Point2D(int x, int y)
            : m_x { x }, m_y { y }
        {}

        int getX() {
            return m_x;
        }

        int getY() {
            return m_y;
        }

        void setX(int x) {
            m_x = x;
        }

        void setY(int y) {
            m_y = y;
        }
    private:
        int m_x, m_y;
};

/**
 * @brief Point3D represents a point in a 3D space (x, y, z)
 *
 * This class holds an x, y & z coordinate.
 * Has getters & setters.
 */
class Point3D {
    public:
        Point3D(int x, int y, int z)
            : m_x { x }, m_y { y }, m_z { z }
        {}

        int getX() {
            return m_x;
        }

        int getY() {
            return m_y;
        }

        int getZ() {
            return m_z;
        }

        void setX(int x) {
            m_x = x;
        }

        void setY(int y) {
            m_y = y;
        }

        void setZ(int z) {
            m_z = z;
        }
    private:
        int m_x, m_y, m_z;
};
