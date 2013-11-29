
#pragma once

#include "NNRenderer.h"
#include "NND2DRenderer.h"
#include "NNSceneDirector.h"
#include "NNConfig.h"
#include "NNInputSystem.h"
#include "NNAudioSystem.h"
#include "NNResourceManager.h"
#include "ReturnScene.h"

/* */
/* NNApplication
/* 프레임워크의 핵심 클래스
/* 렌더러와 윈도우 프레임을 생성하고
/* 게임 루프를 도는 역활을 한다.
/* */

class NNApplication
{

public:
	static NNApplication* GetInstance();
	static void ReleaseInstance();

public:
	bool Init( wchar_t* const title, int width, int height, RendererStatus renderStatus, bool fullscreen );
	static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	/* 파라메터에 따라 윈도우 프레임, 렌더러 생성 */
	bool Release();

	bool Run();

public:
	inline NNRenderer* GetRenderer() const { return m_Renderer; }
	inline HWND GetHWND() const { return m_Hwnd; }
	inline HINSTANCE GetHandleInstance() const { return m_hInstance; }
	inline const wchar_t* GetTitle() const { return m_Title; }
	inline int GetScreenWidth() const { return m_ScreenWidth; }
	inline int GetScreenHeight() const { return m_ScreenHeight; }
	inline float GetTopLine()	{ return -GetScreenHeight()*0.5f; }
	inline float GetBotLine()	{ return GetScreenHeight()*0.5f; }
	inline float GetRightLine()	{ return GetScreenWidth()*0.5f; }
	inline float GetLeftLine()	{ return -GetScreenWidth()*0.5f; }
	inline RendererStatus GetRendererStatus() const { return m_RendererStatus; }

	inline float GetFPS() const { return m_Fps; }
	inline float GetElapsedTime() const { return m_ElapsedTime; }
	inline float GetDeltaTime() const { return m_DeltaTime; }

private:
	bool _CreateWindow( wchar_t* title, int width, int height, bool fullscreen );
	bool _CreateRenderer( RendererStatus renderStatus );

private:
	NNRenderer* m_Renderer;
	NNSceneDirector* m_pSceneDirector;

private:
	HWND			m_Hwnd;
	HINSTANCE		m_hInstance;
	RendererStatus	m_RendererStatus;

private:
	wchar_t*		m_Title;
	int				m_ScreenWidth;
	int				m_ScreenHeight;

private:
	float			m_Fps;
	float			m_FpsTimer;
	float			m_ElapsedTime;
	float			m_PrevElapsedTime;
	float			m_DeltaTimeSum;
	float			m_DeltaTimeSum1;
	int				m_FrameCount;
	int				m_FrameCount1;

	float			m_DeltaTime;

	int				m_PrevTime;
	int				m_NowTime;

	bool			m_DestroyWindow;

private:
	static NNApplication* m_pInstance;

private:
	NNApplication();
	~NNApplication();

};



