#include "RogueClient.h"

int main(int argc, char* args[])
{
	RogueClient client;

	if (!client.Init("Game Window", 1920, 1080))
		return 1;

	client.Run();

	return 0;
}
