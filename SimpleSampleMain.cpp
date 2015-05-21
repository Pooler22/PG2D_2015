﻿//--------------------------------------------------------------------------------------
// File: SimpleSampleMain.cpp
//
// This is a simple Windows Store app for Windows 8.1 Preview showing use of DirectXTK
//
// http://go.microsoft.com/fwlink/?LinkId=248929
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------


#include "pch.h"
#include "SimpleSampleMain.h"

#include <DirectXColors.h>			// For named colors	
#include "Common\DirectXHelper.h"	// For ThrowIfFailed

using namespace SimpleSample;

//Added for Input and Overlay
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Concurrency;


// Loads and initializes application assets when the application is loaded.
SimpleSampleMain::SimpleSampleMain(const std::shared_ptr<DX::DeviceResources>& deviceResources) :
	m_deviceResources(deviceResources)
{
    m_sceneRenderer = std::unique_ptr<DirectXTK3DSceneRenderer>(new DirectXTK3DSceneRenderer(m_deviceResources));

	//TODO: Insert stuff here - initialization


	// Setting render target to 30 FPS !!!!!!!!!!!!!!

	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 30); 
	// Remember - it is usually not necessary to limit the framerate, it will be capped to display refresh rate anyway, usually 60 Hz, - default Windows Apps behaviour

	m_deviceResources->RegisterDeviceNotify(this);
}

SimpleSampleMain::~SimpleSampleMain()
{
    // Deregister device notification
    m_deviceResources->RegisterDeviceNotify(nullptr);
}

// Updates application state when the window size changes (e.g. device orientation change)
void SimpleSampleMain::CreateWindowSizeDependentResources() 
{
	m_sceneRenderer->CreateWindowSizeDependentResources();
}

// Updates the application state once per frame.
void SimpleSampleMain::Update() 
{
	// Update scene objects.
	m_timer.Tick([&]()
	{
		m_sceneRenderer->Update(m_timer);
	});
}

//// This is the main Render function, all other objects go here
//// Remember to use <vector> for all elements that need rendering - better memory access pattern
// Renders the current frame according to the current application state.
// Returns true if the frame was rendered and is ready to be displayed.
bool SimpleSampleMain::Render() 
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return false;
	}

	auto context = m_deviceResources->GetD3DDeviceContext();

	// Reset the viewport to target the whole screen.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	// Reset render targets to the screen.
	ID3D11RenderTargetView *const targets[1] = { m_deviceResources->GetBackBufferRenderTargetView() };
	context->OMSetRenderTargets(1, targets, m_deviceResources->GetDepthStencilView());

	// Clear the back buffer and depth stencil view.
    context->ClearRenderTargetView(m_deviceResources->GetBackBufferRenderTargetView(), DirectX::Colors::CornflowerBlue);
	context->ClearDepthStencilView(m_deviceResources->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Render the scene objects.
	m_sceneRenderer->Render();

	return true;
}


// Signals a new audio device is available
void SimpleSampleMain::NewAudioDevice()
{
    if (m_sceneRenderer)
        m_sceneRenderer->NewAudioDevice();
}

// Notifies renderers that device resources need to be released.
void SimpleSampleMain::OnDeviceLost()
{
	m_sceneRenderer->ReleaseDeviceDependentResources();
}

// Notifies renderers that device resources may now be recreated.
void SimpleSampleMain::OnDeviceRestored()
{
	m_sceneRenderer->CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}
