/**
 * @brief Defines the model class, which stores its vertices (x, y, z) 
 * and faces (which reminds me of an EBO in OpenGL, except it defines 3 triangles per face)
 */

#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

// Use alias for vertex since implementation would be basically the same
using Vertex = Point3D;

/**
 * @brief The model class stores all vertex & face data of a given object.
 *
 * This class reads a given file path, & and decodes each line into either a
 * vertex, or a face. 
 */
class Model {
    public:
        Model(std::string filePath)
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
                // Read data type
                std::stringstream ss {line};
                std::string word{};
                ss >> word;

                // Case 1: data type 'v' for vertex
                if (word == "v") {
                    // Read x, y, z
                    std::vector<float> pos{};
                    for (int i = 0; i < 3; i++) {
                        ss >> word;
                        pos[i] = std::stof(word);
                    }
                    
                    // Create vertex & append to vertices
                    Vertex vertex = Vertex(pos[0], pos[1], pos[2]);
                    m_vertices.push_back(vertex);
                }
                
                // Case 2: data type 'f' for face
                // TODO: Implement this case
            }
        }

        // Getters
        std::vector<Vertex> getVertices() {
            return m_vertices;
        }

        std::vector<int> getFaces() {
            return m_faces;
        }

    private:
        std::ifstream m_file;
        std::vector<Vertex> m_vertices;
        std::vector<int> m_faces;
        // TODO: Create a 'Face' object with that stores the 9 indices.
        // TODO: Create a 'Triangle' object storing 3 indices each
};
