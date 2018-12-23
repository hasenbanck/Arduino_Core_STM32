/*
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
//Based on mbed-os/hal/mbed_pinmap_common.c

#include "pinmap.h"
#include "stm32yyxx_ll_gpio.h"

/* Map STM_PIN to LL */
const uint32_t pin_map_ll[16] = {
    LL_GPIO_PIN_0,
    LL_GPIO_PIN_1,
    LL_GPIO_PIN_2,
    LL_GPIO_PIN_3,
    LL_GPIO_PIN_4,
    LL_GPIO_PIN_5,
    LL_GPIO_PIN_6,
    LL_GPIO_PIN_7,
    LL_GPIO_PIN_8,
    LL_GPIO_PIN_9,
    LL_GPIO_PIN_10,
    LL_GPIO_PIN_11,
    LL_GPIO_PIN_12,
    LL_GPIO_PIN_13,
    LL_GPIO_PIN_14,
    LL_GPIO_PIN_15
};

bool pin_in_pinmap(PinName pin, const PinMap *map)
{
  if (pin != (PinName)NC) {
    while (map->pin != NC) {
      if (map->pin == pin) {
        return true;
      }
      map++;
    }
  }
  return false;
}

void *pinmap_find_peripheral(PinName pin, const PinMap *map)
{
  while (map->pin != NC) {
    if (map->pin == pin) {
      return map->peripheral;
    }
    map++;
  }
  return NP;
}

void *pinmap_peripheral(PinName pin, const PinMap *map)
{
  void *peripheral = NP;

  if (pin != (PinName)NC) {
    peripheral = pinmap_find_peripheral(pin, map);
  }
  return peripheral;
}

PinName pinmap_find_pin(void *peripheral, const PinMap *map)
{
  while (map->peripheral != NP) {
    if (map->peripheral == peripheral) {
      return map->pin;
    }
    map++;
  }
  return NC;
}

PinName pinmap_pin(void *peripheral, const PinMap *map)
{
  PinName pin = NC;

  if (peripheral != NP) {
    pin = pinmap_find_pin(peripheral, map);
  }
  return pin;
}

uint32_t pinmap_find_function(PinName pin, const PinMap *map)
{
  while (map->pin != NC) {
    if (map->pin == pin) {
      return map->function;
    }
    map++;
  }
  return (uint32_t)NC;
}

uint32_t pinmap_function(PinName pin, const PinMap *map)
{
  uint32_t function = (uint32_t)NC;

  if (pin != (PinName)NC) {
    function = pinmap_find_function(pin, map);
  }
  return function;
}

// Merge peripherals
void *pinmap_merge_peripheral(void *a, void *b)
{
  // both are the same (inc both NP)
  if (a == b) {
    return a;
  }

  // one (or both) is not set
  if (a == NP) {
    return b;
  }
  if (b == NP) {
    return a;
  }

  // mis-match error case
  return NP;
}
