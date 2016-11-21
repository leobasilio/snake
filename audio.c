#include "audio.h"

void sn_audio_play(char* nome){

    char arquivo[50];
    SDL_AudioSpec wav_spec;
    Uint8* wav_buf;
    Uint32 wav_len;

    sprintf(arquivo, "audio/%s.wav", nome);

    if(SDL_LoadWAV(arquivo, &wav_spec, &wav_buf, &wav_len) != NULL){

        wav_spec.callback = NULL;
        wav_spec.userdata = NULL;

        SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);

        if(deviceId != 0){

            if(SDL_QueueAudio(deviceId, wav_buf, wav_len) == 0){

                SDL_PauseAudioDevice(deviceId, 0);

                while(SDL_GetQueuedAudioSize(deviceId));

            }

            SDL_CloseAudioDevice(deviceId);

        }

        SDL_FreeWAV(wav_buf);

    }

}
