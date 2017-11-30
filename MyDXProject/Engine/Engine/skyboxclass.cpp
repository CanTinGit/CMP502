////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "skyboxclass.h"

SkyBoxClass::SkyBoxClass(LPDIRECT3DDEVICE9  pDevice)
{
	//????????  
	m_pVertexBuffer = NULL;
	m_pd3dDevice = pDevice;
	for (int i = 0; i<5; i++)
		m_pTexture[i] = NULL;
	m_Length = 0.0f;
}