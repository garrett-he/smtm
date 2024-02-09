/**
 * Copyright (C) 2019 Garrett HE <garrett.he@outlook.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>

static void display_help(FILE* fp) {
    fprintf(fp, "usage: smtm [FILE]\n");
    fprintf(fp, "Lua engine to let you run scripts to cheat/mod in games.\n");
}

int main(int argc, char** argv) {
    if (argc < 2) {
        display_help(stderr);
        return -1;
    }

    return 0;
}
