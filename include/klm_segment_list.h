/**
 * Konker's LED matrix library
 *
 * A library for driving a red LED matrix
 *
 * Copyright 2015, Konrad Markus <konker@luxvelocitas.com>
 *
 * This file is part of konker_led_matrix.
 *
 * konker_led_matrix is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * konker_led_matrix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with konker_led_matrix.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __KONKER_LED_SEGMENT_LIST_H__
#define __KONKER_LED_SEGMENT_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include "klm_segment.h"


/**
 * A singly linked list of segments
 */
typedef struct klm_segment_list
{
    klm_segment * item;
    struct klm_segment_list *next;

} klm_segment_list;


klm_segment_list * const klm_segment_list_create(klm_segment * const item);
void klm_segment_list_destroy(klm_segment_list * const head);
void klm_segment_list_append(klm_segment_list * const head, klm_segment * const new_item);

uint16_t klm_segment_list_get_length(klm_segment_list * const head);
klm_segment * const klm_segment_list_get_nth(klm_segment_list * const head, int16_t n);

#ifdef __cplusplus
}
#endif

#endif // __KONKER_LED_SEGMENT_LIST_H__
