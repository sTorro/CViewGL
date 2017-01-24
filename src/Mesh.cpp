/*
* This file is part of CViewGL project.
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 3 of the License, or (at your
* option) any later version. This program is distributed in the hope that
* it will be useful, but WITHOUT ANY WARRANTY; without even the implied
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with the project. If not, see <http://www.gnu.org/licenses/>.
*
* Copyright ® 2017 Sergio Torró.
*/

#include "Mesh.hpp"

#include <string>
#include <sstream>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->setUp();
}

Mesh::~Mesh() {

}

void Mesh::draw(const GLuint& shaderId) {
    // Bind appropriate textures
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;

    for (GLuint i = 0; i < this->textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding

        // Retrieve texture number (the N in diffuse_textureN)
        std::stringstream ss;
        std::string number;
        std::string name = this->textures[i].type;

        if (name == "texture_diffuse")
            ss << diffuseNr++; // Transfer GLuint to stream
        else if (name == "texture_specular")
            ss << specularNr++; // Transfer GLuint to stream
        number = ss.str();

        // Now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shaderId, (name + number).c_str()), i);

        // And finally bind the texture
        glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
    }

    // Also set each mesh's shininess property to a default value
    // (if you want you could extend this to another mesh property and possibly change this value)
    glUniform1f(glGetUniformLocation(shaderId, "material.shininess"), 16.0f);

    // Draw mesh
    glBindVertexArray(this->m_vao);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Always good practice to set everything back to defaults once configured.
    for (GLuint i = 0; i < this->textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Mesh::setUp(void) {
    // Create buffers/arrays
    glGenVertexArrays(1, &this->m_vao);
    glGenBuffers(1, &this->m_vbo);
    glGenBuffers(1, &this->m_ebo);

    glBindVertexArray(this->m_vao);

    // Load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);

    // A great thing about structs is that their memory layout is sequential for all its items.
    // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
    // again translates to 3/2 floats which translates to a byte array.
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) 0);

    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, normal));

    // Vertex Texture Coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, texture));

    glBindVertexArray(0);
}
