#include <cmath>
#include <iostream>
#include "tgaimage.h"
#include "point.h"
#include "model.h"

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};

/**
 * @brief Draws a line between point a & b.
 *
 * Given 2 points a & b, this function draws a line to the frame buffer with the given color
 * using a modified version of Bresenham's line drawing algorithm. In specific, instead of
 * sampling 't' between 0-1 some number of times, we iterate how wide or how tall the line is
 * depending on which is bigger.
 *
 * @param ax The 'x' value of point a.
 * @param ay The 'y' value of point a.
 * @param bx The 'x' value of point b.
 * @param by The 'y' value of point b.
 * @param framebuffer The framebuffer we write to.
 * @param color The color we set the line.
 */
void line(int ax, int ay, int bx, int by, TGAImage &framebuffer, TGAColor color) {
    // If line is steeper than it is wide, iterate by how tall rather than how wide a line should be.
    // Achieved by swapping ax & ay, & bx & by.
    int width = std::abs(ax - bx), height = std::abs(ay - by);
    bool steep = width < height;
    if (steep) {
        std::swap(ax, ay);
        std::swap(bx, by);
    }

    // Edge Case: ax > bx, resulting in negative 't' thus an impossible 'y' value
    // Fix by swapping a & b
    if (ax > bx) {
        std::swap(ax, bx);
        std::swap(ay, by);
    }

    // Iterate through # of horizontal pixels & sampling accordingly
    for (int x=ax; x<=bx; x++) {
        float t = (x-ax) / static_cast<float>(bx-ax);
        int y = std::round((ay + (by-ay)*t));
        if (steep) {
            framebuffer.set(y, x, color);
        } else {
            framebuffer.set(x, y, color);
        }
    }
}

/**
 * @brief Projects a 3D point (x, y, z) to 2D (x, y)
 *
 * This function turns a 3D coords to 2D coords using the formula
 * x' = x/z
 * y' = y/z
 *
 * @param point The 3D point we transform into 2D.
 */
Point2D project(Point3D point) {
    int x = point.getX(), y = point.getY(), z = point.getZ();
    return Point2D(x / z, y / z);
}

/**
 * Main function.
 */
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Error: Need to provide an object\n";
        exit(-1);
    }

    // 1440p image
    constexpr int width  = 2560;
    constexpr int height = 1440;
    TGAImage framebuffer(width, height, TGAImage::RGB);
    
    // TODO: Read the file path into a 'model' object & iterate through every triangle from every face!
    Model model = Model(argv[1]);

    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}

