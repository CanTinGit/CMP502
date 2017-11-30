////////////////////////////////////////////////////////////////////////////////
// Filename: skyboxclass.h
////////////////////////////////////////////////////////////////////////////////
#pragma once  
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <dxgi.h>
#include <d3dcommon.h>

//?????????FVF??????  
struct SKYBOXVERTEX
{
	float   x, y, z;
	float   u, v;
};
#define D3DFVF_SKYBOX D3DFVF_XYZ|D3DFVF_TEX1  


class SkyBoxClass
{
private:
	ID3D11Device *m_pd3dDevice;            
	ID3D11Buffer *m_pVertexBuffer;       
	ID3D11ShaderResourceView  *m_pTexture[5];          //5???????  
	float           m_Length;           

public:
	SkyBoxClass(ID3D11Device  m_device);      //????  
	virtual ~SkyBoxClass(void);                             //????  

public:
	bool    InitSkyBox(float Length);   //????????  
	bool    LoadSkyTextureFromFile(wchar_t *pFrontTextureFile, wchar_t *pBackTextureFile, wchar_t *pLeftTextureFile, wchar_t *pRightTextureFile, wchar_t *pTopTextureFile);  //????????????????  
	void    RenderSkyBox(D3DXMATRIX *pMatWorld, bool bRenderFrame); //?????,???????????????????????????????  

};