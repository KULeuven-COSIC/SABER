
# Created by Daniel Norte de Moraes <danielcheagle@gmail.com>
# for Saber PQC Project.
# License: Public Domain <Unlicense>

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(saber-avx VERSION 3 DESCRIPTION "SABER is a Module-LWR based KEM submitted to NIST"
 LANGUAGES C)

message("Remember manually change api.h to choose")
message("between LightSaber Saber and FireSaber.")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(MSVC)
else()
    set(CMAKE_C_FLAGS "-Wall -Wextra -fomit-frame-pointer -msse2avx -mavx2 -march=native -fno-common")
    set(CMAKE_C_FLAGS_DEBUG "-g -O0")
    set(CMAKE_C_FLAGS_RELEASE "-O3")
endif()

set_source_files_properties(rng.c PROPERTIES COMPILE_OPTIONS "-std=c11;-Wno-unused-result")
set_source_files_properties(rng.h PROPERTIES COMPILE_OPTIONS "-std=c11;-Wno-unused-result")

set(libfiles
  pack_unpack.c fips202.c verify.c cbd.c SABER_indcpa.c
  kem.c rng.c )

set(libheaders
  SABER_params.h pack_unpack.h verify.h cbd.h SABER_indcpa.h kem.h rng.h fips202.h api.h )

add_library(saber_avx SHARED ${libfiles} ${libheaders})
target_link_libraries(saber_avx crypto)

set_target_properties(saber_avx PROPERTIES VERSION ${CMAKE_PROJECT_VERSION})
set_target_properties(saber_avx PROPERTIES SOVERSION 1)

add_executable(test_kex test/test_kex.c ${libheaders})
target_link_libraries(test_kex saber_avx)

add_executable(sample_matrix_test ${libheaders} test/sample_matrix_test.c)
target_link_libraries(sample_matrix_test saber_avx)

add_executable(PQCgenKAT_kem ${libheaders} test/PQCgenKAT_kem.c)
target_link_libraries(PQCgenKAT_kem saber_avx)


install (FILES ${libheaders} DESTINATION include/saber_pqc/avx)
install(TARGETS saber_avx
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
