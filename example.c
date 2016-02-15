/**
 * Konker's ultrathin LED matrix library
 *
 * A library for driving the Seeedstudio Ultrathin red LED matrix
 *
 * Copyright 2015, Konrad Markus <konker@luxvelocitas.com>
 *
 * This file is part of konker_ultrathin_led_matrix.
 *
 * konker_ultrathin_led_matrix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * konker_ultrathin_led_matrix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with konker_ultrathin_led_matrix.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "kulm_matrix.h"
#include "kulm_segment.h"
#include "hexfont_iso-8859-15.h"

#define EXAMPLE_MATRIX_WIDTH 32
#define EXAMPLE_MATRIX_HEIGHT 16

#define EXAMPLE_A 0
#define EXAMPLE_B 2
#define EXAMPLE_C 3
#define EXAMPLE_D 12
#define EXAMPLE_OE 13
#define EXAMPLE_R1 14
#define EXAMPLE_STB 21
#define EXAMPLE_CLK 22

#ifdef NON_GPIO_MACHINE
#   define EXAMPLE_TEXT_SPEED1 2.20
#   define EXAMPLE_TEXT_SPEED2 4.20
#else
#   define EXAMPLE_TEXT_SPEED1 0.002
#   define EXAMPLE_TEXT_SPEED2 0.004
#endif


int main() {
    printf("Konker's Ultrathin LED Matrix library\n");

    // Initialize WirinPi if necessary
#ifndef ARDUINO
#  ifndef NON_GPIO_MACHINE
    if (wiringPiSetup()) {
        printf("ERROR Initializing WiringPi. Exiting.");
        return -1;
    }
#  endif
#endif
    uint8_t example_display_buffer[
        KULM_BUFFER_LEN(EXAMPLE_MATRIX_WIDTH, EXAMPLE_MATRIX_HEIGHT)];

    // Create a matrix
    kulm_matrix *example_matrix =
                    kulm_mat_create(
                            example_display_buffer,
                            EXAMPLE_MATRIX_WIDTH,
                            EXAMPLE_MATRIX_HEIGHT,
                            EXAMPLE_A,
                            EXAMPLE_B,
                            EXAMPLE_C,
                            EXAMPLE_D,
                            EXAMPLE_OE,
                            EXAMPLE_R1,
                            EXAMPLE_STB,
                            EXAMPLE_CLK);

    // Initialize some font(s)
    hexfont * const example_font = hexfont_load_data(hexfont_iso_8859_15, 16);

    // Create a font list
    hexfont_list * const example_font_list = hexfont_list_create(NULL);

    // Add the font to the font list
    hexfont_list_append(example_font_list, example_font);

    // Create some segments
    kulm_segment * const example_segment0 =
                            kulm_seg_create(
                                        example_matrix,
                                        0,
                                        0,
                                        EXAMPLE_MATRIX_WIDTH/2,
                                        EXAMPLE_MATRIX_HEIGHT,
                                        0);

    kulm_segment * const example_segment1 =
                            kulm_seg_create(
                                        example_matrix,
                                        EXAMPLE_MATRIX_WIDTH/2 + 4,
                                        0,
                                        EXAMPLE_MATRIX_WIDTH/2 - 4,
                                        EXAMPLE_MATRIX_HEIGHT,
                                        0);

    // Create a segments list
    kulm_segment_list * const example_segment_list = kulm_segment_list_create(NULL);

    // Add the segments to the segment list
    kulm_segment_list_append(example_segment_list, example_segment0);
    kulm_segment_list_append(example_segment_list, example_segment1);

    // Initialize the matrix with the example segments and fonts
    kulm_mat_init(
            example_matrix,
            example_font_list,
            example_segment_list);

    // Set some text in segment 0
    kulm_seg_set_text(example_segment0, "HELLO");
    kulm_seg_set_text_speed(example_segment0, -EXAMPLE_TEXT_SPEED1);

    // Set some text in segment 1
    kulm_seg_set_text(example_segment1, "WORLD!");
    kulm_seg_set_text_speed(example_segment1, EXAMPLE_TEXT_SPEED2);

    // Call the animation driver for a while
    int16_t j = 0;
    for (j=0; j<50000; j++) {
        // Update the animation
        kulm_mat_tick(example_matrix);

        // Call the display driver for one row
        kulm_mat_scan(example_matrix);

#ifdef NON_GPIO_MACHINE
        kulm_mat_dump_buffer(example_matrix, stdout);
        sleep(1);
#endif
    }

    // Clean up the matrix
    kulm_mat_destroy(example_matrix);

    printf("Goodbye\n");
    return EXIT_SUCCESS;
}

