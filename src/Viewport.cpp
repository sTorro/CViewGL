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

#include "Viewport.hpp"

Viewport::Viewport(GLFWwindow* window, const std::string& modelPath) {
    glewExperimental = true; // Needed for core profile
    if (glewInit() == GLEW_OK) {
        // OpenGL options
        glEnable(GL_DEPTH_TEST); // z-buffer
        glDepthFunc(GL_LESS); // depth comparison function

        // Visualization
        m_shaderProgram = new ShaderProgram(); // default shaders
        m_camera = new Camera(m_shaderProgram->getProgramID());
        m_input = new Input(window, m_camera);

        // Geometry
        m_model = new Model(modelPath);

        glClearColor(1.0f, 1.0f, 1.0f, .0f);
    }
}

Viewport::~Viewport() {
    if (m_shaderProgram) {
        delete m_shaderProgram;
        m_shaderProgram = nullptr;
    }

    if (m_camera) {
        delete m_camera;
        m_camera = nullptr;
    }

    if (m_input) {
        delete m_input;
        m_input = nullptr;
    }

    if (m_model) {
        delete m_model;
        m_model = nullptr;
    }
}

void Viewport::render(void) { // loop
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m_shaderProgram->getProgramID());

    // Translate it down a bit so it's at the center of the scene
    //glm::mat4 model;
    //m_camera->m_model = glm::translate(model, glm::vec3(0.0f, -5.75f, -80.0f));
    //m_camera->m_model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

    m_model->draw(m_shaderProgram->getProgramID());
    m_camera->update(); // recompute MVP matrix
}

void Viewport::resize(const GLsizei& width, const GLsizei& height) {
    m_camera->calculateAspectRation(width, height);
    glViewport(0, 0, width, height); // reset the viewport
}
