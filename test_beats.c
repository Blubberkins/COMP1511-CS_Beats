// Assignment 2 20T1 COMP1511: CS bEats
// test_beats.c
//
// This program was written by Aaron Wang (z5308498)
// on 22/4/2020
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
    if (add_note_to_beat(test_beat, 0, 12) != INVALID_OCTAVE) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 3: Rejecting notes that are lower/equal to their previous notes

    add_note_to_beat(test_beat, 5, 5);

    if (add_note_to_beat(test_beat, 4, 6) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 5, 4) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 5, 5) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 4: Checking valid notes aren't counted as invalid

    if (add_note_to_beat(test_beat, 5, 5) != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 5, 6) != VALID_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 9, 10) != VALID_NOTE) {
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

    // Test 2: Counting octaves with no notes of the same octave

    if (count_notes_in_octave(test_beat, 0) != 0) {
        return DOES_NOT_MEET_SPEC;
    }
    if (count_notes_in_octave(test_beat, 2) != 0) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 3: Counting octaves with multiple notes of the same octave

    if (count_notes_in_octave(test_beat, 1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    add_note_to_beat(test_beat, 1, 1);

    if (count_notes_in_octave(test_beat, 1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    add_note_to_beat(test_beat, 1, 2);

    if (count_notes_in_octave(test_beat, 1) != 2) {
        return DOES_NOT_MEET_SPEC;
    }
    
    return MEETS_SPEC;
}

// Test function for `add_beat_to_track`
int test_add_beat_to_track(void){
    // Test 1: ???
    // TODO: Write Test 1

    // Test 2: ???
    // TODO: Write Test 2

    // Test 3: ???
    // TODO: Write Test 3

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
