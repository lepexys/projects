#include "pch.h"
#include <iostream>
#include <cstdint>
#include <cmath>
#include <Windows.h>
#include <list>

constexpr auto wav_size = 24000; 
constexpr auto duration = 5 ;
constexpr auto pi = 3.141592653589793238462643383279;

struct signal
{
	double dest_time, //Рассчитанное время прибытия сигнала 
		power; //сила сигнала
	signal(double d,double p)
	{
		dest_time = d;
		power = p;
	}
};
typedef struct  WAV_HEADER
{
	/* RIFF Chunk Descriptor */
	uint8_t         RIFF[4];        // RIFF Header Magic header
	uint32_t        ChunkSize;      // RIFF Chunk Size
	uint8_t         WAVE[4];        // WAVE Header
	/* "fmt" sub-chunk */
	uint8_t         fmt[4];         // FMT header
	uint32_t        Subchunk1Size;  // Size of the fmt chunk
	uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
	uint16_t        NumOfChan;      // Number of channels 1=Mono 2=Sterio
	uint32_t        SamplesPerSec;  // Sampling Frequency in Hz
	uint32_t        bytesPerSec;    // bytes per second
	uint16_t        blockAlign;     // 2=16-bit mono, 4=16-bit stereo
	uint16_t        bitsPerSample;  // Number of bits per sample
	/* "data" sub-chunk */
	uint8_t         Subchunk2ID[4]; // "data"  string
	uint32_t        Subchunk2Size;  // Sampled data length
} wav_hdr;

