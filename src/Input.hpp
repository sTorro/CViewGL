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
#ifndef _INPUT_HPP_
#define _INPUT_HPP_

#include "CViewGLIncludes.hpp"
#include "Camera.hpp"

#define MOUSE_SENSITIVITY 1500

class Input {
  public:
    Input(GLFWwindow* window, Camera* camera);
    ~Input();

    // GFLW is written in plain C, all callbacks must be static to follow the C calling semantics
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
    static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

  private:
    Camera* m_cameraPtr;
    GLFWwindow* m_windowPtr;
    static bool m_hasToMove;
};

#endif // !_INPUT_HPP_

