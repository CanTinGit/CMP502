////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_Input = 0;

	m_RenderTexture = 0;
	m_DebugWindow = 0;
	m_TextureShader = 0;

	//Text
	m_Text = 0;

	//Particle
	m_ParticleShader = 0;
	m_ParticleSystem = 0;

	//Control Particle
	isParticleRun = false;

	isShowingFps = true;
	isShowingMiniMap = false;
	isChangedMatrix = false;

	//Terrain
	m_Terrain = 0;
	m_TerrainShader = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd, HINSTANCE hinstance)
{
	bool result;
	D3DXMATRIX baseViewMatrix;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	//Create the Input object
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the particle shader object.
	m_ParticleShader = new ParticleShaderClass;
	if (!m_ParticleShader)
	{
		return false;
	}

	// Initialize the particle shader object.
	result = m_ParticleShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the particle system object.
	m_ParticleSystem = new ParticleSystemClass;
	if (!m_ParticleSystem)
	{
		return false;
	}

	// Initialize the particle system object.
	result = m_ParticleSystem->Initialize(m_D3D->GetDevice(), L"../Engine/data/star.dds");
	if (!result)
	{
		return false;
	}

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}


	//// Set the initial position of the camera.
	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	
	// Create the model object.
	m_Model = new ModelClass;
	if(!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), "../Engine/data/model.txt", L"../Engine/data/model.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(1.0f);

	// Create the render to texture object.
	m_RenderTexture = new RenderTextureClass;
	if (!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}

	// Create the debug window object.
	m_DebugWindow = new DebugWindowClass;
	if (!m_DebugWindow)
	{
		return false;
	}

	// Initialize the debug window object.
	result = m_DebugWindow->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, 100, 100);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the debug window object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the Terrain object
	m_Terrain = new TerrainClass();
	if (!m_Terrain)
	{
		return false;
	}

	result = m_Terrain->InitializeTerrain(m_D3D->GetDevice(), 128,128);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain shader object
	m_TerrainShader = new TerrainShaderClass();
	if (!m_TerrainShader)
	{
		return false;
	}

	result = m_TerrainShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the particle system object.
	if (m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	// Release the particle shader object.
	if (m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}

	// Release the texture shader object
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the debug window object.
	if (m_DebugWindow)
	{
		m_DebugWindow->Shutdown();
		delete m_DebugWindow;
		m_DebugWindow = 0;
	}

	// Release the render to texture object.
	if (m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool GraphicsClass::Frame(int fps, int cpu, float frameTime)
{
	bool result;
	static float rotation = 0.0f;
	static float delta =0.0f;


	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Update the delta variable each frame. (keep this between 0 and 1)
	delta += 0.001;
	if(delta >1.0f)
	{
		delta -=1.0f;
	}

	// Run the frame processing for the particle system.
	if (isParticleRun == true)
	{
		m_ParticleSystem->Frame(frameTime, m_D3D->GetDeviceContext());
	}

	//Set the Fps
	if (isShowingFps)
	{
		result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
		if (!result)
		{
			return false;
		}

		// Set the cpu usage.
		result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
		if (!result)
		{
			return false;
		}
	}
		
	// Render the graphics scene.
	result = Render(rotation, delta);
	if(!result)
	{
		return false;
	}

	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	result = HandleInput();
	if (!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(float rotation, float deltavalue)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;

	// Render the entire scene to the texture first.
	result = RenderToTexture();
	if (!result)
	{
		return false;
	}

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Render the scene as normal to the back buffer.
	result = RenderScene(deltavalue);
	if (!result)
	{
		return false;
	}

	m_D3D->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	//Render the terrain
	m_Terrain->Render(m_D3D->GetDeviceContext());

	//Render the terrain with terrain shader
	result = m_TerrainShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Light->GetDirection());

	// Put the particle system vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ParticleSystem->Render(m_D3D->GetDeviceContext());

	// Render the model using the texture shader.
	result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_ParticleSystem->GetTexture());
	if (!result)
	{
		return false;
	}

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Put the debug window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_DebugWindow->Render(m_D3D -> GetDeviceContext(), 50, 50);
	if (!result)
	{
		return false;
	}

	if (isShowingMiniMap)
	{
		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_DebugWindow->GetIndexCount(), worldMatrix, viewMatrix,
			orthoMatrix, m_RenderTexture->GetShaderResourceView());
		if (!result)
		{
			return false;
		}
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();
	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::RenderToTexture()
{
	bool result;


	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());


	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);

	// Render the scene now and it will draw to the render to texture instead of the back buffer.
	result = RenderScene(0);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	return true;
}

