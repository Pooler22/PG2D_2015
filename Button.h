#pragma once

#include <Content\AnimatedTexture.h>
#include <SpriteBatch.h>
#include <DirectXMath.h>
#include <DirectXTK\Inc\SimpleMath.h>
#include "SpriteFont.h"

class Button
{
public:
	Button(ID3D11ShaderResourceView* playerSpriteSheet, SpriteFont *spriteFont, std::wstring inString, XMFLOAT2 inPosition) : framesOfAnimation(4), framesToBeShownPerSecond(4)
	{
		string = inString;
		position = inPosition;

		texture = playerSpriteSheet;
		float rotation = 0.f;
		float scale = 3.f;
		animation.reset(new AnimatedTexture(DirectX::XMFLOAT2(0.f, 0.f), rotation, 3, 0.5f));
		animation->Load(texture.Get(), framesOfAnimation, framesToBeShownPerSecond);

		m_font.reset(spriteFont);

		width = textureWidth = animation->getFrameWidth();
		height = textureHeight = animation->getFrameHeight();

		updateBoundingRect();

	}

	Button(ID3D11ShaderResourceView* playerSpriteSheet, SpriteFont *spriteFont) : framesOfAnimation(4), framesToBeShownPerSecond(4)
	{
		//Instantiate animation here
		texture = playerSpriteSheet;
		float rotation = 0.f;
		float scale = 3.f;
		animation.reset(new AnimatedTexture(DirectX::XMFLOAT2(0.f, 0.f), rotation, scale, 0.5f));
		animation->Load(texture.Get(), framesOfAnimation, framesToBeShownPerSecond);
		color = Colors::Black;
		m_font.reset(spriteFont);

		width = textureWidth = animation->getFrameWidth();
		height = textureHeight = animation->getFrameHeight();

		updateBoundingRect();
	}


	void setPosition(DirectX::XMFLOAT2 newPosition)
	{
		position = newPosition;
		updateBoundingRect();
	}

	void setPosition(float posX, float posY)
	{
		position.x = posX;
		position.y = posY;
		updateBoundingRect();
	}

	DirectX::XMFLOAT2 getPosition()
	{
		return position;
	}

	DirectX::XMFLOAT2 getDimension()
	{
		return DirectX::XMFLOAT2(width, height);
	}

	bool isClicked(float x, float y) 
	{
		if (x > (rectangle.X) && y > (rectangle.Y) && x < (rectangle.X + rectangle.Width) && y < (rectangle.Y + rectangle.Height))
		{
			color = Colors::Blue;
			return true;
		}
		else
		{
			color = Colors::Black;
			return false;
		}
	}

	void Update(float elapsed)
	{
		animation->Update(elapsed);
	}

	void Draw(DirectX::SpriteBatch* batch)
	{
		animation->Draw(batch, position);
		m_font->DrawString(batch, string.c_str(), position, color);
	}

	void setString(std::wstring in)
	{
		string = in;
	}

	std::wstring getString()
	{
		return string;
	}

	void setId(std::wstring in)
	{
		id = in;
	}

	std::wstring getId()
	{
		return id;
	}

	Windows::Foundation::Rect getBoundingRect()
	{
		return rectangle;
	}

private:
	void updateBoundingRect()
	{
		//TODO: proper updating when rotating player object
		rectangle.X = position.x;
		rectangle.Y = position.y;
		rectangle.Height = height;
		rectangle.Width = width;
	}

public:
	
	int													width;
	int													height;
	int													textureWidth;
	int													textureHeight;
	int													framesOfAnimation;
	int													framesToBeShownPerSecond;
	Windows::Foundation::Rect							rectangle;
	DirectX::XMFLOAT2									position;
	
	std::wstring										string;
	std::wstring										id;
	
	std::unique_ptr<DirectX::SpriteFont>				m_font;
	DirectX::XMVECTOR									color;
	
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	texture;
	std::unique_ptr<AnimatedTexture>					animation;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pressTexture;
	std::unique_ptr<AnimatedTexture>					presAnimation;
};