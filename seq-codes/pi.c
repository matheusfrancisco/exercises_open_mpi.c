#include <stdio.h>
#include <stdlib.h>

unsigned int compute_pi(unsigned int, unsigned int);

int main(int argc, char **argv) {
  unsigned int points;
  unsigned int points_in_circle;
  unsigned int i;

  if (argc != 2) {
    printf("Uso:\n");
    printf("\t%s <number of points>\n", argv[0]);
    return 1;
  }

  points = atoi(argv[1]);

  /* Seed = 0. */
  points_in_circle = compute_pi(0, points);

  // Approximates Pi.
  printf("Pi = %.040f\n", ((double)points_in_circle / (double)points) * 4);

  return 0;
}

/* Computes the number of points inside the circle. */
unsigned int compute_pi(unsigned int seed, unsigned int points) {
  unsigned int i;
  unsigned int points_in_circle;
  double x, y;

  points_in_circle = 0;
  srand(seed);

  for (i = 0; i < points; i++) {
    /* Sorts a point: x and y are inside the square. We consider R = 1, so x and
     * y are in range [0; 1]. */
    x = (double)rand() / (double)(RAND_MAX);
    y = (double)rand() / (double)(RAND_MAX);

    /* Checks if the point is inside the circle. If R = 1, it is inside if x^2 +
     * y^2 < R^2. */
    if ((x * x + y * y) < 1) {
      points_in_circle++;
    }
  }

  return points_in_circle;
}
