//
// Created by diablo on 06.04.24.
//

#include "MixerManager.h"

MixerManager::MixerManager() {
    // Открытие устройства ALSA
    if (snd_mixer_open(&mixer, 0) != 0) {
        cout << "Error opened mixer" << endl;
    }

    // Инициализация управления элементом (элемент громкости)
    snd_mixer_attach(mixer, card);
    snd_mixer_selem_register(mixer, NULL, NULL);
    snd_mixer_load(mixer);
}

MixerManager::~MixerManager() {
    snd_mixer_close(mixer);
}

snd_mixer_elem_t *MixerManager::get_id_selem() {
    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    return snd_mixer_find_selem(mixer, sid);
}

//int MixerManager::get_mixer_range_volume() {
//    return snd_mixer_selem_get_playback_volume_range(MixerManager::get_id_selem(), &volume_min, &volume_max);
//}
//
//int MixerManager::get_mixer_volume() {
//    return snd_mixer_selem_get_playback_volume(MixerManager::get_id_selem(), SND_MIXER_SCHN_MONO, &volume);
//}

long MixerManager::increase_volume(float value) {
    // Получить минимальное и максимальное значения громкости
    snd_mixer_selem_get_playback_volume_range(MixerManager::get_id_selem(), &volume_min, &volume_max);
    // Получить текущее значение громкости
    snd_mixer_selem_get_playback_volume(MixerManager::get_id_selem(), SND_MIXER_SCHN_MONO, &volume);

    volume += value * (volume_max - volume_min);

    // Если громкость привышает максимум
    if (volume > volume_max) {
        volume = volume_max;
    }

    // Установка нового значения громкости
    snd_mixer_selem_set_playback_volume_all(MixerManager::get_id_selem(), volume);

    return volume;
}

long MixerManager::decrease_volume(float value) {
    snd_mixer_selem_get_playback_volume_range(MixerManager::get_id_selem(), &volume_min, &volume_max);
    snd_mixer_selem_get_playback_volume(MixerManager::get_id_selem(), SND_MIXER_SCHN_MONO, &volume);
    volume -= value * (volume_max - volume_min);
    if (volume < volume_min) {
        volume = volume_min;
    }
    snd_mixer_selem_set_playback_volume_all(MixerManager::get_id_selem(), volume);

    return volume;
}

float MixerManager::get_volume() {
    snd_mixer_selem_get_playback_volume_range(MixerManager::get_id_selem(), &volume_min, &volume_max);
    snd_mixer_selem_get_playback_volume(MixerManager::get_id_selem(), SND_MIXER_SCHN_MONO, &volume);

    if (volume_min == volume_max) {
        std::cerr << "Volume min and max are equal, cannot scale" << std::endl;
        return -1.0; // Или другое значение, которое указывает на ошибку
    }

    // Масштабировать значение громкости в диапазон от 0 до 1
    float scaled_volume = static_cast<float>(volume - volume_min) / (volume_max - volume_min);

    // Масштабировать значение громкости в диапазон от 0.1 до 1.0
    float scaled_value = scaled_volume * (1.0f - 0.1f) + 0.1f;

    // Округляем до 1 знака после запятой
    scaled_value = floor(scaled_value * 10) / 10;

    cout << volume << endl;
    cout << volume_min << endl;
    cout << volume_max << endl;
    cout << scaled_value << endl;

    return scaled_value;
}