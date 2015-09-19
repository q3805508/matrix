#ifndef RENDERER_H
#define RENDERER_H

#include "renderer_global.h"
#include "rendererdef.h"
#include "renderelement.h"
#include <QString>
#include <QVector>
#include "shaderresource.h"
#include "shaderitem.h"

class QWidget;
namespace renderer {
	class HWTexture;
	class HWIndexBuffer;
	class HWShader;
	//class HWVertexBuffer;
	
	class RENDERER_EXPORT IRenderer //: public QObject
	{
		/*Q_OBJECT*/
	public:
		IRenderer();
		virtual ~IRenderer();

		virtual bool init(QWidget* outputWnd,int height,int width,bool windowed) = 0;
		virtual void shutdown() = 0;
		virtual void beginFrame() = 0;
		virtual void endFrame() = 0;
		//virtual void drawPrimitive() = 0;
		virtual void present() = 0;

		virtual RenderElement* createRenderElement(RENDERELEMENT_TYPE type) = 0;
		
		//virtual void drawElement(RenderElement* pElement,ShaderItem* pShaderItem) = 0;

		virtual HWTexture* createHardWareTexture(
			int width,int height,TextureType type,
			int nlod,TextureFormat format,int FLAGS) = 0;
		//virtual void destroyHardWareTexture(HWTexture* texture) = 0;

		virtual HWIndexBuffer* createHardWareIndexBuffer(int count,bool dynamic) = 0;
		virtual renderer::HWVertexBuffer* createHardWareVertexBuffer(int count,renderer::VertexFormat fmt,bool dynamic) = 0;
		//virtual void destroyHardWareIndexBuffer(HWIndexBuffer* indexBuffer) = 0;

		virtual HWShader* createHardWareShader(const char * shaderString,int strLen,
			const char* functionName,QVector<QString> macro,renderer::ShaderType type) = 0;
		//virtual void destroyHardWareShader(HWShader* pShader) = 0;
		virtual void setBackGround(int r,int b,int g,int a) = 0;

		void resize(int height,int width);
		void setFullScreen(bool fullScreen);
	private:
		IRenderer(const IRenderer& src);
		IRenderer& operator = (const IRenderer& src);
	};
}

#endif // RENDERER_H
