#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

	/* A Program to produce statistical data from a read dataset
	 */

int main (void) {

	// Reading --------------------------------------------------------------------

	// Defines read_stream as a FILE pointer and opens file, beginning read stream (stdio.h).
    FILE *read_stream = fopen("dataset.txt", "r");
    // Error Detection
    if (read_stream == NULL) {
    	perror("Error opening file");
        printf("Error code: %d\n", errno);
        printf("Error description: %s\n", strerror(errno));
        return 1;
    } else printf("File was read successfully\n\n");
    // String / Char variables
    char *Char_matrix[256][3], buffer[256], *token; // size of Char_matrix not calculated, a reasonable length is given for brevity as all values cut i < 100 in calculations anyway.
    // Loop Variables
	int i = 0, j;

	// File read via interpreting tokens  via "," and "\n", duplicating into a two-dimensional array via strtok, strdup, & fgets buffer for 100 rows (cstring).
    while (fgets(buffer, sizeof(buffer), read_stream) != NULL && i <100 ) { // Fills buffer array with individual rows of the read_stream.
        token = strtok(buffer, ",\n"); // Sets token pointer to point to the whole value before "," or "\n".
        Char_matrix[i][0] = strdup(token); // Duplicates the value pointed to by token into a matrix (Column: ID)
        token = strtok(NULL, ",\n");
        Char_matrix[i][1] = strdup(token); // Column: Charge
        token = strtok(NULL, ",\n");
        Char_matrix[i][2] = strdup(token); // Column: Energy

        i++;
    }

    float Fl_matrix[1000][3]; // Float version of char matrix
    // Iterates through every element and Converts string array to double for numerical manipulation via atof (cstdlib).
    for (i = 0; i < 100; i++){
    	for (j=0; j < 3; j++){
    		Fl_matrix[i][j] = atof(Char_matrix[i][j]);
    	}
    }


    // Functions --------------------------------------------------------------------

    /**
     * Function Name: Mean
     * Function Brief: Calculates the mean of a column given a fl-array column input
     *
     * Function takes two floats, sum and mean, and for each increment up to the total of b (100)
     * it sums the elements of b[i][x] for each i, returning the sum of every column element divided
     * by 100 (the total).
     *
     * Function Parameters:
     *  (x) The column of which to calculate the mean.
     *
     * Example Usage:
     *
     * 		float Fl_matrix[1000][3];
     *		for (i = 0; i < 100; i++){
     *			for (j=0; j < 3; j++){
     *			printf("Array: %f\n Column 1 Mean: %f\n Column 2 Mean: %f", Fl_matrix[i][j], mean(1), mean(2));
     *			}
     *		}
     */


    float Mean(int x) {
    	float Sum = 0, Mean;

    		    for (i = 0; i < 100; i++) Sum += Fl_matrix[i][x];

    		    return Mean = Sum/100;
    }

    /**
     * Function Name: SD
     * Function Brief: Calculates the standard deviation of a column given a fl-array column input
     *
     * Function calls the mean from mean(x) and sets it to Mean_value, then summing the difference between the individual array data
     * and the mean, all squared. Returns the standard deviation as the square root of the sum of their differences squared in 99
     * (as the sample standard deviation has criteria n-1 in its dividend).
     *
     * Function Parameters:
     *  (x) The column of which to calculate the standard deviation.
     *
     * Example Usage:
     *
     *		float Fl_matrix[1000][3];
     *		for (i = 0; i < 100; i++){
     *			for (j=0; j < 3; j++){
     *				printf("Array: %f\n Column 1 SD: %f\n Column 2 SD: %f", Fl_matrix[i][j], SD(1), SD(2));
     *			}
     *		}
     */


    float SD(int x) {
    	float Sum_difference = 0, SD = 0, Mean_value;

    		Mean_value = Mean(x);

    		for (i = 0; i < 100; i++) Sum_difference += pow(Fl_matrix[i][x]-Mean_value, 2);

    	    return SD = sqrt(Sum_difference/ 99);
    }

    /**
     * Function Name: min_max
     * Function Brief: Calculates the minimum of a column given a fl-array column input
     *
     * Function sets the location of minimum (or maximum, given execution choice) 'location' to 0, assigns float for the final minimum/maximum,
     * it then iterates for every item (100 items) in the array of column x and checks if the value at x is less than (or greater than for maximum)
     * the value at the previous'location' of the minimum/maximum - it sets this new minimum/maximum to location and continues until the whole list
     * is exhausted, it then returns the minimum/maximum equal to the evaluated array element stored at the minimum/maximum location.
     *
     * Function Parameters:
     *  (x) The column of which to calculate the minimum/maximum value.
     *
     * Example Usage:
     *
     * 		float Fl_matrix[1000][3];
     *		for (i = 0; i < 100; i++){
     *			for (j=0; j < 3; j++){
     *				printf("Array: %f\n Column 2 Min: %f\n Column 2 Max: %f", Fl_matrix[i][j], min_max(2, 0), min_max(2, 1));
     *			}
     *		}
     */

    float min_max(int x, int y) {
    	int location = 0;
    	float minimum;
    	for (i = 0; i < 100; i++) {
    		if (Fl_matrix[i][x] < Fl_matrix[location][x] && y == 0)
    			location = i;
    		else if (Fl_matrix[i][x] > Fl_matrix[location][x] && y == 1)
    			location = i;
    		else if  (y != 0 && y!= 1)
			printf("Incorrect use of min_max");

    	}
    	return minimum = Fl_matrix[location][x];
    }


    // Output Table -----------------------------------------------------------
    // Final Print formatted to make legibility easier for each row.
        printf("|     |       C1|   C2    |\n|-----|---------|---------|\n");
    	printf("| Mean|    %.2f |   %.2f |\n", Mean(1), Mean(2) ); // Mean Values
    	printf("| Sdev|    %.2f |    %.2f |\n", SD(1), SD(2)); // Standard Deviation Values
    	printf("|  Min|    %.2f |    %.2f |\n", min_max(1, 0), min_max(2, 0)); // Minimum Values
    	printf("|  Max|    %.2f |   %.2f |\n", min_max(1, 1), min_max(2, 1)); // Maximum Values


    // Final Print formatted to make legibility easier for each row, colours added.
    printf("|     |       C1|   C2    |\n|-----|---------|---------|\n");
	printf("| Mean|\033[0;31m    %.2f\033[0m | \033[0;31m  %.2f\033[0m |\n", Mean(1), Mean(2) ); // Mean Values
	printf("| Sdev|\033[0;31m    %.2f\033[0m |\033[0;31m    %.2f\033[0m |\n", SD(1), SD(2)); // Standard Deviation Values
	printf("|  Min|\033[0;31m    %.2f\033[0m |\033[0;31m    %.2f\033[0m |\n", min_max(1, 0), min_max(2, 0)); // Minimum Values
	printf("|  Max|\033[0;31m    %.2f\033[0m |\033[0;31m   %.2f\033[0m |\n", min_max(1, 1), min_max(2, 1)); // Maximum Values
	


    // End --------------------------------------------------------------------

    	fclose(read_stream); // End read stream

return 0; // End program
}


