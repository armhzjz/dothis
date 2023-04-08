#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ao/ao.h>
#include <math.h>

#define M_PI 3.14159265358979323846

int main (int argc, char *argv[]) {
    printf("argc = %d\n", argc);
    for(int x=0; x<argc; x++) {
        printf("argv[%i]: %s\n", x, argv[x]);
    }

    time_t t = time(NULL);
    if(t != (time_t)(-1))
        printf("The current time is %s(%jd seconds since the Epoch)\n",
            asctime(gmtime(&t)), (__intmax_t)t);
    printf("\n\n");
    struct tm tm = *localtime(&t);
    printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


    ao_initialize();
    ao_device *device;
    ao_sample_format format;
    char *buffer;
    int default_driver;
    int buf_size;
    int sample;
    float freq = 440.0;
    /* set up the default driver */
    default_driver = ao_default_driver_id();
    if(default_driver == -1) {
        fprintf(stderr, "Could not find a sound device or the sound device is already in use");
        return 1;
    }
    memset(&format, 0, sizeof(format));
    format.bits = 16;
    format.channels = 2;
    format.rate = 44100;
    format.byte_format = AO_FMT_LITTLE;
    /* open driver */
    device = ao_open_live(default_driver, &format, NULL /* no options */);
    if (device == NULL) {
        fprintf(stderr, "Error opening device.n");
        return 1;
    }
    /* Play some stuff */
    buf_size = format.bits/8 * format.channels * format.rate;
    buffer = calloc(buf_size, sizeof(char));
    for(int i=0;i<format.rate;i++) {
        sample = (int)(0.75 * 32768.0 * sin(2* M_PI *freq*((float)i/format.rate)));
        /* put the same stuff in left and right channel */
        buffer[4*i] = buffer[4*i+2] = sample & 0xff;
        buffer[4*i+1] = buffer[4*i+3] = (sample >> 8) & 0xff;
    }
    ao_play(device, buffer, buf_size);
    /* close and shutdown */

    ao_close(device);
    free(buffer);
    ao_shutdown();
    
    return 0;
}