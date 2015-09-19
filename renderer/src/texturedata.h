#pragma once
#include <QSharedData>

namespace renderer {

	class TextureData : public QSharedData {
	public:
		TextureData();
		~TextureData();
		TextureData(const TextureData& src);
		int s;
	};
}