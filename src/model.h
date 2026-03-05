/**
 * This header file defines the model class, which stores the given .obj files
 * vertices & faces
 */

#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "vertex.h"
#include "face.h"
#include "facevertex.h"

/**
 * @brief The model class stores all vertex & face data of a given .obj file.
 */
class Model {
    public:
        Model(char *filePath)
            : m_file { filePath }
        {
            // Check if file was successfully read
            if (!m_file) {
                std::cerr << "Error: Could not read file";
                exit(-1);
            }

            // Read file line by line
            std::string line{};
            while (std::getline(m_file, line)) {
                // Read data type (i.e is it v, f)
                std::stringstream ss {line};
                std::string word{};
                ss >> word;

                // Case 1: data type 'v' for vertex
                if (word == "v") {
                    // Read x, y, z
                    std::vector<float> pos{};
                    for (int i = 0; i < 3; i++) {
                        ss >> word;
                        pos.push_back(std::stof(word));
                    }
                    
                    // Create vertex & append to vertices
                    Vertex vertex = Vertex(pos[0], pos[1], pos[2]);
                    m_vertices.push_back(vertex);
                }
                
                // Case 2: data type 'f' for face
                else if (word == "f") {
                    // Read the sets of indices (eg. (v, vt, vn) = (1, 2, 3))
                    std::vector<FaceVertex> faceVertices{};
                    for (int i = 0; i < 3; i++) {
                        ss >> word;
                        std::stringstream indexStream {word};
                        std::vector<int> indices{};
                        std::string buffer;
                        while (std::getline(indexStream, buffer, '/')) {
                            int index = std::stoi(buffer) - 1;  // -1 to convert from obj to C++ indexing
                            indices.push_back(index);
                        }
                        FaceVertex faceVertex = FaceVertex(indices[0], indices[1], indices[2]);
                        faceVertices.push_back(faceVertex);
                    }
                    Face face = Face(faceVertices[0], faceVertices[1], faceVertices[2]);
                    m_faces.push_back(face);
                }
            }
        }

        // Getters
        std::vector<Vertex> getVertices() const {
            return m_vertices;
        }

        std::vector<Face> getFaces() const {
            return m_faces;
        }

    private:
        std::ifstream m_file;
        std::vector<Vertex> m_vertices;
        std::vector<Face> m_faces;
};
