//Copyright (C) 2018-21 Arc676/Alessandro Vinciguerra <alesvinciguerra@gmail.com>

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3).

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "slow.h"

void slowSort(void** array, int len, int size, COMP_FUNC cmp) {
	if (len < 2) {
		return;
	}
	int half = len / 2;
	slowSort(array, half, size, cmp);
	slowSort(adv(array, half * size), len - half, size, cmp);
	
	void** a = adv(array, (half - 1) * size);
	void** b = adv(array, (len - 1) * size);
	if (cmp(a, b) == 1) {
		swapElements(a, b, size);

		#ifdef VISUALIZER
		visualizer_updateArray(a, 2, size);
		#endif
	}

	slowSort(array, len - 1, size, cmp);
}
