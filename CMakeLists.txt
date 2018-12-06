cmake_minimum_required(VERSION 3.12)

add_library(HTS_Engine_World SHARED
        lib/audioio.cpp
        lib/cheaptrick.cpp
        lib/matlabfunctions.cpp
        lib/stonemask.cpp
        lib/HTS_audio.c
        lib/HTS_engine.c
        lib/HTS_gstream.c
        lib/HTS_hidden.h
        lib/HTS_label.c
        lib/HTS_misc.c
        lib/HTS_model.c
        lib/HTS_pstream.c
        lib/HTS_sstream.c
        lib/HTS_vocoder.c
        lib/synth.cpp
        lib/synthesis.cpp
        lib/synthesisrealtime.cpp
        lib/synthworld.cpp
        lib/d4c.cpp
        lib/dio.cpp
        lib/fft.cpp
        lib/SPTKfunctions.c
        lib/common.cpp
        )

include_directories(include include/world)

add_executable(Hts_Englne bin/hts_engine.c)
target_link_libraries(Hts_Englne HTS_Engine_World)
