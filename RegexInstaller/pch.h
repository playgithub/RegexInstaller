// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#pragma execution_character_set("utf-8")

#define _CRT_SECURE_NO_WARNINGS

#include "targetver.h"

// wxWidgets
#define WXUSINGDLL
#include <wx/wx.h>
#include <wx/listctrl.h>

// STL
#include <sstream>
#include <fstream>
#include <regex>
#include <filesystem>

// boost
#define BOOST_ALL_DYN_LINK

// rapidjson
#include <rapidjson/error/error.h>
#include <rapidjson/error/en.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/istreamwrapper.h>

#endif //PCH_H
