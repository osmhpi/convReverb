#include "CPUconvIdentity.h"

#include <fftw3.h>
#include <math.h>

namespace cpuconv {

		uint32_t identity(float *target, uint32_t targetFrames, float *outputsx, float *outputdx) {

			fftw_plan target_plan_forward, target_plan_backward;

			// FFT buffers
			fftw_complex *targetSignal = new fftw_complex[targetFrames];
			fftw_complex *targetSignalFt = new fftw_complex[targetFrames];
			fftw_complex *targetSignalIft = new fftw_complex[targetFrames];

			// prepare input signal for fft and move it to complex array
			for (int i = 0; i < targetFrames; ++i) {
				targetSignal[i][0] = target[i];
				targetSignal[i][1] = 0.0f;
			}

			// fourrier transform of targetSignal
			target_plan_forward = fftw_plan_dft_1d(targetFrames, targetSignal, targetSignalFt, FFTW_FORWARD, FFTW_ESTIMATE);
			fftw_execute(target_plan_forward);

			// backward fourrier transform on transformed signal
			target_plan_backward = fftw_plan_dft_1d(targetFrames, targetSignalFt, targetSignalIft, FFTW_BACKWARD,
																							FFTW_ESTIMATE);
			fftw_execute(target_plan_backward);

			int diffs = 0;
			for (int i = 0; i < targetFrames; ++i) {

				outputsx[i] = (float) ((targetSignalIft[i][0]) / (float) targetFrames);
				outputdx[i] = (float) ((targetSignalIft[i][0]) / (float) targetFrames);
			}

			delete[] targetSignal;
			delete[] targetSignalFt;
			delete[] targetSignalIft;

			return targetFrames;
		}
}