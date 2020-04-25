// Assignment 2 20T1 COMP1511: CS bEats
// beats.c
//
// This program was written by Aaron Wang (z5308498)
// on 22/4/2020
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Fix default return value of add_musical_note_to_beat.

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Add any extra #includes your code needs here.

#include "beats.h"

// Add your own #defines here.

////////////////////////////////////////////////////////////////////////

// You don't have to use the provided struct track, you are free to
// make your own struct instead.
// If you use the provided struct track, you will have to add fields
// to store other information.

struct track {

    // Pointer to the first beat in the track
    struct beat *head;

    // Additions:

    // Pointer to the currently playing beat
    struct beat *current;
    // Number keeping track of how many beats there are in a track
    int num_beats;
};

// You don't have to use the provided struct beat, you are free to
// make your own struct instead.
// If you use the provided struct beat, you may add fields
// to it to store other information.

struct beat {
    // You may choose to add or change fields in this struct.

    // *notes is a pointer to the first note of the beat
    struct note *notes;
    struct beat *next;
};

// You don't have to use the provided struct note, you are free to
// make your own struct instead.
// If you use the provided struct note, you add fields
// to it to store other information.

struct note {
    // You may choose to add or change fields in this struct.
    int octave;
    int key;
    struct note *next;
};

// Add any other structs you define here.

////////////////////////////////////////////////////////////////////////

// Add prototypes for any extra functions you create here.



// Return a malloced Beat with fields initialized.
Beat create_beat(void) {
    Beat new_beat = malloc(sizeof (struct beat));
    assert(new_beat != NULL);

    new_beat->next = NULL;
    new_beat->notes = NULL;

    // You do not need to change this function, unless you change
    // the implementation of struct beat.

    return new_beat;
}

// You need to implement the following functions.
// You can find descriptions of what each function should do in beats.h

////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add a note to the end of a beat.
int add_note_to_beat(Beat beat, int octave, int key) {
    
    // invalid octave
    if (octave < 0 || octave >= 10) {

        return INVALID_OCTAVE;

    // invalid key
    } else if (key < 0 || key >= 12) {

        return INVALID_KEY;

    // the beat contains no notes
    } else if (beat->notes == NULL) {

        // creates new note
        struct note *new_note = malloc(sizeof(struct note));

        new_note->octave = octave;
        new_note->key = key;
        new_note->next = NULL;

        // assigns the first note of the beat to the new note
        beat->notes = new_note;

        return VALID_NOTE;

    } else {
    
        // creates a copy of the pointer to the first note in the beat
        struct note *previous_note = beat->notes;

        // loops through the notes until it reaches the note before
        // the new note (potentially) being created
        while (previous_note->next != NULL) {

            previous_note = previous_note->next;

        }

        if (octave < previous_note->octave) {

            return NOT_HIGHEST_NOTE;

        } else if (octave >= previous_note->octave) {

            if (octave == previous_note->octave && key <= previous_note->key) {

                return NOT_HIGHEST_NOTE;

            // the new note is higher than the previous note
            } else {

                // creates new note
                struct note *new_note = malloc(sizeof(struct note));

                previous_note->next = new_note;

                new_note->octave = octave;
                new_note->key = key;
                new_note->next = NULL;

                return VALID_NOTE;

            }

        }

    }

    return NOT_HIGHEST_NOTE;
}

// Print the contents of a beat.
void print_beat(Beat beat) {

    // creates a copy of the pointer to the first note in the beat
    struct note *print_note = beat->notes;

    // the beat contains no notes
    if (print_note == NULL) {

        printf("\n");

    }
    
    // loop through each note in the beat
    while (print_note != NULL) {

        // while there is a note after the current note
        while (print_note->next != NULL) {

            if (print_note->key < 10) {

                printf("%d 0%d | ", print_note->octave, print_note->key);

            } else {

                printf("%d %d | ", print_note->octave, print_note->key);

            }

            print_note = print_note->next;

        }

        // when it reaches the final note in the beat

        if (print_note->key < 10) {

            printf("%d 0%d\n", print_note->octave, print_note->key);

        } else {

            printf("%d %d\n", print_note->octave, print_note->key);

        }

        // loops the print_note to the final note's 'next', which is NULL
        print_note = print_note->next;

    }

    return;
}

