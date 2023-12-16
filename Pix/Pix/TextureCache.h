#pragma once
#include "Texture.h"

class TextureCache
{
public:
	static TextureCache* Get();

	void Clear();
	void SetTexture(const std::string& fileName);

	X::Color SampleColor(const X::Color& uv) const;
	void SetUseFilter(bool useFilter);
	void SetAddressMode(AddressMode addressMode);

private:
	std::vector<std::unique_ptr<Texture>> mTextures;
	const Texture* mCurrentTexture = nullptr;
	AddressMode mAddressMode = AddressMode::Clamp;
	bool mUseFilter;
};

