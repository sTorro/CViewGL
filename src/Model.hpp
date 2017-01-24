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

#pragma once
#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "CViewGLIncludes.hpp"
#include "Mesh.hpp"

#include <assimp/scene.h>

class Model {
  public:
    Model() = delete;
    Model(const std::string& path);
    ~Model();

    void draw(const GLuint& shaderId);

  private:
    std::vector<Mesh> m_meshes;
    std::string m_directory;
    std::vector<Texture> m_textures; // loaded textures

    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
    GLint textureFromFile(const char* path, const std::string& directory) const;
};

#endif // !_MODEL_HPP_

