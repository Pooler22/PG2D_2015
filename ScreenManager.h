#pragma once

#include <wrl.h>
#include <future>
#include <Content\AnimatedTexture.h>
#include <SpriteBatch.h>
#include <DirectXMath.h>
#include <DirectXTK\Inc\SimpleMath.h>
#include "SpriteFont.h"
#include "Screen.h"
//#include "..\Common\DirectXHelper.h"	// For ThrowIfaFailed and ReadDataAsync

class ScreenManager
{
public:
	ScreenManager()
	{
		screens = std::vector<std::shared_ptr<Screen>>();
	};
	~ScreenManager() {};
	void addElement(Screen* screen)
	{
		screens.push_back(std::shared_ptr<Screen>(screen));
	}

	void Update(float elapsed)
	{
		for (auto &screen : screens)
		{
			if (screen->getName() == name)
				screen->Update(elapsed);
		}
	}

	void Draw(DirectX::SpriteBatch* batch)
	{
		for (auto &screen : screens)
		{
			if(screen->getName() == name)
				screen->Draw(batch);
		}
	}

	void setName(std::wstring stringIn)
	{
		name = stringIn;
	}

	std::wstring getName()
	{
		return name;
	}

private:
	std::wstring								name;
	std::vector<std::shared_ptr<Screen>>		screens;

};