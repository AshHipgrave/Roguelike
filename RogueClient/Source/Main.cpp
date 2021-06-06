#include "Core/RogueClient.h"

#include <Windows.h>

int main(int argc, char* args[])
{
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	RogueClient client;

	if (!client.Init("Game Window", 1920, 1080))
		return 1;

	client.Run();

	return 0;
}