void CreateWavFile(const char* filePath, const double* Amplitude, int VectorSize)
{
	int16_t Data;
	wav_hdr wavHeader;
	wavHeader.RIFF[0] = 'R'; wavHeader.RIFF[1] = 'I'; wavHeader.RIFF[2] = 'F'; wavHeader.RIFF[3] = 'F';
	wavHeader.WAVE[0] = 'W'; wavHeader.WAVE[1] = 'A'; wavHeader.WAVE[2] = 'V'; wavHeader.WAVE[3] = 'E';
	wavHeader.fmt[0] = 'f';  wavHeader.fmt[1] = 'm';  wavHeader.fmt[2] = 't';  wavHeader.fmt[3] = ' ';
	wavHeader.Subchunk2ID[0] = 'd'; wavHeader.Subchunk2ID[1] = 'a'; wavHeader.Subchunk2ID[2] = 't'; wavHeader.Subchunk2ID[3] = 'a';
	wavHeader.Subchunk1Size = 16;
	wavHeader.AudioFormat = 1;
	wavHeader.NumOfChan = 2;
	wavHeader.bitsPerSample = 16;
	wavHeader.SamplesPerSec = wav_size/2;
	wavHeader.bytesPerSec = wavHeader.SamplesPerSec * wavHeader.NumOfChan*wavHeader.bitsPerSample/8;
	wavHeader.blockAlign = wavHeader.NumOfChan * 2;
	wavHeader.Subchunk2Size = 2 * VectorSize * wavHeader.blockAlign;
	wavHeader.ChunkSize = sizeof(wav_hdr) - 8 + wavHeader.Subchunk2Size;
	size_t headerSize = sizeof(wav_hdr);

	FILE* wavFile = fopen(filePath, "wb"); 
	
	fwrite(&wavHeader, 1, headerSize, wavFile);   
	for (int i = 0; i < VectorSize; i++)
	{
		Data = int16_t(Amplitude[i]);
		fwrite(&Data, 2, 1, wavFile);
	}
	fclose(wavFile);
}

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	list<signal*> rtimes,ltimes; //два списка сигналов для каждого уха
	double data[wav_size * duration],
		eardistance = 0.204, //Расстояние между ушами
		sos = 340.29, //Скорость звука
		thingdist, //Расстояние до источника звука(от центра "головы")
		som, //Скорость источника звука
		sod = (double)1 / (wav_size/2), //скорость дискретизации
		x = 0.0, y = 0.0, //координаты источника звука 
		freq, //Угловая скорость
		ang, //фаза вращения для источника звука
		cur_time, //текущее время
		power, //сила посланного сигнала
		dist; // Расстояние до источника звука от приёмника
	while (true)
	{
		cout << "Enter the ditance between center of a head and a sound source in centimeters: "; //Задаётся расстояние до источника звука
		cin >> thingdist;
		if (cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
		{
			thingdist /= 100.0;
			break;
		}
	}
	while (true)
	{
		cout << "Enter the speed of sound source in meters per second: ";//Задаётся скорость источника звука
		cin >> som;
		if (cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
			break;
	}
	y = thingdist;
	freq = (double)som / thingdist;
	ang = (double)pi / 2 + freq * (double)sod / 2;
	for (int i = 0; i < wav_size * duration; i += 2)
	{
		cur_time = (double)(sod * (i + 1)) / 2;
		power = sin(cur_time*261.626*pi * 2);
		ang += sod * freq;
		x = sin(ang);
		y = cos(ang);
		dist = cur_time + (double)sqrt(pow(x + (double)eardistance / 2, 2) + pow(y, 2)) / sos; // рассчёт времени, в которое сигнал достигнет приёмника
		signal *sl = new signal(dist, power);
		ltimes.push_back(sl); // запись в список сигналов
		dist = cur_time + (double)sqrt(pow(x - (double)eardistance / 2, 2) + pow(y, 2)) / sos;
		signal *sr = new signal(dist, power);
		rtimes.push_back(sr);
		data[i] = NULL;
		data[i + 1] = NULL;
			signal *lb1 = nullptr, *lb2 = nullptr, *rb1 = nullptr, *rb2 = nullptr; 
			for (auto j = rtimes.begin(); j != rtimes.end(); j++) //если в некотором промежутке времени пришло несколько сигналов, то запоминаем два ближайших к центру
			{
				if (abs((*j)->dest_time - cur_time) <= (double)sod / 2)
				{
					if (rb1 == nullptr)
					{
						rb1 = *j;
						j = rtimes.erase(j);
					}
					else
					{
						if (rb2 == nullptr)
						{
							rb2 = *j;
							j = rtimes.erase(j);
						}
						else
							if (abs(((double)(rb2->dest_time + rb1->dest_time) / 2) - cur_time) > abs(((double)(rb2->dest_time + (*j)->dest_time) / 2) - cur_time))
							{
								rb1 = rb2;
								rb2 = *j;
								j = rtimes.erase(j);
							}
					}
				}
			}
			for (auto j = ltimes.begin(); j != ltimes.end(); j++)
			{
				if (abs((*j)->dest_time - cur_time) <= (double)sod / 2)
				{
					if (lb1 == nullptr)
					{
						lb1 = *j;
						j = ltimes.erase(j);
					}
					else
					{
						if (lb2 == nullptr)
						{
							lb2 = *j;
							j = ltimes.erase(j);
						}
						else
							if (abs(((double)(lb2->dest_time + lb1->dest_time) / 2) - cur_time) > abs(((double)(lb2->dest_time + (*j)->dest_time) / 2) - cur_time))
							{
								lb1 = lb2;
								lb2 = *j;
								j = ltimes.erase(j);
							}
					}
				}
			}
			if (rb1 != nullptr)
			{
				if (rb2 == nullptr)
				{
					data[i] = (10000.0 - (((cos(ang) > 0) ? cos(ang) : 0) * 3000)) * rb1->power;
				}
				else
				{
					data[i] = (10000.0 - (((cos(ang) > 0) ? cos(ang) : 0) * 3000)) * (((double)(rb2->dest_time - rb1->dest_time) / (rb2->dest_time - rb1->dest_time))*(cur_time - rb1->dest_time) + rb1->power);
				}
			}
			else
				data[i] = 0;
			if (lb1 != nullptr)
			{
				if (lb2 == nullptr)
				{
					data[i + 1] = (10000.0 + (((cos(ang) < 0) ? cos(ang) : 0) * 3000)) * lb1->power;
				}
				else
				{
					data[i + 1] = (10000.0 + (((cos(ang) < 0) ? cos(ang) : 0) * 3000)) * (((double)(lb2->dest_time - lb1->dest_time) / (lb2->dest_time - lb1->dest_time))*(cur_time - lb1->dest_time) + lb1->power);
				}
			}
			else
				data[i+1] = 0;
		if (i > 1) //Алгоритм сглаживания сигнала для избежания скачков
		{
			if (data[i - 1] == 0 && data[i + 1] != 0)
			{
				int j = i - 1;
				while (j > 1 && data[j] == 0)
					j -= 2;
				if (data[j] != 0)
				{
					double add = (double)(data[i + 1] - data[j]) / ((i + 1 - j) / 2);
					j += 2;
					while (j < i)
					{
						data[j] = data[j - 2] + add;
						j += 2;
					}
				}
			}
			if (data[i - 2] == 0 && data[i] != 0)
			{
				int j = i - 2;
				while (j > 0 && data[j] == 0)
					j -= 2;
				if (data[j] != 0)
				{
					double add = (double)(data[i] - data[j]) / ((i - j) / 2);
					j += 2;
					while (j < i)
					{
						data[j] = data[j - 2] + add;
						j += 2;
					}
				}
			}
		}
	}
	CreateWavFile("test.wav", data, wav_size * duration);
	return NULL;
}