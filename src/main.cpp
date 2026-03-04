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

// Image dimensions
constexpr int width  = 1440;
constexpr int height = 1440;

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
 * @brief Spits orthogonal projection of the vector (x, y, z)
 * 
 * @param vertex The normalized coordinates (x, y, z) that we 
 * @return Point2D (x, y) in the 
 */
Point2D project(Vertex vertex) {
    float x = vertex.getX(), y = vertex.getY();
    // +1 to convert from range [-1, 1] to [0, 2]
    x = x + 1;
    y = y + 1;
    // Multiply x & y by width/2 & height/2 respectively to turn into corresponding pixel coordinates
    // (i.e we want coordinates in range (x, y) = [0-1280, 0-720])
    x *= width/2;
    y *= height/2;
    return Point2D(x, y);
}

/**
 * @brief Reads all vertices & converts them to 2D points.
 *
 * @param The array of vertices we want to convert into 2D points.
 */
std::vector<Point2D> convertTo2D(std::vector<Vertex> &vertices) {
    std::vector<Point2D> points{};
    for (auto vertex : vertices) {
        Point2D point = project(vertex);
        points.push_back(point);
    }
    return points;
}

/**
 * Main function.
 */
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Error: Need to provide an object\n";
        exit(-1);
    }

    TGAImage framebuffer(width, height, TGAImage::RGB);
    
    // Read model & get vertices + faces
    Model model = Model(argv[1]);
    std::vector<Vertex> vertices = model.getVertices();
    std::vector<Face> faces = model.getFaces();
    
    // Convert vertices (x, y, z normalized) to a 2D point
    std::vector<Point2D> points = convertTo2D(vertices);
    
    // Draw every face
    for (Face face : faces) {
        // Grab face vertices
        std::vector<FaceVertex> faceVertices = face.getFaceVertices();
        FaceVertex v1 = faceVertices[0];
        FaceVertex v2 = faceVertices[1];
        FaceVertex v3 = faceVertices[2];

        // Grab indices for vertices
        int indexA = v1.getVertexIndex();
        int indexB = v2.getVertexIndex();
        int indexC = v3.getVertexIndex();

        // Grab points corresponding to indices & draw the triangle
        Point2D a = points[indexA];
        Point2D b = points[indexB];
        Point2D c = points[indexC];

        line(a.getX(), a.getY(), b.getX(), b.getY(), framebuffer, red);
        line(a.getX(), a.getY(), c.getX(), c.getY(), framebuffer, red);
        line(c.getX(), c.getY(), b.getX(), b.getY(), framebuffer, red);
    }

    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}

