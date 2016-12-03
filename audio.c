#include "audio.h"
#include "opcoes.h"

#define NOME_AUDIO "audio/%s.wav"

static SDL_AudioDeviceID deviceId;
static Uint8* wav_buf = NULL;
static Uint32 wav_len, wav_pos;

static bool modo_sinc = false;

/* Reprodução síncrona */
void sn_audio_play(char* nome){

    modo_sinc = true;

    sn_audio_start(nome);

    while(wav_pos < wav_len);

    sn_audio_stop();

    modo_sinc = false;

}

static void sn_audio_callback(void* userdata, Uint8* stream, int stream_len){

    int stream_pos = 0;

    while(stream_pos < stream_len){

        if(wav_pos >= wav_len){

            if(modo_sinc){

                SDL_memset(stream+stream_pos, 0, stream_len-stream_pos);

                return;

            }else{

                wav_pos = 0;

            }

        }

        if(stream_len-stream_pos < wav_len-wav_pos){ // mais áudio do que stream

            SDL_memcpy(stream+stream_pos, wav_buf+wav_pos, stream_len-stream_pos); // preenche stream até o fim

            wav_pos += stream_len-stream_pos;
            stream_pos = stream_len;

        }else{ // mais stream do que áudio

            SDL_memcpy(stream+stream_pos, wav_buf+wav_pos, wav_len-wav_pos); // preenche stream o quanto dá

            stream_pos += wav_len-wav_pos;
            wav_pos = wav_len;

        }

    }

}

/* Reprodução assíncrona */
void sn_audio_start(char* nome){

    char arquivo[50];
    SDL_AudioSpec wav_spec;

    if(!sn_opcoes_som_get() && !modo_sinc) return;

    sprintf(arquivo, NOME_AUDIO, nome);

    if(SDL_LoadWAV(arquivo, &wav_spec, &wav_buf, &wav_len) != NULL){

        if(!sn_opcoes_som_get()){
            SDL_memset(wav_buf, 0, wav_len);
        }

        wav_spec.callback = sn_audio_callback;
        wav_spec.userdata = NULL;

        deviceId = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);

        if(deviceId != 0){

            wav_pos = 0;

            SDL_PauseAudioDevice(deviceId, 0);

            return;

        }

        SDL_FreeWAV(wav_buf);

        wav_buf = NULL;

    }

}


void sn_audio_stop(){

    if(wav_buf){

        SDL_CloseAudioDevice(deviceId);

        SDL_FreeWAV(wav_buf);

        wav_buf = NULL;

    }

}
