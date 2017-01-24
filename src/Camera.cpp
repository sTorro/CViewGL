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

#include "Camera.hpp"
#include "MainWindow.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LINKS:
// https://github.com/tomdalling/opengl-series/blob/master/source/04_camera/source/tdogl/Camera.h
// https://github.com/tomdalling/opengl-series/blob/master/source/04_camera/source/tdogl/Camera.cpp
// http://www.gamedev.net/page/resources/_/technical/math-and-physics/a-simple-quaternion-based-camera-r1997
// https://en.wikipedia.org/wiki/Unit_circle
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Camera::Camera(const GLuint& shaderProgram) :
    m_shaderProgramId(shaderProgram),
    m_position(0.0f, 0.0f, -6.0f),
    m_target(0, 0, 0),
    m_up(0, 1, 0),
    m_fieldOfView(45.0f),
    m_nearPlane(0.1f),
    m_farPlane(100.0f),
    m_viewportAspectRatio((float) CViewGL::CurrentWidth / CViewGL::CurrentHeight) {
    m_matrixId = glGetUniformLocation(m_shaderProgramId, "MVP");
}

Camera::~Camera() {
    //
}

void Camera::update(void) {
    glm::mat4 mvp = matrix();
    glUniformMatrix4fv(m_matrixId, 1, GL_FALSE, &mvp[0][0]);
}

void Camera::zoom(const float& angle) {
    m_fieldOfView += glm::radians(angle);
}

glm::mat4 Camera::projection() const {
    return glm::perspective(m_fieldOfView, m_viewportAspectRatio, m_nearPlane, m_farPlane);
}

glm::mat4 Camera::view() const {
    return glm::lookAt(m_position, m_target, m_up);
}

glm::mat4 Camera::matrix() const {
    // Model View Projection matrix
    return projection() * view() * m_model; //glm::mat4(1.0f);
}

void Camera::rotate(const glm::vec3& mouseDir) {
    // Get the axis to rotate around the x-axis.
    glm::vec3 axis = glm::cross(m_target - m_position, m_up);

    // To be able to use the quaternion conjugate, the axis to
    // rotate around must be normalized.
    axis = glm::normalize(axis);

    // Rotate around the y axis
    rotateCamera(mouseDir.y, axis);

    // Rotate around the x axis
    rotateCamera(mouseDir.x, glm::vec3(0, 1, 0));
}

void Camera::rotateCamera(const float& angle, const glm::vec3& axis) {
    glm::quat temp;
    temp.x = axis.x * glm::sin(angle / 2.0F);
    temp.y = axis.y * glm::sin(angle / 2.0F);
    temp.z = axis.z * glm::sin(angle / 2.0F);
    temp.w = glm::cos(angle / 2.0F);

    glm::quat quatView;
    quatView.x = m_position.x;
    quatView.y = m_position.y;
    quatView.z = m_position.z;
    quatView.w = 0;

    auto result = temp * quatView * glm::conjugate(temp);
    m_position.x = result.x;
    m_position.y = result.y;
    m_position.z = result.z;
}

void Camera::calculateAspectRation(const GLsizei& width, const GLsizei& height) {
    this->m_viewportAspectRatio = (float) width / height;
}
