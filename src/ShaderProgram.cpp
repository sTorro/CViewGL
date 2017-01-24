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

#include "ShaderProgram.hpp"
#include "CViewGLIncludes.hpp"

#include <vector>
#include <fstream>

ShaderProgram::ShaderProgram() {
    std::string vertexFullPath(DEF_VERTEX_SHADER_NAME);
    std::string fragmentFullPath(DEF_FRAGMENT_SHADER_NAME);
#if defined(_WIN32)
    char buffer[_MAX_PATH];
    GetModuleFileName(nullptr, buffer, _MAX_PATH);
    std::string exePath(buffer); // 9 = CViewGL.exe
    exePath = exePath.substr(0, exePath.find_last_of("\\") + 1); // +1 to keep the last slash
    vertexFullPath = exePath + vertexFullPath;
    fragmentFullPath = exePath + fragmentFullPath;
#endif
    compile(vertexFullPath, fragmentFullPath);
}

ShaderProgram::ShaderProgram(const std::string& vertPath, const std::string& fragPath) {
    compile(vertPath, fragPath);
}

ShaderProgram::~ShaderProgram() {
    glDetachShader(m_programID, m_vertexShaderID);
    glDetachShader(m_programID, fragmentShaderID);
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

////////////////////////////////////////////////////////////////////////////////////
// PUBLIC
void ShaderProgram::compile(const std::string& vertPath, const std::string& fragPath) {
    GLint vertResult = GL_FALSE;
    GLint fragResult = GL_FALSE;

    // Vertex shader
    std::string vertexCode = processShaderCode(vertPath);
    if (vertexCode.empty())
        std::cerr << "ERROR! Vertex shader code is empty..." << std::endl;
    else
        vertResult = compileShader(vertexCode, m_vertexShaderID, GL_VERTEX_SHADER);

    // Fragment shader
    std::string fragmentCode = processShaderCode(fragPath);
    if (fragmentCode.empty())
        std::cerr << "ERROR! Fragment shader code is empty..." << std::endl;
    else
        fragResult = compileShader(fragmentCode, fragmentShaderID, GL_FRAGMENT_SHADER);

    if (vertResult == GL_TRUE && fragResult == GL_TRUE) {
        if (!link())
            std::cerr << "Program link fails :(" << std::endl;
        else std::cout << "Shader program OK." << std::endl;
    } else
        std::cerr << "Skip linking program, some shader fails. vertResult=" << vertResult <<
                  " fragResult=" << fragResult << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// PRIVATE
std::string ShaderProgram::processShaderCode(const std::string& path) const {
    std::string shaderCode = "";
    std::ifstream stream(path, std::ios::in);

    if (stream.is_open()) {
        std::string line;
        while (getline(stream, line))
            shaderCode += "\n" + line;
        stream.close();
    } else
        std::cerr << "Error opening the following path: " << path << " !" << std::endl;

    return shaderCode;
}

GLint ShaderProgram::compileShader(const std::string& shaderCode, GLuint& shaderId, const GLenum type) const {
    GLint result = GL_FALSE;
    shaderId = glCreateShader(type);

    char const* shaderCodePtr = shaderCode.c_str();
    glShaderSource(shaderId, 1, &shaderCodePtr, NULL);
    glCompileShader(shaderId);

    // Check shader
    int infoLogLength;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0) {
        std::vector<char> shaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(shaderId, infoLogLength, NULL, &shaderErrorMessage[0]);
        printf("%s\n", &shaderErrorMessage[0]);
    }

    return result;
}

GLint ShaderProgram::link(void) {
    m_programID = glCreateProgram();

    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, fragmentShaderID);
    glLinkProgram(m_programID);

    // Check the program
    int infoLogLength;
    GLint result = GL_FALSE;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
    glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0) {
        std::vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(m_programID, infoLogLength, NULL, &programErrorMessage[0]);
        printf("%s\n", &programErrorMessage[0]);
    }

    return result;
}
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// GETTERS
GLuint ShaderProgram::getVertexID(void) const {
    return m_vertexShaderID;
}

GLuint ShaderProgram::getFragmentID(void) const {
    return fragmentShaderID;
}

GLuint ShaderProgram::getProgramID(void) const {
    return m_programID;
}
////////////////////////////////////////////////////////////////////////////////////
