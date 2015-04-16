//For educational use only
//NOT TO BE USED IN COMMERCIAL OR SCHOOL PROJECTS

#pragma once

#include <wrl.h>


//#include "..\Common\DirectXHelper.h"	// For ThrowIfFailed and ReadDataAsync

#include <Content\AnimatedTexture.h>
#include <SpriteBatch.h>

#include <DirectXMath.h>
#include <DirectXTK\Inc\SimpleMath.h>


class Player
{
public:
	Player(ID3D11ShaderResourceView* playerSpriteSheet) : framesOfAnimation(4), framesToBeShownPerSecond(4)
	{
		position = DirectX::XMFLOAT2(512, 512);
		
		//Instantiate animation here
		texture = playerSpriteSheet;
		float rotation = 0.f;
		float scale = 3.f;
		animation.reset(new AnimatedTexture(DirectX::XMFLOAT2(0.f, 0.f), rotation, scale, 0.5f));
		animation->Load(texture.Get(), framesOfAnimation, framesToBeShownPerSecond);

		width = textureWidth = animation->getFrameWidth();
		height = textureHeight = animation->getFrameHeight();

		rectangle.X = position.x;
		rectangle.Y = position.y;
		rectangle.Height = height;
		rectangle.Width = width;
		
	}

	void Update(float elapsed)
	{
		animation->Update(elapsed);
	}

	void Draw(DirectX::SpriteBatch* batch)
	{
		animation->Draw(batch, position);
	}

public:
	Windows::Foundation::Rect							rectangle;

private:
	DirectX::XMFLOAT2									position;

	int													width;
	int													height;
	int													textureWidth;
	int													textureHeight;
	int													framesOfAnimation;
	int													framesToBeShownPerSecond;

	//Texture and animation
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	texture;
	std::unique_ptr<AnimatedTexture>					animation;

};