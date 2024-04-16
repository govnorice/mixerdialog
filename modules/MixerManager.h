//
// Created by diablo on 06.04.24.
//

#ifndef TEST_MIXERMANAGER_H
#define TEST_MIXERMANAGER_H

#include <alsa/asoundlib.h>
#include <iostream>
#include <cmath>

using namespace std;

class MixerManager {
public:
    MixerManager();
    ~MixerManager();

    long increase_volume(float value);
    long decrease_volume(float value);
    float get_volume();
private:
    snd_mixer_t *mixer;
    snd_mixer_selem_id_t *sid;
    const char *card = "default";
    const char *selem_name = "Master";
    long volume, volume_min, volume_max;

    // Получить идентификатор элемента громкости
    snd_mixer_elem_t* get_id_selem();
};


#endif //TEST_MIXERMANAGER_H
