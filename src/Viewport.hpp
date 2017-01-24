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
#ifndef _VIEWPORT_HPP_
#define _VIEWPORT_HPP_

#include "ShaderProgram.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "Model.hpp"

class Viewport {
  public:
    Viewport(GLFWwindow* window, const std::string& modelPath);
    ~Viewport();

    void render(void);
    void resize(const GLsizei& width, const GLsizei& height);

  private:
    ShaderProgram* m_shaderProgram;
    Camera* m_camera;
    Input* m_input;
    Model* m_model;
};

#endif // _VIEWPORT_HPP_