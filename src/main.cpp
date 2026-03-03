#include <cmath>
#include "tgaimage.h"

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

int main(int argc, char** argv) {
    constexpr int width  = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    int ax =  7, ay =  3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    framebuffer.set(ax, ay, white);
    framebuffer.set(bx, by, white);
    framebuffer.set(cx, cy, white);
    
    // Write a line from a to b
    line(ax, ay, bx, by, framebuffer, red);
    // Write a line from a to c
    line(ax, ay, cx, cy, framebuffer, green);
    // Write a line from b to c
    line(cx, cy, bx, by, framebuffer, blue);

    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}

