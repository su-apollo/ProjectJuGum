
#include "NNApplication.h"
#include "NNAudioSystem.h"

#include "MainMenuScene.h"
#include "PlayScene.h"
#include "ReturnScene.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nShowCmd )
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc( );

	AllocConsole();
	FILE* pStream;
	freopen_s( &pStream, "CONOUT$", "wt", stdout );
#endif


	NNApplication* Application = NNApplication::GetInstance();

	Application->Init( L"JuGums", 1000, 700, D2D );
	
	NNSceneDirector::GetInstance()->ChangeScene( CMainMenuScene::Create() );

	Application->Run();
	Application->Release();

#ifdef _DEBUG
	FreeConsole();
#endif

	return 0;
}