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
* Copyright ® 2016 Sergio Torró.
*/

#pragma once
#ifndef _SHADER_PROGRAM_HPP_
#define _SHADER_PROGRAM_HPP_

#include <string>
#include <GL\glew.h>

class ShaderProgram {
  public:
    ShaderProgram(); // it uses default shaders
    ShaderProgram(const std::string& vertPath, const std::string& fragPath);
    ~ShaderProgram();

    // Getters
    GLuint getVertexID(void) const;
    GLuint getFragmentID(void) const;
    GLuint getProgramID(void) const;

  private:
    GLuint m_programID;
    GLuint m_vertexShaderID;
    GLuint fragmentShaderID;

    void compile(const std::string& vertPath, const std::string& fragPath);
    GLint link(void);

    std::string processShaderCode(const std::string& path) const;
    GLint compileShader(const std::string& shaderCode, GLuint& shaderId, const GLenum type) const;
};

#endif // _SHADER_PROGRAM_HPP_
