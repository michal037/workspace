cmake_minimum_required(VERSION 3.7)
project(gui_engine)
set(CMAKE_C_STANDARD 11)

##### Main program #####
set(SOURCES_GUI_ENGINE
        # Global
        source/main.c
        source/types.h
        source/macros.h
        source/detect_os.h
        source/about.h

        # System
        source/system/engine.c
        source/system/engine.h
        source/system/common.c
        source/system/common.h
        source/system/config.c
        source/system/config.h
        source/system/misc.c
        source/system/misc.h
        source/system/onewaylist.c
        source/system/onewaylist.h
        source/system/generic_structures.c
        source/system/generic_structures.h
        source/system/autoit3/autoit3mingw.c
        source/system/autoit3/autoit3.h

        # Graphics
        source/graphics/display.c
        source/graphics/display.h
        source/graphics/gui/gui.c
        source/graphics/gui/gui.h
        source/graphics/gui/gui_elements.h
        source/graphics/gui/gui_elements.c
        source/graphics/gui/gui_colors.h
        source/graphics/gui/misc.c
        source/graphics/gui/misc.h
        source/graphics/gui/layouts/main/gui_layouts_main.h
        source/graphics/gui/layouts/main/gui_layouts_main.c

        # Network - TODO: Certificate problem
        # source/network/update_checker.c
        # source/network/update_checker.h

        # Files
        source/files/icon.h
        # Optional, for Windows .exe file
        source/files/windows/exe_data.rc
        )

add_executable(gui_engine ${SOURCES_GUI_ENGINE})

target_link_libraries(gui_engine
        # Allegro 5 (Static) + (Windows libraries optional)
        liballegro_acodec-static.a libFLAC.a libogg.a libwsock32.a libdumb.a libvorbisfile.a
        libvorbis.a libogg.a libopusfile.a libopus.a libogg.a liballegro_audio-static.a
        libdsound.a libopenal.a liballegro_color-static.a liballegro_dialog-static.a
        liballegro_image-static.a libpng.a libz.a libjpeg.a liballegro_main-static.a
        liballegro_memfile-static.a liballegro_physfs-static.a libphysfs.a
        liballegro_primitives-static.a liballegro_ttf-static.a libfreetype.a libz.a
        liballegro_font-static.a liballegro-static.a libkernel32.a libuser32.a libgdi32.a
        libcomdlg32.a libole32.a libwinmm.a libpsapi.a libshlwapi.a libdinput8.a libstdc++.a
        libglu32.a libopengl32.a libwinpthread.a libgraphite2.dll.a libharfbuzz.a libbz2.a

        # CURL
        # curl nghttp2 rtmp ssh2 ssl crypto
        # ssl crypto gdi32 wldap32 z ws2_32
)

##### Tools #####
set(TOOLS_BIN2HEADER
        # Global
        tools/bin2header/main.c
        )
add_executable(bin2header ${TOOLS_BIN2HEADER})

##### Tests #####
set(TESTS_01
        tests/01/main.c
        tests/01/exe_data.rc
        )
add_executable(test01 ${TESTS_01})
set(TESTS_02
        tests/02/main.c
        )
add_executable(test02 ${TESTS_02})