#include "Game.h"

int main(int argc, char *args[])
{
	TheGame::Instance()->Initialize();
	TheGame::Instance()->Run();


	//Cleanup
	Audio::Instance()->Shutdown();
	TheShader::Instance()->DetachShaders();
	TheShader::Instance()->DestroyShaders();
	TheShader::Instance()->DestroyProgram();
	TheTexture::Instance()->UnloadFromMemory();
	TheGame::Instance()->ShutDown();
	return 0;
}

