
#include "NNApplication.h"
#include "NNAudioSystem.h"

#include "SpriteExample.h"
#include "LabelExample.h"
#include "SoundExample.h"
#include "InputExample.h"
#include "CustomObjectExample.h"
#include "TestScene.h"

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

	Application->Init( L"JuGums", 400, 600, D2D );

	// Sprite Example
	// NNSceneDirector::GetInstance()->ChangeScene( SpriteExample::Create() );

	// Label Example
	// NNSceneDirector::GetInstance()->ChangeScene( LabelExample::Create() );

	// Input Example
	// NNSceneDirector::GetInstance()->ChangeScene( InputExample::Create() );

	// Sound Example
	// NNSceneDirector::GetInstance()->ChangeScene( SoundExample::Create() );

	// CustomObject Example
	// NNSceneDirector::GetInstance()->ChangeScene( CustomObjectExample::Create() );

	// TestScene
	NNSceneDirector::GetInstance()->ChangeScene( CTestScene::Create() );

	Application->Run();
	Application->Release();

	// for debugging
	FreeConsole();

	return 0;
}