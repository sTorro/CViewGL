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
* Copyright ® 2017 Sergio Torró.
*/

#pragma once
#ifndef _CVIEWGL_INCLUDES_HPP_
#define _CVIEWGL_INCLUDES_HPP_

#define WINDOW_WIDTH_DEFAULT 1024
#define WINDOW_HEIGHT_DEFAULT 768
#define FULL_SCREEN FALSE
#define WINDOW_TITLE "CViewGL"

#define DEF_VERTEX_SHADER_NAME "shaders\\default.vert"
#define DEF_FRAGMENT_SHADER_NAME "shaders\\default.frag"

#define NUL_STR '\0'

// Graphics and maths
// The including order is IMPORTANT
#include <GL\glew.h>
#include <glfw3.h> // context
#include <glm\glm.hpp> // math
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

// Standard
#include <iostream>
#include <algorithm>
#include <sstream>

// Boost
//#include <boost\algorithm\string.hpp>

#if defined(_WIN32)
#include <Windows.h>
#endif

struct SupportedFile {
    SupportedFile(const std::string& name, const std::string& ext) :
        Name(name), Extension(ext) {}
    std::string Name;
    std::string Extension;
};

namespace CViewGL {
    static GLsizei CurrentWidth = WINDOW_WIDTH_DEFAULT;
    static GLsizei CurrentHeight = WINDOW_HEIGHT_DEFAULT;

    const SupportedFile SuportedFiles[] = {
        SupportedFile("Wavefront Object (.obj)", "obj"),
        SupportedFile("Stereolithography (.stl)", "stl"),
        SupportedFile("Autodesk (.fbx)", "fbx"),
        SupportedFile("Collada (.dae)", "dae"),
        SupportedFile("Blender 3D (.blend)", "blend"),
        SupportedFile("3ds Max 3DS (.3ds)", "3ds"),
        SupportedFile("3ds Max ASE (.ase)", "ase"),
        SupportedFile("Stanford Polygon Library (.ply)", "ply"),
        SupportedFile("AutoCAD DXF (.dxf)", "dxf"),
        SupportedFile("LightWave (.lwo)", "lwo"),
        SupportedFile("LightWave Scene (.lws)", "lws"),
        SupportedFile("Modo (.lxo)", "lxo"),
        SupportedFile("DirectX X (.x)", "x"),
        SupportedFile("AC3D (.ac)", "ac"),
        SupportedFile("Milkshape 3D (.ms3d)", "ms3d")
    };

    static std::string GetSuportedFiles(void) {
        std::stringstream ss;
        for (auto const& file : SuportedFiles)
            ss << file.Name << NUL_STR << "*." << file.Extension << NUL_STR;
        return ss.str();
    }
}

#endif // _CVIEWGL_INCLUDES_HPP_
