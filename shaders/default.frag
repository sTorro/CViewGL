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
* Copyright � 2017 Sergio Torr�.
*/

#version 430 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D texture_diffuse1;

void main()
{    
    color = texture(texture_diffuse1, TexCoords);
}