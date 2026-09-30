/*
 * Searching - Silver rectangles (Challenge 7)
 * A rectangle is silver if the ratio of its sides lies in [1.6, 1.7]
 * (both inclusive). Count the silver rectangles.
 * The ratio is checked both as width/height and as height/width, so the
 * orientation of the rectangle does not matter (a rectangle is counted once).
 * width and height are doubles so that the division is not an integer one.
 *
 * Input : N, then N lines "W H".
 * Output: the number of silver rectangles.
 *
 * Sample: 5 / 10 1 / 165 100 / 180 100 / 170 100 / 160 100 -> 3
 */
#include <stdio.h>

int main()
{
    int n, i, count = 0;
    double width, height;

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%lf %lf", &width, &height);
        if(width/height>=1.6 && width/height<=1.7)
            count++;
        else if(height/width >=1.6 && height/width<=1.7)
            count++;
    }
    printf("%d\n", count);
    return 0;
}
