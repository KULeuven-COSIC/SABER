
# Created by Daniel Norte de Moraes <danielcheagle@gmail.com>
# for Saber PQC Project.
# License: Public Domain <Unlicense>

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(saber-reference VERSION 3 DESCRIPTION "SABER is a Module-LWR based KEM submitted to NIST"
 LANGUAGES C)

message("Remember manually change SABER_params.h to choose")
message("between LightSaber Saber and FireSaber.")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(MSVC)
else()
    set(CMAKE_C_FLAGS "-Wall -Wextra -Wmissing-prototypes -Wredundant-decls -fomit-frame-pointer -march=native")
    set(CMAKE_C_FLAGS_DEBUG "-g -O0")
    set(CMAKE_C_FLAGS_RELEASE "-O3")
endif()

set_source_files_properties(rng.c PROPERTIES COMPILE_OPTIONS "-std=c99;-Wno-unused-result") # added NISTFLAGS
set_source_files_properties(rng.h PROPERTIES COMPILE_OPTIONS "-std=c99;-Wno-unused-result") # added NISTFLAGS
set_source_files_properties(test/PQCgenKAT_kem.c PROPERTIES COMPILE_OPTIONS "-std=c99;-Wno-unused-result") # added NISTFLAGS

set(libfiles
  pack_unpack.c poly.c fips202.c verify.c cbd.c SABER_indcpa.c
  kem.c rng.c )

set(libheaders
  SABER_params.h pack_unpack.h poly.h rng.h fips202.h verify.h cbd.h
  SABER_indcpa.h )

set(libheaders_install
  api.h SABER_params.h )

add_library(saber_reference SHARED ${libfiles} ${libheaders})
target_link_libraries(saber_reference crypto)

set_target_properties(saber_reference PROPERTIES VERSION ${CMAKE_PROJECT_VERSION})
set_target_properties(saber_reference PROPERTIES SOVERSION 1)

add_executable(test_kex test/test_kex.c ${libheaders})
target_link_libraries(test_kex saber_reference)

add_executable(kem ${libheaders} test/kem.c)
target_link_libraries(kem saber_reference)

add_executable(PQCgenKAT_kem ${libheaders} test/PQCgenKAT_kem.c)
target_link_libraries(PQCgenKAT_kem saber_reference)


install (FILES ${libheaders_install} DESTINATION include/saber_pqc/reference)
install(TARGETS saber_reference
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