bool GraphicsClass::RenderScene(float delta)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;
	static float rotation = 0.0f;


	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	//D3DXMatrixRotationY(&worldMatrix, rotation);

	
	D3DXMATRIX cubeROT, cubeMOVE;
	D3DXMatrixRotationY(&cubeROT, rotation);
	D3DXMatrixRotationX(&cubeMOVE, rotation);
	
	if (isChangedMatrix == true)
	{
		worldMatrix = worldMatrix * cubeROT * cubeMOVE;
	}
	else
	{
		D3DXMatrixRotationY(&worldMatrix, rotation);
	}
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D -> GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), delta, m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), m_Model->GetTexture());
	if (!result)
	{
		return false;
	}

	return true;
}

void GraphicsClass::CameraMove(float speed, int flag) 
{
	// flag = 1, move X
	if (flag == 1) 
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x + speed, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
	}

	if (flag == 2)
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x, m_Camera->GetPosition().y + speed, m_Camera->GetPosition().z);
	}
}

void GraphicsClass::OpenOrCloseParticle() 
{
	if (isParticleRun == true)
	{
		isParticleRun = false;
	}
	else
	{
		isParticleRun = true;
	}
}


void GraphicsClass::OpendOrCloseFPS()
{
	if (isShowingFps == true)
	{
		isShowingFps = false;
	}
	else
	{
		isShowingFps = true;
	}
}

void GraphicsClass::ShowMiniMap()
{
	if (isShowingMiniMap == true)
	{
		isShowingMiniMap = false;
	}
	else
	{
		isShowingMiniMap = true;
	}
}

void GraphicsClass::ChangeLightColor(float speed, float max, int flag)
{
	//Change the red color
	if (flag == 1)
	{
		m_Light->SetDiffuseColor(m_Light->GetDiffuseColor().x + speed, m_Light->GetDiffuseColor().y, m_Light->GetDiffuseColor().z, m_Light->GetDiffuseColor().w);
	}

	//change the Green
	if (flag == 2)
	{
		m_Light->SetDiffuseColor(m_Light->GetDiffuseColor().x, m_Light->GetDiffuseColor().y + speed, m_Light->GetDiffuseColor().z, m_Light->GetDiffuseColor().w);
	}

	//change the blue
	if (flag == 3)
	{
		m_Light->SetDiffuseColor(m_Light->GetDiffuseColor().x + speed, m_Light->GetDiffuseColor().y, m_Light->GetDiffuseColor().z + speed, m_Light->GetDiffuseColor().w);
	}
}

void GraphicsClass::ChangeLightColorBack()
{
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void GraphicsClass::ChangeWorldMatrix()
{
	if (isChangedMatrix == true)
	{
		isChangedMatrix = false;
	}
	else
	{
		isChangedMatrix = true;
	}
}

void GraphicsClass::GenerateTerrain()
{
	m_Terrain->GenerateHeightMap(m_D3D->GetDevice(), true);
}

bool GraphicsClass::HandleInput()
{
	bool result;
	//Check Input and update Camera position
	if (m_Input->IsWPressed() == true)
		CameraMove(0.3f, 2);
	if (m_Input->IsSPressed() == true)
		CameraMove(-0.3f, 2);

	if (m_Input->IsAPressed() == true)
		CameraMove(-0.3f, 1);

	if (m_Input->IsDPressed() == true)
		CameraMove(0.3f, 1);

	//Check Input and control the Particle system
	if (m_Input->IsPPressed() == true)
		OpenOrCloseParticle();

	//Check Input and control the Sound system
	//if (m_Input->IsRPressed() == true)
	//	m_Sound->PauseAndPlay();


	//Check Input and control the FPS
	if (m_Input->IsLPressed() == true)
		OpendOrCloseFPS();

	//Control the MiniMap
	if (m_Input->IsMPressed() == true)
		ShowMiniMap();

	//Control the Light color
	if (m_Input->IsTPressed() == true)
		ChangeLightColor(0.1f, 5.0f, 1);

	if (m_Input->IsYPressed() == true)
		ChangeLightColor(0.1f, 5.0f, 2);

	if (m_Input->IsUPressed() == true)
		ChangeLightColor(0.1f, 5.0f, 3);

	//Change the light to white
	if (m_Input->IsBPressed() == true)
		ChangeLightColorBack();

	//Change world Matrix
	if (m_Input->IsXPressed() == true)
		ChangeWorldMatrix();

	if (m_Input->IsSpacePressed() == true)
		GenerateTerrain();
	return true;
}