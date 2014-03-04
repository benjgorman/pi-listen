/*

VisAural - Sample usb microphone in order to visualise sounds for hearing impaired indivudals

*/


#define ALSA_PCM_NEW_HW_PARAMS_API

#include <alsa/asoundlib.h>

int main ()
{

	long loops;
	int capture;
	int size;
	snd_pcm_t *handle;
	snd_pcm_hw_params_t *params;
	unsigned int val;
	int dir;
	snd_pcm_uframes_t frames;
	char *buffer;


	/* Open PCM device (microphone) for recording (capture) */


	capture = snd_pcm_open(&handle, "default:CARD=CameraB409241", SND_PCM_STREAM_CAPTURE, 0)

	if (capture < 0)
	{
		fprintf(stderr, "Unable to open pcm device: %s\n", snd_strerror(rc));
		exit(1);
	}
	

	/* Allocate a hardware parameters object */
	snd_pcm_hw_params_alloca(&params);

	/* Fill it with the default values. */
	snd_pcm_hw_params_any(handle, params);

	/* set the desired hardware parameters */


	/* Non Interleaved mode */

	snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RAW_INTERLEAVED);

	/* Singed 16-bit little-endian format */
	snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);

	/* Four Channels */
	snd_pcm_hw_params_set_channels(handle, params, 4);

	/* 44100 bits/second sampling rate CD Quality */
	val = 44100;
	snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);

	/* Set period size to 32 frames */
	frames = 32;
	snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);

	capture = snd_pcm_hw_params(handle, params);

	if (capture < 0)
	{
		fprintf(stderr, "Unable to set hw parameters %s\n", snd_strerror(capture));
		exit(1);
	}


	snd_pcm_params_get_period_size(params, &frames, &dir);

	size = frames *8; /* 2 bytes/sample, 4 channels */

	buffer = (char *) malloc(size);

	snd_pcm_hw_params_get_period_time(params, &val, &dir);

	loops = 5000000 / val;

	while (loops > 0)
	{
		loops--;
		capture = send_pcm_readi(handle, buffer, frames);

		if (capture == -EPIPE)
		{
			fprintf(stderr, "overrun occured");
			snd_pcm_prepare(handle);
		}
		else if (capture <0)
		{
			fprintf(stderr, "error from read: %s\n", snd_strerror(capture));
		}
		else if(capture != (int)frames)
		{
			fprintf(stderr, "short read, read %d frames\n", capture);
		}

		/* do something here with the period in the buffer 

		

		*/

		printf("HERE IS WHERE I WILL DO STUFF");

	}


snd_pcm_drain(handle);
snd_pcm_close(handle);
free(buffer);



}