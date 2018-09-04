cmake_minimum_required(VERSION 3.1)
project(indie_studio)

set(CMAKE_CXX_STANDARD 14)

set(NAME bomberman)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Item/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/irrlicht/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/irrklang/include)

if (UNIX)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/irrlicht/lib/Linux)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/irrklang)
endif (UNIX)
if (WIN32)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/irrlicht/lib/Win32-visualStudio/Irrlicht.lib)
	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/irrklang/lib/Win32-visualStudio/irrKlang.lib)
endif(WIN32)

set(
	SRCS
	./Core/StudioCore.cpp
	./Game/Bomberman.cpp
	./Graphical/Graphical.cpp
	./Graphical/GetEvent.cpp
	./Introduction/Intro.cpp
	./Item/BombStandard.cpp
	./Menu/Button.cpp
	./Menu/Menu.cpp
	./Menu/Param.cpp
	./main.cpp
	./Map/Map.cpp
	./Map/Floor.cpp
	./Map/Cube.cpp
	./Collision/Collision.cpp
	./Song/Song.cpp
	./IA/IA.cpp
	./Credits/Credits.cpp
)

add_executable(${NAME} ${SRCS})

if (UNIX)
	target_link_libraries(${NAME} Irrlicht IrrKlang GL Xxf86vm Xext X11 Xcursor pthread)
endif(UNIX)

if (WIN32)
	target_link_libraries(${NAME} ${CMAKE_CURRENT_SOURCE_DIR}/irrlicht/lib/Win32-visualStudio/Irrlicht.lib)
	target_link_libraries(${NAME} ${CMAKE_CURRENT_SOURCE_DIR}/irrklang/lib/Win32-visualStudio/irrKlang.lib)
endif(WIN32)
