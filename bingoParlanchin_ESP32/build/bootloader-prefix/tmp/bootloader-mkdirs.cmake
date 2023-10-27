# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/luciano/programas/ESP32/esp-idf/components/bootloader/subproject"
  "/home/luciano/eclipse-workspaces/ws_prueba/Bingo_ESP32/bingoParlanchin_ESP32/build/bootloader"
  "/home/luciano/eclipse-workspaces/ws_prueba/Bingo_ESP32/bingoParlanchin_ESP32/build/bootloader-prefix"
  "/home/luciano/eclipse-workspaces/ws_prueba/Bingo_ESP32/bingoParlanchin_ESP32/build/bootloader-prefix/tmp"
  "/home/luciano/eclipse-workspaces/ws_prueba/Bingo_ESP32/bingoParlanchin_ESP32/build/bootloader-prefix/src/bootloader-stamp"
  "/home/luciano/eclipse-workspaces/ws_prueba/Bingo_ESP32/bingoParlanchin_ESP32/build/bootloader-prefix/src"
  "/home/luciano/eclipse-workspaces/ws_prueba/Bingo_ESP32/bingoParlanchin_ESP32/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/luciano/eclipse-workspaces/ws_prueba/Bingo_ESP32/bingoParlanchin_ESP32/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/luciano/eclipse-workspaces/ws_prueba/Bingo_ESP32/bingoParlanchin_ESP32/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
