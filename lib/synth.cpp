//-----------------------------------------------------------------------------
// 
// Author: Zhizheng Wu (wuzhizheng@gmail.com)
// Date: 11-03-2016
//
// To generate waveform given F0, band aperiodicities and spectrum with WORLD vocoder
//
// This is modified based on Msanori Morise's test.cpp. Low-dimensional band aperiodicities are used as suggested by Oliver.
//
// synth FFT_length sampling_rate F0_file spectrogram_file aperiodicity_file output_waveform
//
//-----------------------------------------------------------------------------

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <sys/stat.h> 

#if (defined (__WIN32__) || defined (_WIN32)) && !defined (__MINGW32__)
#include <conio.h>
#include <windows.h>
#pragma comment(lib, "winmm.lib")
#pragma warning(disable : 4996)
#endif
#if (defined (__linux__) || defined(__CYGWIN__) || defined(__APPLE__))
#include <stdint.h>
#include <sys/time.h>
#endif

// For .wav input/output functions.
#include "audioio.h"

// WORLD core functions.
// Note: win.sln uses an option in Additional Include Directories.
// To compile the program, the option "-I $(SolutionDir)..\src" was set.
#include "world/d4c.h"
#include "world/dio.h"
#include "world/matlabfunctions.h"
#include "world/cheaptrick.h"
#include "world/stonemask.h"
#include "world/synthesis.h"

#include "world/common.h"
#include "world/constantnumbers.h"

// Frame shift [msec]
# define FRAMEPERIOD 5.0

#if (defined (__linux__) || defined(__CYGWIN__) || defined(__APPLE__))
// Linux porting section: implement timeGetTime() by gettimeofday(),
#ifndef DWORD
#define DWORD uint32_t
#endif
DWORD timeGetTime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  DWORD ret = static_cast<DWORD>(tv.tv_usec / 1000 + tv.tv_sec * 1000);
  return ret;
}
#endif

//-----------------------------------------------------------------------------
// struct for WORLD
// This struct is an option.
// Users are NOT forced to use this struct.
//-----------------------------------------------------------------------------
typedef struct {
  double frame_period;
  int fs;

  double *f0;
  double *time_axis;
  int f0_length;

  double **spectrogram;
  double **aperiodicity;
  int fft_size;
} WorldParameters;

//-----------------------------------------------------------------------------
// Test program.
// test.exe input.wav outout.wav f0 spec flag
// input.wav  : argv[1] Input file
// output.wav : argv[2] Output file
// f0         : argv[3] F0 scaling (a positive number)
// spec       : argv[4] Formant shift (a positive number)
//-----------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  if (argc != 7) {
    printf("command: synth FFT_length sampling_rate F0_file spectrogram_file aperiodicity_file output_waveform\n");
    return -2;
  }

  int fft_size = atoi(argv[1]);
  int fs = atoi(argv[2]);


  // compute n bands from fs as in d4c.cpp:325   
  int number_of_aperiodicities = static_cast<int>(MyMinDouble(world::kUpperLimit, fs / 2.0 -
      world::kFrequencyInterval) / world::kFrequencyInterval);

  WorldParameters world_parameters = { 0 };
  // You must set fs and frame_period before analysis/synthesis.
  world_parameters.fs = fs;

  // 5.0 ms is the default value.
  // Generally, the inverse of the lowest F0 of speech is the best.
  // However, the more elapsed time is required.
  world_parameters.frame_period = 5.0;
  world_parameters.fft_size = fft_size;


  // find number of frames (doubles) in f0 file:  
  struct stat st;
  if (stat(argv[3], &st) == -1) {
    printf("cannot read f0\n");
    return -2;
    }
}
