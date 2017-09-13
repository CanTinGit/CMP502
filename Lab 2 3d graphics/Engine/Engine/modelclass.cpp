////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "modelclass.h"


ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}


bool ModelClass::Initialize(ID3D11Device* device)
{
	bool result;


	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	return true;
}


void ModelClass::Shutdown()
{
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}


void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int ModelClass::GetIndexCount()
{
	return m_indexCount;
}


bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	int m_slides = 32;
	float radius = 2.0f;
	double angle = 360 / m_slides;
	// Set the number of vertices in the vertex array.
	m_vertexCount = m_slides+1;

	// Set the number of indices in the index array.
	m_indexCount = m_slides*3;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	// Load the vertex array with data.

	//Triangle
	//vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	//vertices[0].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // Top middle.
	//vertices[1].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//vertices[2].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);  // Bottom right.
	//vertices[2].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//Square
	//vertices[0].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // Bottom left.
	//vertices[0].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//vertices[1].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);  // Top middle.
	//vertices[1].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//vertices[2].position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);  // Bottom right.
	//vertices[2].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);


	//vertices[3].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // Bottom right.
	//vertices[3].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//Star
	//vertices[0].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // Bottom left.
	//vertices[0].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//vertices[1].position = D3DXVECTOR3(0.224f, 0.309f, 0.0f);  // Top middle.
	//vertices[1].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//vertices[2].position = D3DXVECTOR3(0.951f, 0.309f, 0.0f);  // Bottom right.
	//vertices[2].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//vertices[3].position = D3DXVECTOR3(0.363f, -0.118f, 0.0f);  // Bottom right.
	//vertices[3].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//vertices[4].position = D3DXVECTOR3(0.587f, -0.809f, 0.0f);  // Bottom right.
	//vertices[4].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//vertices[5].position = D3DXVECTOR3(0.0f, -0.382f, 0.0f);  // Bottom right.
	//vertices[5].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//vertices[6].position = D3DXVECTOR3(-0.588f, -0.809f, 0.0f);  // Bottom right.
	//vertices[6].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//vertices[7].position = D3DXVECTOR3(-0.363f, -0.118f, 0.0f);  // Bottom right.
	//vertices[7].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//vertices[8].position = D3DXVECTOR3(-0.951f, 0.309f, 0.0f);  // Bottom right.
	//vertices[8].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//vertices[9].position = D3DXVECTOR3(-0.224f, 0.309f, 0.0f);  // Bottom right.
	//vertices[9].color = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	//Circle
	vertices[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  
	vertices[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);  //Red, Green, Blue
	float tempColor = 1.0f / (float)m_slides;
	float colorX, colorY, colorZ;
	colorX = 0.0f;
	colorY = 0.0f;
	colorZ = 0.0f;
	for (int i = 0; i < m_vertexCount-1; i++) 
	{
		float tempAngle = i * angle;
		float X = radius * cos(tempAngle*PI / 180);
		float Y = radius * sin(tempAngle*PI / 180);
		if (tempAngle == 90)
		{
			X = 0;
		}

		if (tempAngle == 270)
		{
			X = 0;
		}
		if (tempAngle == 0)
		{
			Y = 0;
		}
		if (tempAngle == 180)
		{
			Y = 0;
		}
		
		colorX = colorX + 2 * tempColor;
		colorZ = colorZ + 2 * tempColor;
		vertices[i+1].position = D3DXVECTOR3(X, Y, 0.0f);
		vertices[i+1].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	}

	// Load the index array with data.

	//Triangle
	//indices[0] = 1;  // Bottom left.
	//indices[1] = 0;  // Top middle.
	//indices[2] = 2;  // Bottom right.

	////Star
	//indices[0] = 9;  // Bottom left.
	//indices[1] = 0;  // Top middle.
	//indices[2] = 1;  // Bottom right.
	//indices[3] = 9;
	//indices[4] = 1;
	//indices[5] = 3;
	//indices[6] = 1;  
	//indices[7] = 2;  
	//indices[8] = 3;  
	//indices[9] = 3;
	//indices[10] = 4;
	//indices[11] = 5;
	//indices[12] = 3;  
	//indices[13] = 5;  
	//indices[14] = 7;  
	//indices[15] = 5;
	//indices[16] = 6;
	//indices[17] = 7;
	//indices[18] = 7;
	//indices[19] = 9;
	//indices[20] = 3;
	//indices[21] = 7;
	//indices[22] = 8;
	//indices[23] = 9;

	//circle
	int offset = 1;
	indices[0] = 1;
	for (int i = 1; i < m_indexCount-2; i++)
	{
		int temp = i % 3;
		if(temp == 1)
		{
			indices[i] = 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 1;
			offset++;
		}
	}
	indices[m_indexCount - 1] = 1;
	indices[m_indexCount - 2] = 0;
	indices[m_indexCount - 3] = m_slides;


	// Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}