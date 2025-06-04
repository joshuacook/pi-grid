#include <stdio.h>
#include <time.h>

#if defined(HAVE_LIBMONOME) && defined(HAVE_ALSA)
#include "note_utils.h"
#include <alsa/asoundlib.h>
#include <monome.h>

static snd_seq_t *seq;
static int out_port;
static int midi_channel = 9;

static struct timespec last_press[128];
static struct timespec corner_down[4];
static int channel_mode = 0;

static void send_note(int note, int velocity) {
    snd_seq_event_t ev;
    snd_seq_ev_clear(&ev);
    snd_seq_ev_set_source(&ev, out_port);
    snd_seq_ev_set_subs(&ev);
    snd_seq_ev_set_direct(&ev);
    if (velocity) {
        snd_seq_ev_set_noteon(&ev, midi_channel, note, velocity);
    } else {
        snd_seq_ev_set_noteoff(&ev, midi_channel, note, 0);
    }
    snd_seq_event_output(seq, &ev);
    snd_seq_drain_output(seq);
}

static long diff_ms(struct timespec *a, struct timespec *b) {
    return (b->tv_sec - a->tv_sec) * 1000 + (b->tv_nsec - a->tv_nsec) / 1000000;
}

static int is_corner(int x, int y) {
    return ((x == 0 || x == 7) && (y == 0 || y == 7));
}

static int handle_grid(const monome_event_t *e, void *data) {
    int note = xy_to_note(e->grid.x, e->grid.y);
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    if (e->event_type == MONOME_BUTTON_DOWN) {
        if (is_corner(e->grid.x, e->grid.y)) {
            corner_down[(e->grid.y ? 2 : 0) + (e->grid.x ? 1 : 0)] = now;
        }

        if (channel_mode) {
            midi_channel = note % 16;
            channel_mode = 0;
            return 0;
        }

        long delta = diff_ms(&last_press[note], &now);
        int velocity = 90;
        if (delta < 200)
            velocity = 120;
        else if (delta > 1000)
            velocity = 30;
        last_press[note] = now;

        monome_led_set((monome_t *)data, e->grid.x, e->grid.y, 1);
        send_note(note, velocity);
    } else if (e->event_type == MONOME_BUTTON_UP) {
        monome_led_set((monome_t *)data, e->grid.x, e->grid.y, 0);
        send_note(note, 0);

        if (is_corner(e->grid.x, e->grid.y)) {
            long held = diff_ms(&corner_down[(e->grid.y ? 2 : 0) + (e->grid.x ? 1 : 0)], &now);
            if (held > 1000)
                channel_mode = 1;
        }
    }
    return 0;
}

int main(void) {
    if (snd_seq_open(&seq, "default", SND_SEQ_OPEN_OUTPUT, 0) < 0) {
        fprintf(stderr, "Failed to open ALSA sequencer\n");
        return 1;
    }
    snd_seq_set_client_name(seq, "pi-grid");
    out_port = snd_seq_create_simple_port(
        seq, "out", SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ,
        SND_SEQ_PORT_TYPE_MIDI_GENERIC | SND_SEQ_PORT_TYPE_APPLICATION);
    if (out_port < 0) {
        fprintf(stderr, "Failed to create MIDI port\n");
        return 1;
    }

    monome_t *monome = monome_open(NULL);
    if (!monome) {
        fprintf(stderr, "Unable to open monome\n");
        return 1;
    }

    monome_register_handler(monome, MONOME_BUTTON_DOWN, handle_grid, monome);
    monome_register_handler(monome, MONOME_BUTTON_UP, handle_grid, monome);
    monome_event_loop(monome);

    monome_close(monome);
    snd_seq_close(seq);
    return 0;
}

#else

int main(void) {
    puts("hello");
    return 0;
}

#endif
