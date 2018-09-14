include (CMakeForceCompiler)
SET(CMAKE_SYSTEM_NAME Generic)

# specify the cross compiler
#SET(CMAKE_C_COMPILER i386-elf-gcc)
#SET(CMAKE_CXX_COMPILER i386-elf-g++)

CMAKE_FORCE_C_COMPILER(i686-elf-gcc GNU)
CMAKE_FORCE_CXX_COMPILER(i686-elf-g++ GNU)

# use this if CMAKE complains about '-rdynamic'
SET(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
