#pragma once
#include "material.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"

namespace renderer {
	class RENDERER_EXPORT SubRenderMesh {
	public:
		SubRenderMesh();
		~SubRenderMesh();

		void setVertexBuffer(VertexBuffer vb,int iStream,int begin = 0,int count = -1);
		void setIndexBuffer(IndexBuffer ib,int begin = 0,int count = -1);
		void setRenderType(RenderType type);
		void setSubMatID(int id);

		VertexBuffer getVertexBuffer(int iStream);
		IndexBuffer getIndexBuffer();
		int getSubMatID();
		RenderType getRenderType(RenderType type);

		void getVertexBufferUsed(int iStream,int& begin,int& count);
		void getIndexBufferUsed(int& begin,int& count);

	private:
		VertexBuffer vb[VS_MAX];
		int vbBegin[VS_MAX];
		int vbCount[VS_MAX];
		IndexBuffer ib;
		int ibBegin;
		int ibCount;
		int subMatID;
		RenderType renderType;
	};

	class RENDERER_EXPORT RenderMesh {
	public:
		RenderMesh();
		~RenderMesh();

		void setSubMeshCount(int n);
		void setSubMesh(const SubRenderMesh& subRMesh,int i);

		void setMaterial(const Material& material);
		const Material& getMaterial();

		SubRenderMesh& getSubMesh(int i);
		int getNumSubMesh();


	private:
		QVector<SubRenderMesh> subMesh;
		Material mat;
	};
}