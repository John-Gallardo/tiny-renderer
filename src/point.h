/********************************************************************************************
 * Point2D class.
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
