/* main.c - Example program.  

   Copyright (c) 2015, Monaco F. J. <moanco@icmc.usp.br>

   This file is part of POSIXeg.

   POSIXeg is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <stdlib.h>

#include <rectangle.h>
#include <square.h>
#include <circle.h>

#define SIDE   5.0
#define RADIUS 3.0
#define BASE 3.0
#define HEIGHT 2.0

int main (int argc, char **argv)
{
  float ac, ar, as;

  ac = circle (RADIUS);
  ar = rectangle (BASE, HEIGHT);
  as = square (SIDE);

  printf ("Area of a circle of radius %1.1f is %1.1f\n", RADIUS, ac);
  printf ("Area of a rectangle of base %1.1f and height %1.1f is %1.1f\n", BASE, HEIGHT, ar);
  printf ("Area of a square of sides %1.1f is %1.1f\n", SIDE, as);

  return EXIT_SUCCESS;
}
