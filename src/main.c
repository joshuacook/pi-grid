#include <stdio.h>

#if defined(HAVE_LIBMONOME) && defined(HAVE_ALSA)
#include <monome.h>
#include <alsa/asoundlib.h>

static snd_seq_t *seq;
static int out_port;

static int xy_to_note(int x, int y) {
    return y * 16 + x;
}

static void send_note(int note, int velocity) {
    snd_seq_event_t ev;
    snd_seq_ev_clear(&ev);
    snd_seq_ev_set_source(&ev, out_port);
    snd_seq_ev_set_subs(&ev);
    snd_seq_ev_set_direct(&ev);
    if (velocity) {
        snd_seq_ev_set_noteon(&ev, 9, note, velocity);
    } else {
        snd_seq_ev_set_noteoff(&ev, 9, note, 0);
    }
    snd_seq_event_output(seq, &ev);
    snd_seq_drain_output(seq);
}

static int handle_grid(const monome_event_t *e, void *data) {
    int note = xy_to_note(e->grid.x, e->grid.y);
    if (e->event_type == MONOME_BUTTON_DOWN) {
        send_note(note, 100);
    } else if (e->event_type == MONOME_BUTTON_UP) {
        send_note(note, 0);
    }
    return 0;
}

int main(void) {
    if (snd_seq_open(&seq, "default", SND_SEQ_OPEN_OUTPUT, 0) < 0) {
        fprintf(stderr, "Failed to open ALSA sequencer\n");
        return 1;
    }
    snd_seq_set_client_name(seq, "pi-grid");
    out_port = snd_seq_create_simple_port(seq, "out",
        SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ,
        SND_SEQ_PORT_TYPE_MIDI_GENERIC|SND_SEQ_PORT_TYPE_APPLICATION);
    if (out_port < 0) {
        fprintf(stderr, "Failed to create MIDI port\n");
        return 1;
    }

    monome_t *monome = monome_open(NULL);
    if (!monome) {
        fprintf(stderr, "Unable to open monome\n");
        return 1;
    }

    monome_register_handler(monome, MONOME_BUTTON_DOWN, handle_grid, NULL);
    monome_register_handler(monome, MONOME_BUTTON_UP, handle_grid, NULL);
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
