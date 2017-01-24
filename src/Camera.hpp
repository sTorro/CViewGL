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
#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "CViewGLIncludes.hpp"

class Camera {
  public:
    Camera(const GLuint& shaderProgram);
    virtual ~Camera();

    // disable default and copy ctors
    Camera() = delete;
    Camera(const Camera&) = delete;

    void zoom(const float& angle);
    void update(void);
    void rotate(const glm::vec3& mouseDir);
    void calculateAspectRation(const GLsizei& w, const GLsizei& h);

    glm::mat4 m_model;

  private:
    GLuint m_shaderProgramId;
    GLuint m_matrixId;

    // camera "look at"
    glm::vec3 m_position; // eye
    glm::vec3 m_target;
    glm::vec3 m_up;

    // projection
    float m_fieldOfView;
    float m_nearPlane;
    float m_farPlane;
    float m_viewportAspectRatio;

    glm::mat4 projection() const;
    glm::mat4 view() const;
    glm::mat4 matrix() const;
    void rotateCamera(const float& angle, const glm::vec3& axis);
};

#endif // !_CAMERA_HPP_
