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

    add_note_to_beat(test_beat, 2, 3);

    if (add_note_to_beat(test_beat, 1, 0) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 2, 2) != NOT_HIGHEST_NOTE) {
        return DOES_NOT_MEET_SPEC;
    }
    if (add_note_to_beat(test_beat, 2, 3) != NOT_HIGHEST_NOTE) {
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

    if (count_notes_in_octave(test_beat, 2) != 0) {
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
    Beat test_beatA = create_beat();

    add_note_to_beat(test_beatA, 1, 1);
    add_note_to_beat(test_beatA, 1, 2);

    add_beat_to_track(test_track1, test_beatA);

    // Adding a beat with notes
    if (count_beats_left_in_track(test_track1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    Track test_track2 = create_track();
    Beat test_beatX = create_beat();

    add_beat_to_track(test_track2, test_beatX);

    // Adding a beat with no notes
    if (count_beats_left_in_track(test_track2) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: Adding multiple beats to the track
    
    Beat test_beatB = create_beat();

    // Testing if test_beatA was properly added and its notes were not
    // carried over to test_beatB
    if (count_notes_in_octave(test_beatB, 1) != 0) {
        return DOES_NOT_MEET_SPEC;
    }

    add_beat_to_track(test_track1, test_beatB);

    // Adding a second beat with no notes
    if (count_beats_left_in_track(test_track1) != 2) {
        return DOES_NOT_MEET_SPEC;
    }

    Beat test_beatY = create_beat();

    add_note_to_beat(test_beatY, 1, 1);
    add_note_to_beat(test_beatY, 1, 2);

    add_beat_to_track(test_track2, test_beatY);

    // Adding a second beat with notes
    if (count_beats_left_in_track(test_track2) != 2) {
        return DOES_NOT_MEET_SPEC;
    }

    return MEETS_SPEC;
}

// Test function for `remove_selected_beat`

int test_remove_selected_beat(void) {

    Track test_track1 = create_track();

    // Test 1: Removing a beat with no currently selected beat in the track
    
    Beat test_beat1 = create_beat();
    add_note_to_beat(test_beat1, 1, 1);
    add_beat_to_track(test_track1, test_beat1);
    
    remove_selected_beat(test_track1);

    // track should consist of: beat1
    if (count_beats_left_in_track(test_track1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 2: Removing a beat with the first beat selected in the track
    
    Beat test_beat2 = create_beat();
    add_beat_to_track(test_track1, test_beat2);

    Beat test_beat3 = create_beat();
    add_note_to_beat(test_beat3, 1, 1);
    add_beat_to_track(test_track1, test_beat3);

    select_next_beat(test_track1);

    remove_selected_beat(test_track1);

    // track should consist of: >beat2, beat3 
    // (> indicates this beat is currently selected)
    if (count_beats_left_in_track(test_track1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 3: Removing a beat with the last beat selected in the track
    
    select_next_beat(test_track1);
    
    remove_selected_beat(test_track1);

    // track should consist of: beat2
    if (count_beats_left_in_track(test_track1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

    // Test 4: Removing a beat with the middle beat selected in the track

    Beat test_beat4 = create_beat();
    add_beat_to_track(test_track1, test_beat4);

    Beat test_beat5 = create_beat();
    add_note_to_beat(test_beat5, 1, 1);
    add_beat_to_track(test_track1, test_beat5);

    Beat test_beat6 = create_beat();
    add_beat_to_track(test_track1, test_beat6);

    select_next_beat(test_track1);
    select_next_beat(test_track1);

    remove_selected_beat(test_track1);

    // track should consist of: beat2, >beat5, beat6
    if (count_beats_left_in_track(test_track1) != 1) {
        return DOES_NOT_MEET_SPEC;
    }

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