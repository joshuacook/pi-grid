#include "note_utils.h"
#include <assert.h>

int main(void) {
    // Test corners of an 8x8 grid
    assert(xy_to_note(0, 0) == 0);
    assert(xy_to_note(7, 0) == 7);
    assert(xy_to_note(0, 7) == 112);
    assert(xy_to_note(7, 7) == 119);

    // Test middle
    assert(xy_to_note(3, 4) == 67);

    return 0;
}
