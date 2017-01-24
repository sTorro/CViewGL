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

#include "MainWindow.hpp"

Viewport* MainWindow::m_viewport = nullptr;

MainWindow::MainWindow() {
    if (glfwInit()) {
        setUpContext();
        m_window = glfwCreateWindow(CViewGL::CurrentWidth, CViewGL::CurrentHeight, WINDOW_TITLE, nullptr, nullptr);
        if (m_window != nullptr) {
            glfwMakeContextCurrent(m_window);
            glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
            glfwSetWindowSizeCallback(m_window, windowSizeCallback);
            auto modelPath = getModelPath();
            m_viewport = new Viewport(m_window, modelPath);
        }
    } else std::cerr << "Error creating the context at MainWindow." << std::endl;
}

MainWindow::~MainWindow() {
    if (m_viewport) {
        delete m_viewport;
        m_viewport = nullptr;
    }

    glfwTerminate();
}

////////////////////////////////////////////////////////////////////////////////////
// PUBLIC
void MainWindow::show(void) {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
    m_viewport->render();
}

bool MainWindow::exitRequested(void) {
    return glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(m_window) == 0;
}

std::string MainWindow::getModelPath(void) const {
    char buffer[_MAX_PATH];
#if defined(_WIN32) // Windows
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = buffer;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(buffer);
    auto filter = CViewGL::GetSuportedFiles();
    ofn.lpstrFilter = filter.c_str();
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    GetOpenFileName(&ofn);
    std::cout << "Selected file: " << buffer << std::endl;
#endif
    // TODO: other systems
    return std::string(buffer);
}
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// PRIVATE
void MainWindow::setUpContext(void) {
    //glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// Callback implementation
void MainWindow::windowSizeCallback(GLFWwindow* window, int width, int height) {
    CViewGL::CurrentWidth = width;
    CViewGL::CurrentHeight = height;
    m_viewport->resize(width, height);
    std::cout << "Resized to " << CViewGL::CurrentWidth << "x" << CViewGL::CurrentHeight << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////