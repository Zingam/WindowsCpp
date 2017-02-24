///////////////////////////////////////////////////////////////////////////////
#include "XAudio2Engine.h"
///////////////////////////////////////////////////////////////////////////////
// C Header inclusions
///////////////////////////////////////////////////////////////////////////////
#include <cassert>
///////////////////////////////////////////////////////////////////////////////
// C++ Header inclusions
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
///////////////////////////////////////////////////////////////////////////////
// System Library inclusions
///////////////////////////////////////////////////////////////////////////////
#include <xaudio2.h>
///////////////////////////////////////////////////////////////////////////////
// External Library inclusions
///////////////////////////////////////////////////////////////////////////////
#include "External/Common/Utils.h"
///////////////////////////////////////////////////////////////////////////////
// Namespace declarations
///////////////////////////////////////////////////////////////////////////////
using Common::Utils::SafeRelease;
using Common::Utils::SafeDestroyVoice;
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Constructors & Destructors
///////////////////////////////////////////////////////////////////////////////
///
/// PCM Constructor
///
XAudio2Engine::XAudio2Engine()
    : m_IsInitialized(false)
{
    auto hresult = XAudio2Create(&m_XAudio2Engine);
    if (FAILED(hresult))
    {
        std::cout << "XAudio2 engine was not created!" << std::endl;
        goto XAudio2Engine_ctor_Error;
    }

    XAUDIO2_DEBUG_CONFIGURATION debug = { 0 };
    debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
    debug.BreakMask = XAUDIO2_LOG_ERRORS;
    m_XAudio2Engine->SetDebugConfiguration(&debug, nullptr);

    hresult = m_XAudio2Engine->CreateMasteringVoice(
        &m_MasteringVoice,
        XAUDIO2_DEFAULT_CHANNELS,
        XAUDIO2_DEFAULT_SAMPLERATE,
        0,
        0, 
        NULL);
    if (FAILED(hresult))
    {
        std::cout << "Master voice was not created!" << std::endl;
        goto XAudio2Engine_ctor_Error;
    }

    m_IsInitialized = true;
    goto XAudio2Engine_ctor_End;

    // C4533: initialization of 'debug' is skipped by 'goto XAudio2Engine_ctor_Error'
#pragma warning (disable:4533)
XAudio2Engine_ctor_Error:
    m_IsInitialized = false;
#pragma warning (default:4533)

XAudio2Engine_ctor_End:
    {}
}

///
/// PCM Constructor
///
XAudio2Engine::~XAudio2Engine()
{   
    for (auto sourceVoice : m_SourceVoices)
    {
        if (nullptr != sourceVoice)
        {
            SafeDestroyVoice(sourceVoice);
        }
    }
    m_SourceVoices.clear();

    if (nullptr != m_MasteringVoice)
    {
        SafeDestroyVoice(m_MasteringVoice);
    }

    if (nullptr != m_XAudio2Engine)
    {
        SafeRelease(m_XAudio2Engine);
    }
}

XAudio2Engine::XAudio2Engine(XAudio2Engine&& xAudio2Engine)
{
    m_IsInitialized = xAudio2Engine.m_IsInitialized;
    xAudio2Engine.m_IsInitialized = false;

    m_XAudio2Engine = xAudio2Engine.m_XAudio2Engine;
    xAudio2Engine.m_XAudio2Engine = nullptr;

    m_MasteringVoice = std::move(xAudio2Engine.m_MasteringVoice);
    xAudio2Engine.m_MasteringVoice = nullptr;

    m_SourceVoices = std::move(xAudio2Engine.m_SourceVoices);
    xAudio2Engine.m_SourceVoices.clear();
}

XAudio2Engine& 
XAudio2Engine::operator=(XAudio2Engine&& xAudio2Engine)
{
    if (this != &xAudio2Engine)
    {
        m_IsInitialized = xAudio2Engine.m_IsInitialized;
        xAudio2Engine.m_IsInitialized = false;

        m_XAudio2Engine = std::move(xAudio2Engine.m_XAudio2Engine);
        xAudio2Engine.m_XAudio2Engine = nullptr;

        m_MasteringVoice = std::move(xAudio2Engine.m_MasteringVoice);
        xAudio2Engine.m_MasteringVoice = nullptr;

        m_SourceVoices = std::move(xAudio2Engine.m_SourceVoices);
        xAudio2Engine.m_SourceVoices.clear();
    }

    return *this;
}

IXAudio2SourceVoice* 
XAudio2Engine::GetSourceVoice(WAVEFORMATEX const* format)
{
    assert(nullptr != m_XAudio2Engine);

    IXAudio2SourceVoice* sourceVoice = nullptr;
    auto hresult = m_XAudio2Engine->CreateSourceVoice(&sourceVoice, format);
    if (FAILED(hresult))
    {
        return nullptr;
    }
    m_SourceVoices.push_back(sourceVoice);

    return sourceVoice;
}
