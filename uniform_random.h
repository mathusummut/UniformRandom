#pragma once

#include "limits.h"

#ifdef _WIN32
#include "windows.h"
#else
#include <chrono>
#endif

namespace uniform_random {
	typedef unsigned long long ulong;

	struct seed_generator {
		ulong seeds[56];

		seed_generator() {
			ulong seed = 1389880606230557208ull - time_seed();
			seeds[55] = seed;
			ulong num = 1;
			for (int num1, i = 1; i < 55; i++) {
				num1 = 21 * i % 55;
				seeds[num1] = num;
				num = seed - num;
				seed = seeds[num1];
			}
			int j;
			for (int i = 1; i < 5; i++) {
				for (j = 1; j < 56; j++)
					seeds[j] -= seeds[1 + (j + 30) % 55];
			}
		}

		//Gets a valid time seed.
		static inline ulong time_seed() {
#ifdef _WIN32
			LARGE_INTEGER num;
			QueryPerformanceCounter(&num);
			return num.QuadPart;
#else
			return static_cast<ulong>(std::chrono::high_resolution_clock::now().time_since_epoch().count());
#endif
		}
	};
	
	//The current random value index counter.
	static unsigned int index = 0;
	static seed_generator state;

	//Generates a random integer.
	static inline ulong random() {
		unsigned int curr = ++index % 56;
		ulong value = state.seeds[curr] - state.seeds[(curr + 21) % 56];
		state.seeds[curr] = value;
		return value;
	}

	//Generates a random value in the range [0, 1).
	static inline double random_double() {
		return random() * 5.421010862427522170331137592055280434137021303416885e-20;
	}

	//Returns a random double in the specified range for the specified integer value.
	static inline double to_interval(ulong value, double min, double max) {
		if (min > max) {
			double temp = min;
			min = max;
			max = temp;
		}
		return (value * 5.421010862427522170331137592055280434137021303416885e-20) * (max - min) + min;
	}
}