// Count the number of notes in a beat that are in a given octave.
int count_notes_in_octave(Beat beat, int octave) {
    
    // creates a copy of the pointer to the first note in the beat
    struct note *count_note = beat->notes;

    int count = 0;

    // loop through each note in the beat
    while (count_note != NULL) {

        // if the octave of the current note matches the given octave
        if (count_note->octave == octave) {

            count++;

        }

        count_note = count_note->next;

    }

    return count;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

// Return a malloced track with fields initialized.
Track create_track(void) {
    
    Track new_track = malloc(sizeof (struct track));
    assert(new_track != NULL);

    new_track->head = NULL;
    new_track->current = NULL;
    new_track->num_beats = 0;

    return new_track;
}

// Add a beat after the current beat in a track.
void add_beat_to_track(Track track, Beat beat) {
    
    // if there are no beats in the track
    if (track->head == NULL) {

        // Set the first beat of the track to the added beat
        track->head = beat;

        // Add one to the total number of beats in the track
        track->num_beats++;

    // if there are beats in the track and there is no currently selected beat
    } else if (track->current == NULL) {

        // set the added beat's 'next' to the previous first note of the track
        beat->next = track->head;

        // set the added beat as the first note of the track
        track->head = beat;

        // Add one to the total number of beats in the track
        track->num_beats++;

    // if there is a currently selected beat and it is not the last beat
    // in the track
    } else if (track->current->next != NULL) {

        // set the added beat's 'next' to the previous 'next' of the
        // currently selected beat
        beat->next = track->current->next;

        // set the currently selected beat's 'next' to the added beat
        track->current->next = beat;

        // Add one to the total number of beats in the track
        track->num_beats++;

    // the currently selected beat is the last beat in the track
    } else {

        // set the currently selected beat's 'next' to the added beat
        track->current->next = beat;

        // Add one to the total number of beats in the track
        track->num_beats++;

    }

    return;
}

// Set a track's current beat to the next beat.
int select_next_beat(Track track) {

    // if there are no beats in the track
    if (track->head == NULL) {

        return TRACK_STOPPED;

    // if there are beats in the track and there is no currently selected beat
    } else if (track->current == NULL) {

        track->current = track->head;
        return TRACK_PLAYING;

    // if the currently selected beat is the last beat in the track
    } else if (track->current->next == NULL) {

        track->current = NULL;
        return TRACK_STOPPED;

    // if there is a currently selected beat
    } else {

        track->current = track->current->next;
        return TRACK_PLAYING;

    }

}

// Print the contents of a track.
void print_track(Track track) {
    
    // if there are beats in the track
    if (track->head != NULL) {

        int beat_num = 0;

        // creates a copy of the pointer to the first beat of the track
        struct beat *current_print_beat = track->head;

        while (current_print_beat != NULL) {

            if (current_print_beat == track->current) {

                printf(">");

            } else {

                printf(" ");

            }

            beat_num++;
            printf("[%d] ", beat_num);
            print_beat(current_print_beat);
            current_print_beat = current_print_beat->next;

        }

    }

    return;
}

// Count beats after the current beat in a track.
int count_beats_left_in_track(Track track) {

    // if no beat is currently selected (the track is 'stopped')
    if (track->current == NULL) {

        return track->num_beats;

    // a beat is currently selected
    } else {

        // set beats_left to the number of beats in the track
        int beats_left = track->num_beats;

        // creates a copy of the pointer to the first beat of the track
        struct beat *current_beat = track->head;

        // loops through the track until reaching the current beat
        while (current_beat != track->current) {

            // subtracts 1 from beats_left every time it loops to a
            // non-current beat
            beats_left--;
            current_beat = current_beat->next;

        }

        // returns beats_left - 1 as when it exits the loop it does not count
        // the last beat left
        return beats_left - 1;

    }

}

////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

// Free the memory of a beat, and any memory it points to.
void free_beat(Beat beat) {
    // Note: there is no printf in this function, as the
    // Stage 1 & 2 autotests call free_beat but don't check whether
    // the memory has been freed (so this function should do nothing in
    // Stage 1 & 2, rather than exit).
    return;
}

// Free the memory of a track, and any memory it points to.
void free_track(Track track) {
    // Note: there is no printf in this function, as the
    // Stage 1 & 2 autotests call free_track but don't check whether
    // the memory has been freed (so this function should do nothing in
    // Stage 1 & 2, rather than print an error).
    return;
}

// Remove the currently selected beat from a track.
int remove_selected_beat(Track track) {
    printf("remove_selected_beat not implemented yet.");
    return TRACK_STOPPED;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Add note to beat, given its 'musical notation'.
int add_musical_note_to_beat(Beat beat, char *musical_notation) {
    printf("add_musical_note_to_beat not implemented yet.");
    return VALID_NOTE;
}


////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Cut a range of beats to the end of a track.
void cut_range_to_end(Track track, int range_length) {
    printf("cut_range_to_end not implemented yet.");
    return;
}

// Reverse a list of beats within a range of a track.
int reverse_range(Track track, int range_length) {
    printf("reverse_range not implemented yet.");
    return 0;
}
