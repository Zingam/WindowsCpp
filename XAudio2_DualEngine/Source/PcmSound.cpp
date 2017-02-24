///////////////////////////////////////////////////////////////////////////////
#include "PcmSound.h"
///////////////////////////////////////////////////////////////////////////////
// C++ Library inclusions
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
// Project inclusions
///////////////////////////////////////////////////////////////////////////////
#include "XAudio2Engine.h"
///////////////////////////////////////////////////////////////////////////////
// Namespace declarations
///////////////////////////////////////////////////////////////////////////////
using Common::Utils::SafeDelete_Array;
///////////////////////////////////////////////////////////////////////////////


///
/// PCM Constructor
///
PcmSound::PcmSound(const wchar_t* filename)
    : Format(nullptr)
    , WaveData(nullptr)
    , WaveSize(0)
    , m_Filename(L"")
    , m_IsLoaded(false)
{
    // Get the full path from "filename"
    DWORD filenameExpandedSize = 0;
    // Get the required buffer size;
    filenameExpandedSize = ExpandEnvironmentStrings(filename, nullptr, filenameExpandedSize) + 1;
    // Expand the environment variables to a full path
    LPWSTR filenameExpanded = new WCHAR[filenameExpandedSize];
    ZeroMemory(filenameExpanded, filenameExpandedSize);
    ExpandEnvironmentStrings(filename, filenameExpanded, filenameExpandedSize);
    // Get the full path
    DWORD fullPathnameSize = 0;
    fullPathnameSize = GetFullPathName(
        filenameExpanded,
        fullPathnameSize,
        nullptr,
        nullptr) + 1;
    LPWSTR fullPathname = new WCHAR[fullPathnameSize];
    ZeroMemory(fullPathname, fullPathnameSize);
    GetFullPathName(
        filenameExpanded,
        fullPathnameSize,
        fullPathname,
        nullptr);
    // Complete member field initialization
    m_Filename = std::wstring(fullPathname);
    // Clean up
    SafeDelete_Array(filenameExpanded);
    SafeDelete_Array(fullPathname);

    auto hresult = m_Wave.Open(const_cast<wchar_t*>(m_Filename.c_str()), NULL, WAVEFILE_READ);
    if (FAILED(hresult))
    {
        goto PcmSound_ctor_Error;
    }

    auto waveFormatExSize = sizeof(WAVEFORMATEX) + m_Wave.GetFormat()->cbSize;
    Format = reinterpret_cast<WAVEFORMATEX*>(new CHAR[waveFormatExSize]);
    ZeroMemory(Format, waveFormatExSize);
    memcpy_s(Format, waveFormatExSize, m_Wave.GetFormat(), waveFormatExSize);
    WaveSize = m_Wave.GetSize();
    WaveData = new unsigned char[WaveSize];

    hresult = m_Wave.Read(WaveData, WaveSize, &WaveSize);
    if (FAILED(hresult))
    {
        if (WaveData)
        {
            SafeDelete_Array(WaveData);
            SafeDelete_Array(Format);
        }

        goto PcmSound_ctor_Error;
    }

    m_IsLoaded = true;

    hresult = m_Wave.Close();
    if (FAILED(hresult))
    {
        //goto PcmSound_ctor_Error;
    }

    goto PcmSound_ctor_End;

PcmSound_ctor_Error:
    m_IsLoaded = false;

PcmSound_ctor_End:
    {}
}

PcmSound::PcmSound(PcmSound && other)
{
    Format = other.Format;
    other.Format = nullptr;
    WaveData = other.WaveData;
    other.WaveData = nullptr;
    WaveSize = other.WaveSize;
    other.WaveSize = 0;
    m_Filename = std::move(other.m_Filename);
    other.m_Filename.clear();
    m_IsLoaded = other.m_IsLoaded;
    other.m_IsLoaded = false;
    m_Wave = std::move(other.m_Wave);
    other.m_Wave = CWaveFile();
}

///
/// PCM Destructor
///
PcmSound::~PcmSound()
{
    m_IsLoaded = false;
    
    SafeDelete_Array(Format);
    SafeDelete_Array(WaveData);
    WaveSize = 0;
}

PcmSound& 
PcmSound::operator=(PcmSound && other)
{
    if (this != &other)
    {
        Format = other.Format;
        other.Format = nullptr;
        WaveData = other.WaveData;
        other.WaveData = nullptr;
        WaveSize = other.WaveSize;
        other.WaveSize = 0;
        m_Filename = std::move(other.m_Filename);
        other.m_Filename.clear();
        m_IsLoaded = other.m_IsLoaded;
        other.m_IsLoaded = false;
        m_Wave = std::move(other.m_Wave);
        other.m_Wave = CWaveFile();
    }

    return *this;
}

///
/// IsLoaded - returns if the object contains valid sound data.
///
bool 
PcmSound::IsLoaded()
{
    return m_IsLoaded;
}

///
/// IsPlaying - returns if the sound is playing.
///
bool 
PcmSound::IsPlaying()
{
    XAUDIO2_VOICE_STATE state = { 0 };
    bool isPlaying = false;
    for (auto sourceVoice : m_SourceVoices)
    {
        sourceVoice->GetState(&state);
        if (state.BuffersQueued > 0)
        {
            isPlaying |= true;

            // One "true" occurrence is enough
            break;
        }
    }

    return isPlaying;
}

///
/// Play - plays the sound.
///
void 
PcmSound::Play()
{
    for (auto sourceVoice : m_SourceVoices)
    {
        if (SUCCEEDED(sourceVoice->Start()))
        {
            std::wcout << "Playing: " << m_Filename << std::endl;
        }
    }
}

///
/// Attach - Attaches the sound to the XAudio object.
///
void 
PcmSound::Attach(XAudio2Engine& xAudio2Engine)
{
    if ((m_IsLoaded)
        && (nullptr != this->Format))
    {
        auto sourceVoice = xAudio2Engine.GetSourceVoice(this->Format);
        if (nullptr != sourceVoice)
        {
            XAUDIO2_BUFFER buffer = { 0 };
            buffer.AudioBytes = this->WaveSize;
            buffer.pAudioData = this->WaveData;
            buffer.Flags = XAUDIO2_END_OF_STREAM;

            auto hresult = sourceVoice->SubmitSourceBuffer(&buffer);
            if (SUCCEEDED(hresult))
            {
                m_SourceVoices.push_back(sourceVoice);
            }
        }
    }
}
