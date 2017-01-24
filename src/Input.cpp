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

#include "Input.hpp"
#include <iostream>

bool Input::m_hasToMove = false;

Input::Input(GLFWwindow* window, Camera* camera) :
    m_windowPtr(window),
    m_cameraPtr(camera) {

    assert(m_windowPtr);
    assert(m_cameraPtr);

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set callbacks here
    glfwSetMouseButtonCallback(m_windowPtr, mouseButtonCallback);
    glfwSetCursorPosCallback(m_windowPtr, mouseMoveCallback);
    glfwSetScrollCallback(m_windowPtr, mouseScrollCallback);
    //glfwSetKeyCallback(window, keyCallback);

    // http://gamedev.stackexchange.com/questions/58541/how-can-i-associate-a-key-callback-with-a-wrapper-class-instance
    glfwSetWindowUserPointer(m_windowPtr, m_cameraPtr); // user pointer
}

Input::~Input() {
    //m_windowPtr = nullptr;
}

///////////////////////////////////////////////////////////////////////////////////////////
// Callback implementation
void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            Input::m_hasToMove = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            //glfwSetCursor(window, glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR));
        } else if (action == GLFW_RELEASE) {
            Input::m_hasToMove = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            //glfwSetCursor(window, glfwCreateStandardCursor(GLFW_ARROW_CURSOR));
        }
    }
}

void Input::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    assert(cam);
    float offset = xoffset - yoffset;
    cam->zoom(offset);
}

void Input::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
    if (Input::m_hasToMove) {
        auto cam = static_cast<Camera*>(glfwGetWindowUserPointer(window));
        assert(cam);

        // the middle of the screen in the x direction
        auto midX = CViewGL::CurrentWidth / 2;

        // the middle of the screen in the y direction
        auto midY = CViewGL::CurrentHeight / 2;

        // vector that describes mouseposition - center
        glm::vec3 mouseDir(0, 0, 0);

        // move the mouse back to the middle of the screen
        if (xpos == midX && ypos == midY) return;
        glfwSetCursorPos(window, midX, midY);

        // We have to remember that positive rotation is counter-clockwise, so...
        // Moving the mouse down is a negative rotation about the x axis
        mouseDir.x = (float)(midX - xpos) / MOUSE_SENSITIVITY;
        // Moving the mouse right is a negative rotation about the y axis
        mouseDir.y = (float)(midY - ypos) / MOUSE_SENSITIVITY;

        cam->rotate(mouseDir);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////