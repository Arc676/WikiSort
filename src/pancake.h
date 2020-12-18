//Copyright (C) 2019-20 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3).

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PANCAKE_H
#define PANCAKE_H

#include "tim.h"

void pancakeSort(void** array, int len, int size, COMP_FUNC cmp);

#endif

#ifdef __cplusplus
}
#endif
