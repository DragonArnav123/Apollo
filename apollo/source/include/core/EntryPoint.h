#pragma once

#include "Core.h"
#include "Application.h"

#if defined(APOLLO_PLATFORM_WINDOWS)
	// TODO	
	// int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdArgs, int cmdLine)
	// {
	// 	// log
	// 	/*
	// 	Copied from github, convert wchar argv to char argv with nullptr terminated argv:
	// 		https://stackoverflow.com/questions/74999026/is-there-the-commandlinetoargva-function-in-windows-c-c-vs-2022
	// 		answered by: Dúthomhas
	// 	*/
	// 	int argc;

	// 	// Get the command line arguments as wchar_t strings
	// 	wchar_t ** wargv = CommandLineToArgvW(GetCommandLineW(), &argc);

	// 	// Count the number of bytes necessary to store the UTF-8 versions of those strings
	// 	int n = 0;

	// 	for (int i = 0;  i < argc;  i++)
	// 		n += WideCharToMultiByte(CP_UTF8, 0, wargv[i], -1, nullptr, 0, nullptr, nullptr) + 1;

	// 	// Allocate the argv[] array + all the UTF-8 strings
	// 	char **argv = (char **) malloc((argc + 1) * sizeof(char *) + n);

	// 	if (!*argv) 
	// 	{ 
	// 		argc = 0; 
	// 	}

	// 	// Convert all wargv[] --> argv[]
	// 	char * arg = (char *)&((*argv)[argc + 1]);
		
	// 	for (int i = 0;  i < argc;  i++)
	// 	{
	// 		(*argv)[i] = *arg;
	// 		arg += WideCharToMultiByte(CP_UTF8, 0, wargv[i], -1, arg, n, nullptr, nullptr) + 1;
	// 	}
	// 	(*argv)[argc] = NULL;

	// 	Apollo::Application *app = Apollo::CreateApplication(argc, (const char **) argv);
	// 	app->OnBegin();
	// 	app->Run();
	// 	app->OnShutDown();

	// 	delete app;
	// 	return (0);
	// }

	int main(int argc, const char *argv[])
	{
		// Initialize Apollo
		Apollo::Initialize();

		Apollo::Application *app = Apollo::CreateApplication(argc, argv);

		app->OnBegin();
		app->Run();
		app->OnShutDown();

		delete app;

		// Terminate Apollo
		Apollo::Terminate();
		
		return (0);
	}

#else

	int main(int argc, const char *argv[])
	{
		Apollo::Application *app = Apollo::CreateApplication(argc, argv);

		app->OnBegin();
		app->Run();
		app->OnShutDown();

		delete app;
		return (0);
	}

#endif