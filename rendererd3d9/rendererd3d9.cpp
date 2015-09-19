#include "rendererd3d9.h"
#include "hwshaderd3d9.h"
#include "hwvertexbufferd3d9.h"
#include "hwindexbufferd3d9.h"
#include <QtGui/QWidget>
#include <qdebug.h>
#include <d3d9.h>
#include <d3dx9.h>

namespace d3d9{

	void checkD3D(HRESULT hr)
	{
		Q_ASSERT(!FAILED(hr));
	}

	RendererD3D9::RendererD3D9()
	{
		pDeviceD3D9 = NULL;
		this->backGround = D3DCOLOR_ARGB(255,0,0,0);
	}

	RendererD3D9::~RendererD3D9()
	{

	}

	bool RendererD3D9::init(QWidget* outputWnd,int height,int width,bool windowed)
	{
		HWND winID = (HWND)outputWnd->winId();

		//init d3d9
		LPDIRECT3D9 pD3D9 = NULL;
		pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);

		D3DPRESENT_PARAMETERS d3dpp;
		memset(&d3dpp,0,sizeof(d3dpp));
		d3dpp.BackBufferHeight = height;
		d3dpp.BackBufferWidth = width;
		d3dpp.Windowed = windowed;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.hDeviceWindow = winID;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		IDirect3DDevice9* pD3DDevice = NULL;
		HRESULT hr = pD3D9->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,
			winID,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dpp,&pD3DDevice);
		pD3D9->Release();

		this->pDeviceD3D9 = pD3DDevice;

		return true;
	}

	void RendererD3D9::shutdown()
	{
		this->pDeviceD3D9->Release();
	}

	void RendererD3D9::beginFrame()
	{
		HRESULT hr = this->pDeviceD3D9->Clear(0,NULL,
			D3DCLEAR_TARGET|D3DCLEAR_STENCIL|D3DCLEAR_ZBUFFER,
			this->backGround,1.0f,0);
		checkD3D(hr);
		hr = this->pDeviceD3D9->BeginScene();
		checkD3D(hr);
	}

	void RendererD3D9::endFrame()
	{
		HRESULT hr = this->pDeviceD3D9->EndScene();
		checkD3D(hr);
	}

	renderer::RenderElement* RendererD3D9::createRenderElement(renderer::RENDERELEMENT_TYPE type)
	{
		return NULL;
	}

	void RendererD3D9::drawElement(renderer::RenderElement* pElement,renderer::ShaderItem* pShaderItem)
	{

	}

	void RendererD3D9::present()
	{
		HRESULT hr = this->pDeviceD3D9->Present(NULL,NULL,NULL,NULL);
		checkD3D(hr);
	}

	renderer::HWShader* RendererD3D9::createHardWareShader(const char * shaderString,int strLen, const char* functionName,QVector<QString> macro,renderer::ShaderType type)
	{
		if (strLen < 0)
			strLen = strlen(shaderString);
		
		static QVector<D3DXMACRO> macroBuffer;
		macroBuffer.resize(macro.size());
		for (int i = 0; i < macro.size(); i++)
		{
			macroBuffer[i].Name = (const char*)macro[i].constData();
		}
		const char* profile;
		if (type == renderer::SHADER_PS)
			profile = "ps_3_0";
		else
			profile = "vs_3_0";
		LPD3DXBUFFER outShader = NULL;
		LPD3DXBUFFER errMsg = NULL;
		LPD3DXCONSTANTTABLE constantTable = NULL;
		HRESULT hr = D3DXCompileShader(shaderString,strLen,macroBuffer.constData(),NULL,functionName,profile,0,&outShader,&errMsg,&constantTable);
		if (hr != S_OK)
		{
			qDebug()<<"compile shader failed : "<<(const char*)errMsg->GetBufferPointer();
			if (errMsg)
				errMsg->Release();
			if (outShader)
				outShader->Release();
			if (constantTable)
				constantTable->Release();
			return NULL;
		}
		IDirect3DPixelShader9* pPS = NULL;
		IDirect3DVertexShader9* pVS = NULL;
		if (type == renderer::SHADER_PS)
			hr = this->pDeviceD3D9->CreatePixelShader((const DWORD*)outShader->GetBufferPointer(),&pPS);
		else
			hr = this->pDeviceD3D9->CreateVertexShader((const DWORD*)outShader->GetBufferPointer(),&pVS);
		outShader->Release();
		if (hr != S_OK)
		{
			if (pPS)
				pPS->Release();
			if (pVS)
				pVS->Release();
			return NULL;
		}
		HWShaderD3D9* pShader = new HWShaderD3D9();
		pShader->initShader(type,pVS,pPS,constantTable);

		//HWShaderD3D9* pShader;
		return pShader;
	}

	void RendererD3D9::releaseHardWareShader(d3d9::HWShaderD3D9* pShader)
	{
		if (pShader->pCTable)
			pShader->pCTable->Release();
		pShader->pCTable = NULL;
		if (pShader->pPS)
			pShader->pPS->Release();
		pShader->pPS = NULL;
		if (pShader->pVS)
			pShader->pVS->Release();
		pShader->pVS = NULL;
		pShader->sType = renderer::SHADER_END;

		delete pShader;
	}

	renderer::HWTexture* RendererD3D9::createHardWareTexture(
		int width,int height,renderer::TextureType type,
		int nlod,renderer::TextureFormat format,int FLAGS)
	{
		return NULL;
	}

	renderer::HWIndexBuffer* RendererD3D9::createHardWareIndexBuffer(int count,bool dynamic)
	{
		int length = count * sizeof(short);
		DWORD usage = 0;
		if (dynamic)
			usage = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
		D3DPOOL pool = D3DPOOL_MANAGED;
		if (dynamic)
			pool = D3DPOOL_DEFAULT;
		IDirect3DIndexBuffer9* pIndexBuffer = NULL;
		HRESULT hr = this->pDeviceD3D9->CreateIndexBuffer(length,usage,D3DFMT_INDEX16,pool,&pIndexBuffer,NULL);
		if (hr != S_OK)
			return NULL;
		HWIndexBufferD3D9* pIB = new HWIndexBufferD3D9();
		pIB->initIndexBuffer(count,pIndexBuffer);
		return pIB;
	}

	void RendererD3D9::releaseHardWareIndexBuffer(HWIndexBufferD3D9* pIB)
	{
		if (pIB->pIB)
			pIB->pIB->Release();
		pIB->pIB = NULL;
		delete pIB;
	}

	renderer::HWVertexBuffer* RendererD3D9::createHardWareVertexBuffer(
		int count,renderer::VertexFormat fmt,bool dynamic)
	{
		int sizePerVertex = renderer::getVertexSize(fmt);
		int bufferSize = count * sizePerVertex;
		DWORD usage = 0;
		if (dynamic)
			usage = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
		D3DPOOL pool = D3DPOOL_MANAGED;
		if (dynamic)
			pool = D3DPOOL_DEFAULT;
		IDirect3DVertexBuffer9* pVB = NULL;
		HRESULT hr = this->pDeviceD3D9->CreateVertexBuffer(bufferSize,usage,0,pool,&pVB,NULL);
		if (hr != S_OK)
			return NULL;
		HWVertexBufferD3D9* pVertexBuffer = new HWVertexBufferD3D9;
		pVertexBuffer->initVertexBuffer(fmt,count,pVB);
		return pVertexBuffer;
	}

	void RendererD3D9::releaseHardWareVertexBuffer(HWVertexBufferD3D9* pVB)
	{
		if (pVB->pVertexBuffer)
			pVB->pVertexBuffer->Release();
		pVB->pVertexBuffer = NULL;
		pVB->format = renderer::VF_UNKNOWN;
		pVB->nCount = 0;
		delete pVB;	
	}

	void RendererD3D9::setBackGround(int r,int b,int g,int a)
	{
		this->backGround = D3DCOLOR_ARGB(a,r,g,b);
	}

	void RendererD3D9::resize(int height,int width)
	{

	}

	void RendererD3D9::setFullScreen(bool fullScreen)
	{

	}
}