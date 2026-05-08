# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/tima/mentoring/tt_2/build/_deps/math-src"
  "/home/tima/mentoring/tt_2/build/_deps/math-build"
  "/home/tima/mentoring/tt_2/build/_deps/math-subbuild/math-populate-prefix"
  "/home/tima/mentoring/tt_2/build/_deps/math-subbuild/math-populate-prefix/tmp"
  "/home/tima/mentoring/tt_2/build/_deps/math-subbuild/math-populate-prefix/src/math-populate-stamp"
  "/home/tima/mentoring/tt_2/build/_deps/math-subbuild/math-populate-prefix/src"
  "/home/tima/mentoring/tt_2/build/_deps/math-subbuild/math-populate-prefix/src/math-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/tima/mentoring/tt_2/build/_deps/math-subbuild/math-populate-prefix/src/math-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/tima/mentoring/tt_2/build/_deps/math-subbuild/math-populate-prefix/src/math-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
