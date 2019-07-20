#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=i686-w64-mingw32-gcc
CCC=i686-w64-mingw32-g++
CXX=i686-w64-mingw32-g++
FC=gfortran
AS=i686-w64-mingw32-ar

# Macros
CND_PLATFORM=Mingw32-Linux
CND_DLIB_EXT=so
CND_CONF=Windows_i686
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Events/Control.o \
	${OBJECTDIR}/Events/Engine.o \
	${OBJECTDIR}/Events/JoyControl.o \
	${OBJECTDIR}/Events/KeyControl.o \
	${OBJECTDIR}/Frames/Engine.o \
	${OBJECTDIR}/Graphics/Animation.o \
	${OBJECTDIR}/Graphics/Animator.o \
	${OBJECTDIR}/Graphics/BasicText.o \
	${OBJECTDIR}/Graphics/Engine.o \
	${OBJECTDIR}/Graphics/Image.o \
	${OBJECTDIR}/Graphics/Surface.o \
	${OBJECTDIR}/Sound/Engine.o \
	${OBJECTDIR}/Structs.o \
	${OBJECTDIR}/Transformable.o \
	${OBJECTDIR}/newmain.o \
	${OBJECTDIR}/test/TestRectangle.o \
	${OBJECTDIR}/test/TestText.o


# C Compiler Flags
CFLAGS=-m32

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../../WinLibraries/SDL2-2.0.9/i686-w64-mingw32/lib -L../../WinLibraries/gcc/i686-w64-mingw32/5.3-win32 -lmingw32 -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_net -lSDL2_mixer -lSDL2main -mwindows -lSDL2.dll -static-libstdc++ -static-libgcc

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sdl_globaltest.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sdl_globaltest.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sdl_globaltest.exe ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Events/Control.o: Events/Control.cpp
	${MKDIR} -p ${OBJECTDIR}/Events
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Events/Control.o Events/Control.cpp

${OBJECTDIR}/Events/Engine.o: Events/Engine.cpp
	${MKDIR} -p ${OBJECTDIR}/Events
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Events/Engine.o Events/Engine.cpp

${OBJECTDIR}/Events/JoyControl.o: Events/JoyControl.cpp
	${MKDIR} -p ${OBJECTDIR}/Events
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Events/JoyControl.o Events/JoyControl.cpp

${OBJECTDIR}/Events/KeyControl.o: Events/KeyControl.cpp
	${MKDIR} -p ${OBJECTDIR}/Events
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Events/KeyControl.o Events/KeyControl.cpp

${OBJECTDIR}/Frames/Engine.o: Frames/Engine.cpp
	${MKDIR} -p ${OBJECTDIR}/Frames
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Frames/Engine.o Frames/Engine.cpp

${OBJECTDIR}/Graphics/Animation.o: Graphics/Animation.cpp
	${MKDIR} -p ${OBJECTDIR}/Graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/Animation.o Graphics/Animation.cpp

${OBJECTDIR}/Graphics/Animator.o: Graphics/Animator.cpp
	${MKDIR} -p ${OBJECTDIR}/Graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/Animator.o Graphics/Animator.cpp

${OBJECTDIR}/Graphics/BasicText.o: Graphics/BasicText.cpp
	${MKDIR} -p ${OBJECTDIR}/Graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/BasicText.o Graphics/BasicText.cpp

${OBJECTDIR}/Graphics/Engine.o: Graphics/Engine.cpp
	${MKDIR} -p ${OBJECTDIR}/Graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/Engine.o Graphics/Engine.cpp

${OBJECTDIR}/Graphics/Image.o: Graphics/Image.cpp
	${MKDIR} -p ${OBJECTDIR}/Graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/Image.o Graphics/Image.cpp

${OBJECTDIR}/Graphics/Surface.o: Graphics/Surface.cpp
	${MKDIR} -p ${OBJECTDIR}/Graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Graphics/Surface.o Graphics/Surface.cpp

${OBJECTDIR}/Sound/Engine.o: Sound/Engine.cpp
	${MKDIR} -p ${OBJECTDIR}/Sound
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Sound/Engine.o Sound/Engine.cpp

${OBJECTDIR}/Structs.o: Structs.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Structs.o Structs.cpp

${OBJECTDIR}/Transformable.o: Transformable.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Transformable.o Transformable.cpp

${OBJECTDIR}/newmain.o: newmain.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/newmain.o newmain.cpp

${OBJECTDIR}/test/TestRectangle.o: test/TestRectangle.cpp
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/TestRectangle.o test/TestRectangle.cpp

${OBJECTDIR}/test/TestText.o: test/TestText.cpp
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -DWINDOWS -I../../WinLibraries/gcc/i686-w64-mingw32 -I../../WinLibraries/SDL2-2.0.9/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/TestText.o test/TestText.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
