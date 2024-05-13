#include "../../apollo/source/include/core/Application.h"
#include "../../apollo/source/include/core/Engine.h"
#include "../../apollo/source/include/core/Log.h"
#include "include/Worlds.h"

#include <string>

void static PrintWorldNames()
{
	std::string worldNames =
		"DefWorld: It is the default world\n";

	AP_CLIENT_INFO("World names: {}", worldNames);
}

Apollo::Application *Apollo::CreateApplication(APi32 argc, APccstr argv[])
{
	if (argc < 2)
	{
		AP_CLIENT_CRITICAL("Invalid Command Line Args: [Exe] [WorldName]");
		AP_CLIENT_INFO("To find world name, use: [Exe] --print-world-names");
		Apollo::ForceExit(-1);
	}

	if (std::string(argv[1]) == "DefWorld")
	{
		Apollo::Application *sandbox = static_cast<Apollo::Application*>(RunDefaultWorld({ "Test Apollo::Engine", "", { argc, argv } }));
		return sandbox;
	}
	else if (std::string(argv[1]) == "--print-world-names")
	{
		PrintWorldNames();
	}
	else 
	{
		AP_CLIENT_CRITICAL("Given World name does not exist!");
		Apollo::ForceExit(-2);
	}


	return nullptr;
}