#include <iostream>

#include "RogueClient.h"

int main(int argc, char* args[])
{
	std::cout << "Hello, world!" << std::endl;

	RogueClient client;

	if (!client.Init("Game Window", 1920, 1080))
		return 1;

	client.LoadResources();

	client.Run();
	client.Exit();

	return 0;
}
