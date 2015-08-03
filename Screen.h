#pragma once

#include <wrl.h>
#include <future>
#include <Content\AnimatedTexture.h>
#include <SpriteBatch.h>
#include <DirectXMath.h>
#include <DirectXTK\Inc\SimpleMath.h>
#include "SpriteFont.h"
//#include "..\Common\DirectXHelper.h"	// For ThrowIfaFailed and ReadDataAsync

class Screen
{
public:
	Screen() 
	{
		buttons = std::vector<std::shared_ptr<Button>>();
	};
	~Screen() {};
	void addElement(Button* button)
	{
		buttons.push_back(std::shared_ptr<Button>(button));
	}

	void Update(float elapsed)
	{
		for (auto &button : buttons)
		{
			button->Update(elapsed);
		}
	}

	void Draw(DirectX::SpriteBatch* batch)
	{
		for (auto &button : buttons)
		{
			button->Draw(batch);
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
	std::vector<std::shared_ptr<Button>>		buttons;

};