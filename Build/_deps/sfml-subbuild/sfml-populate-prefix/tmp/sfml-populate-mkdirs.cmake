# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "D:/Uni Work/Angry Birds/angry-birds-clone-assignment-SubhamVala/Build/_deps/sfml-src")
  file(MAKE_DIRECTORY "D:/Uni Work/Angry Birds/angry-birds-clone-assignment-SubhamVala/Build/_deps/sfml-src")
endif()
file(MAKE_DIRECTORY
  "D:/Uni Work/Angry Birds/angry-birds-clone-assignment-SubhamVala/Build/_deps/sfml-build"
  "D:/Uni Work/Angry Birds/angry-birds-clone-assignment-SubhamVala/Build/_deps/sfml-subbuild/sfml-populate-prefix"
  "D:/Uni Work/Angry Birds/angry-birds-clone-assignment-SubhamVala/Build/_deps/sfml-subbuild/sfml-populate-prefix/tmp"
  "D:/Uni Work/Angry Birds/angry-birds-clone-assignment-SubhamVala/Build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp"
  "D:/Uni Work/Angry Birds/angry-birds-clone-assignment-SubhamVala/Build/_deps/sfml-subbuild/sfml-populate-prefix/src"
  "D:/Uni Work/Angry Birds/angry-birds-clone-assignment-SubhamVala/Build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Uni Work/Angry Birds/angry-birds-clone-assignment-SubhamVala/Build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Uni Work/Angry Birds/angry-birds-clone-assignment-SubhamVala/Build/_deps/sfml-subbuild/sfml-populate-prefix/src/sfml-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
