////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "rendertextureclass.h"
#include "debugwindowclass.h"
#include "textureshaderclass.h"
#include "textclass.h"
#include "particleshaderclass.h"
#include "particlesystemclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int, float);
	bool Render(float, float);
	void CameraMove(float, int);
	void OpenOrCloseParticle();
	void OpendOrCloseFPS();
	void ShowMiniMap();
	void ChangeLightColor(float, float, int);
	void ChangeLightColorBack();
	void ChangeWorldMatrix();

private:
	bool RenderToTexture();
	bool RenderScene(float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;

	DebugWindowClass* m_DebugWindow;
	RenderTextureClass* m_RenderTexture;
	TextureShaderClass* m_TextureShader;

	//Text
	TextClass* m_Text;

	//Particle
	ParticleShaderClass* m_ParticleShader;
	ParticleSystemClass* m_ParticleSystem;

	//Control Particle
	bool isParticleRun;

	bool isShowingFps;
	bool isShowingMiniMap;
	bool isChangedMatrix;
};

#endif