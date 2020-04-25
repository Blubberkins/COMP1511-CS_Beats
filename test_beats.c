// Assignment 2 20T1 COMP1511: CS bEats
// test_beats.c
//
// This program was written by Aaron Wang (z5308498)
// on 23/4/2020
//
// Version 1.0.0: Assignment released.
#include <stdio.h>
#include <stdlib.h>

#include "test_beats.h"
#include "beats.h"


// Test function for `add_note_to_beat`

int test_add_note_to_beat(void) {

    // Test 1: Rejecting negative inputs.

    Beat test_beat = create_beat();

    if (add_note_to_beat(test_beat, -1, -1) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, -1, 0) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 1, -1) != INVALID_KEY) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: Rejecting octave and key inputs greater than their max values

    if (add_note_to_beat(test_beat, 10, 12) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 10, 0) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 0, 12) != INVALID_KEY) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 3: Rejecting inputs that are lower/equal to the previous note

    add_note_to_beat(test_beat, 2, 2);

    if (add_note_to_beat(test_beat, 1, 0) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 1, 1) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 2, 1) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 4: Accepting valid inputs

    if (add_note_to_beat(test_beat, 2, 5) != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 3, 9) != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 9, 0) != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }

    return MEETS_SPEC;
}

// Test function for `count_notes_in_octave`

int test_count_notes_in_octave(void) {

    // Test 1: Counting invalid octaves.

    Beat test_beat = create_beat();

    add_note_to_beat(test_beat, 1, 1);

    if (count_notes_in_octave(test_beat, -1) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 11) != 0) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: Counting valid octaves with one note of the same octave.

    add_note_to_beat(test_beat, 3, 3);

    if (count_notes_in_octave(test_beat, 2) != 1) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 3) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 3: Counting valid octaves with multiple notes of the same octave.

    add_note_to_beat(test_beat, 3, 4);
    add_note_to_beat(test_beat, 4, 1);
    add_note_to_beat(test_beat, 4, 2);
    add_note_to_beat(test_beat, 4, 3);

    if (count_notes_in_octave(test_beat, 3) != 2) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 4) != 3) {
        return DOES_NOT_MEET_SPEC;
    }

    return MEETS_SPEC;
}

// Test function for `add_beat_to_track`

int test_add_beat_to_track(void) {

    // Test 1: Adding beats to track when there are no beats in the track
    
    Track test_track1 = create_track();
    Beat test_beat1 = create_beat();

    add_note_to_beat(test_beat1, 1, 1);
    add_note_to_beat(test_beat1, 1, 2);

    add_beat_to_track(test_track1, test_beat1);

    // Adding a beat with notes
    if (count_beats_left_in_track(test_track1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    Track test_track2 = create_track();
    Beat test_beat2 = create_beat();

    add_beat_to_track(test_track2, test_beat2);

    // Adding a beat with no notes
    if (count_beats_left_in_track(test_track2) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: Adding multiple beats to the track
    
    Beat test_beat3 = create_beat();

    add_beat_to_track(test_track1, test_beat3);

    // Adding a second beat with no notes
    if (count_beats_left_in_track(test_track1) != 2) {
        return DOES_NOT_MEET_SPEC;
    }

    Beat test_beat4 = create_beat();

    add_note_to_beat(test_beat4, 1, 1);
    add_note_to_beat(test_beat4, 1, 2);

    add_beat_to_track(test_track2, test_beat4);

    // Adding a second beat with notes
    if (count_beats_left_in_track(test_track2) != 2) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 3: Adding beats to track when there is a currently selected beat
    // and it is not the last beat in the track
    // TODO: Write Test 3

    // Test 4: Adding beats to track when the currently selected beat
    // is the last beat in the track

    return MEETS_SPEC;
}

// Test function for `remove_selected_beat`
int test_remove_selected_beat(void){
    // Test 1: ???
    // TODO: Write Test 1

    // Test 2: ???
    // TODO: Write Test 2

    // Test 3: ???
    // TODO: Write Test 3

    return MEETS_SPEC;
}

// Test function for `add_musical_note_to_beat`
int test_add_musical_note_to_beat(void){
    // Test 1: ???
    // TODO: Write Test 1

    // Test 2: ???
    // TODO: Write Test 2

    // Test 3: ???
    // TODO: Write Test 3

    return MEETS_SPEC;
}