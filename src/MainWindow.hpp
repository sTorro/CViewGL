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
#ifndef _MAIN_WINDOW_HPP_
#define _MAIN_WINDOW_HPP_

#include "CViewGLIncludes.hpp"
#include "Viewport.hpp"

class MainWindow {
  public:
    MainWindow();
    ~MainWindow();

    void show(void);
    bool exitRequested(void);

    static void windowSizeCallback(GLFWwindow* window, int width, int height);
    std::string getModelPath(void) const;

  private:
    GLFWwindow* m_window;
    static Viewport* m_viewport;

    void setUpContext(void);
};

#endif // _MAIN_WINDOW_HPP_