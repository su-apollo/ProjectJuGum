
#include "NNApplication.h"
#include "NNAudioSystem.h"

#include "SpriteExample.h"
#include "LabelExample.h"
#include "SoundExample.h"
#include "InputExample.h"
#include "CustomObjectExample.h"
#include "TestScene.h"
#include "Playtest.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nShowCmd )
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc( );
#endif

	// for debugging
	AllocConsole();
	FILE* pStream;
	freopen_s( &pStream, "CONOUT$", "wt", stdout );

	NNApplication* Application = NNApplication::GetInstance();

	Application->Init( L"JuGums", 1000, 700, D2D );

	// Sprite Example
	// NNSceneDirector::GetInstance()->ChangeScene( SpriteExample::Create() );

	// Label Example
	// NNSceneDirector::GetInstance()->ChangeScene( LabelExample::Create() );

	// Input Example
	// NNSceneDirector::GetInstance()->ChangeScene( InputExample::Create() );

	// Sound Example
	// NNSceneDirector::GetInstance()->ChangeScene( SoundExample::Create() );

	// CustomObject Example
	 NNSceneDirector::GetInstance()->ChangeScene( CustomObjectExample::Create() );

	// TestMenuScene
	// NNSceneDirector::GetInstance()->ChangeScene( CTestScene::Create() );

	// Playtest
	// NNSceneDirector::GetInstance()->ChangeScene( CPlaytest::Create() );

	Application->Run();
	Application->Release();

	// for debugging
	FreeConsole();

	return 0;
}