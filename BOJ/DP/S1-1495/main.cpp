
#include <iostream>

#define MAX_VOLUME (1001U)
#define MAX_SONGS_COUNT (51)

static bool sbSongVolumes[MAX_SONGS_COUNT][MAX_VOLUME] = { false, };

int main()
{
    unsigned int songsCount = 0;
    unsigned int startVolume = 0;
    int maxVolume = 0;

    std::cin >> songsCount >> startVolume >> maxVolume;

    sbSongVolumes[0][startVolume] = true;
    for (unsigned int song = 1; song <= songsCount; ++song)
    {
        unsigned int songVolume = 0;
        std::cin >> songVolume;
        
        unsigned int lastSong = song - 1;
        for (int volume = 0; volume <= maxVolume; ++volume)
        {
            if (sbSongVolumes[lastSong][volume] == false)
            {
                continue;
            }

            int nextVolume = volume + songVolume;
            if (nextVolume <= maxVolume)
            {
                sbSongVolumes[song][nextVolume] = true;
            }

            nextVolume = volume - songVolume;
            if (nextVolume >= 0)
            {
                sbSongVolumes[song][nextVolume] = true;
            }
        }
    }
    
    int printVolume = -1;
    for (int volume = maxVolume; volume >= 0; --volume)
    {
        if (sbSongVolumes[songsCount][volume])
        {
            printVolume = volume;

            break;
        }
    }

    std::cout << printVolume;

    return 0;
}