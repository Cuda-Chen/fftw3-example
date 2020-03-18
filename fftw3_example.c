#include <stdio.h>
#include <math.h>

#include <fftw3.h>

#define N 16

int main()
{
    fftw_complex in[N], out[N], ref[N];
    fftw_plan fft, ifft;
    int i;

    /* prepare a cosine wave */
    for(int i = 0; i < N; i++)
    {
        in[i][0] = cos(3 * 2*M_PI*i/N);
        in[i][1] = 0;
        printf("input: %3d %+9.5f %+9.5f I\n",
                i, in[i][0], in[i][1]);
    }
    printf("\n");

    /* Fourier transform and save result to `out` */
    fft = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(fft);
    for(i = 0; i < N; i++)
    {
        printf("frequency: %3d %+9.5f %+9.5f I\n", i, out[i][0], out[i][1]);
    }
    fftw_destroy_plan(fft);

    /* inverse Fourier transform and save result to `ref` */
    printf("\ninverse transform:\n");
    ifft = fftw_plan_dft_1d(N, out, ref, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(ifft);
    /* normalize */
    for(i = 0; i < N; i++)
    {
        ref[i][0] *= 1./N;
        ref[i][1] *= 1./N;
    }
    for(i = 0; i < N; i++)
    {
        printf("recover: %3d %+9.5f %+9.5f I v.s. %+9.5f %+9.5f I\n",
                i, in[i][0], in[i][1], ref[i][0], ref[i][1]);
    }
    fftw_destroy_plan(ifft);

    fftw_cleanup();

    return 0;
}
