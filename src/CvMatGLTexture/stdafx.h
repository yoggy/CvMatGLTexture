#pragma once

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>

#pragma warning(disable:4098)
#include <GL/GL.h>
#include <GL/GLU.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include <SDL.h>
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#ifdef _DEBUG
	#pragma comment(lib, "opencv_core248d.lib")
	#pragma comment(lib, "opencv_imgproc248d.lib")
	#pragma comment(lib, "opencv_highgui248d.lib")
#else
	#pragma comment(lib, "opencv_core248.lib")
	#pragma comment(lib, "opencv_imgproc248.lib")
	#pragma comment(lib, "opencv_highgui248.lib")
#endif