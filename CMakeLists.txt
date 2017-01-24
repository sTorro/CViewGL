###############################################
# Main CMake script for CViewGL

cmake_minimum_required(VERSION 3.5)
project(CViewGL)
find_package(OpenGL REQUIRED)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)")
endif()

if (CMAKE_SOURCE_DIR MATCHES " ")
	message("Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif()

if (CMAKE_BINARY_DIR MATCHES " ")
	message("Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause.")
endif()

# Compile external dependencies 
add_subdirectory(extern)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

link_directories(
	${CMAKE_SOURCE_DIR}/extern/SOIL/lib
	$ENV{BOOST_ROOT}/lib
)

include_directories(
	$ENV{BOOST_ROOT}
	extern/glfw-3.2.1/include/GLFW/
	extern/glm-0.9.7.1/
	extern/glew-2.0.0/include/
	extern/assimp-3.0.1270/include/
	extern/SOIL
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_200
	assimp
	SOIL
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# CViewGL binaries
file(GLOB INC src/*.h src/*.hpp)
file(GLOB SRC src/*.cpp)
file(GLOB SHD shaders/*.frag shaders/*.vert)
add_executable(CViewGL ${INC} ${SRC} ${SHD})
target_link_libraries(CViewGL ${ALL_LIBS})
set_target_properties(CViewGL PROPERTIES COMPILE_DEFINITIONS "USE_ASSIMP")

# Xcode and Visual working directories
set_target_properties(CViewGL PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")
create_target_launcher(CViewGL WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/")

# Shaders
SOURCE_GROUP(shaders REGULAR_EXPRESSION "shaders/*")

if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode")
	file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/")
	add_custom_command(
	   TARGET CViewGL POST_BUILD
	   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/CViewGL${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
	)

	file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/shaders")
	
	# Copy shaders to bin
	foreach(ShaderFile ${SHD})
		add_custom_command(
			TARGET CViewGL POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy "${ShaderFile}" "${CMAKE_CURRENT_SOURCE_DIR}/bin/shaders/"
		)
	endforeach()
elseif(${CMAKE_GENERATOR} MATCHES "Xcode")
endif(NOT ${CMAKE_GENERATOR} MATCHES "Xcode")
