///////////////////////////////////////////////////////////////////////////////
// External Library inclusions
///////////////////////////////////////////////////////////////////////////////
#include "External/Common/Utils.h"
#include "External/WaveFile/WaveFile.h"
///////////////////////////////////////////////////////////////////////////////
// Project inclusions
///////////////////////////////////////////////////////////////////////////////
#include "PcmSound.h"
#include "XAudio2Context.h"
#include "XAudio2Engine.h"
///////////////////////////////////////////////////////////////////////////////


///
/// main - program entry point
///
int main(int args, char* argc[])
{
    UNREFERENCED_PARAMETER(args);
    UNREFERENCED_PARAMETER(argc);

    auto& xAudio2Context = XAudio2Context::CreateXAudio2Context();
    if (!xAudio2Context.IsInitialized())
    {
        Main_Return(-1);
    }

    auto& xAudio2Engine1 = xAudio2Context.CreateXAudio2Engine();
    auto& xAudio2Engine2 = xAudio2Context.CreateXAudio2Engine();

    // Load sounds
    std::list<PcmSound> pcmSounds;
    if (xAudio2Engine1.IsInitialized())
    {
        pcmSounds.push_back(PcmSound(L"%MEDIA_ASSETS_WAVE_SAMPLES%/Bass/Synth/Kurzweil-K2000-Big-Mono-Bass-C1.wav"));
        pcmSounds.back().Attach(xAudio2Engine1);
        pcmSounds.push_back(PcmSound(L"%MEDIA_ASSETS_WAVE_SAMPLES%/Drums/Snare/Yamaha-RM50-Snare-Drum-1.wav"));
        pcmSounds.back().Attach(xAudio2Engine1);
        pcmSounds.push_back(PcmSound(L"%MEDIA_ASSETS_WAVE_SAMPLES%/Guitar/Acoustic/E-Mu-Proteus-FX-AcStereo-C3.wav"));
        pcmSounds.back().Attach(xAudio2Engine1);
        pcmSounds.push_back(PcmSound(L"%MEDIA_ASSETS_WAVE_SAMPLES%/Guitar/Electric/Alesis-S4-Plus-Clean-Gtr-C4.wav"));
        pcmSounds.back().Attach(xAudio2Engine1);
    }

    if (xAudio2Engine2.IsInitialized())
    {
        pcmSounds.push_back(PcmSound(L"%MEDIA_ASSETS_WAVE_SAMPLES%/Orchestral/Woodwinds/Ensoniq-SQ-1-Clarinet-C4.wav"));
        pcmSounds.back().Attach(xAudio2Engine2);
        pcmSounds.push_back(PcmSound(L"%MEDIA_ASSETS_WAVE_SAMPLES%/Synthesizer/Piano/Kurzweil-K2000-Bright-Piano-C6.wav"));
        pcmSounds.back().Attach(xAudio2Engine2);
    }
    
    // Play sounds
    for (auto& pcmSound : pcmSounds)
    {
        pcmSound.Play();
    }

    // Wait until all sounds finish playing
    auto currentPcmSound = begin(pcmSounds);
    while (!pcmSounds.empty())
    {
        if (currentPcmSound->IsPlaying())
        {
            ++currentPcmSound;
            if (pcmSounds.end() == currentPcmSound)
            {
                currentPcmSound = begin(pcmSounds);
            }
        }
        else
        {
            currentPcmSound = pcmSounds.erase(currentPcmSound);
            if (end(pcmSounds) == currentPcmSound)
            {
                currentPcmSound = begin(pcmSounds);
            }
        }

        // Press ESC to exit
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }

        Sleep(5);
    }

    // Return normally
    Main_Return(0);
}
