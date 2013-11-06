
#include "NNApplication.h"
#include "NNAudioSystem.h"

#include "MainMenuScene.h"
#include "PlayScene.h"
#include "ReturnScene.h"

/*#include "PrintLog.h"*/

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nShowCmd )
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc( );

#endif


	NNApplication* Application = NNApplication::GetInstance();

	Application->Init( L"JuGums", 1280, 800, D2D );
	
	NNSceneDirector::GetInstance()->ChangeScene( new CMainMenuScene() );

	Application->Run();
	Application->Release();

	return 0;
}