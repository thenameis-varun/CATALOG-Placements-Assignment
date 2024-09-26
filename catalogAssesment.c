#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "cJSON.h" 

// Function to decode a string value from a given base into a long long integer
long long decodeBase(const char* value, int base) {
    long long result = 0;  // Initialize the result to 0
    const char* ptr = value;  // Pointer to traverse through the string

    // Loop through each character in the value string
    while (*ptr) {
        result *= base;  // Multiply result by the base for every digit

        // Check if the character is a digit or letter and convert accordingly
        if (isdigit(*ptr)) {
            result += *ptr - '0';  // Convert digit characters ('0'-'9')
        } else {
            result += toupper(*ptr) - 'A' + 10;  // Convert letter characters ('A'-'F' etc.)
        }
        ptr++;  // Move to the next character
    }

    return result;  // Return the decoded result
}

// Function to perform Lagrange interpolation and calculate the constant term 'c'
double lagrangeInterpolation(int x[], long long y[], int k) {
    double result = 0.0;  // Initialize the result to 0

    // Outer loop goes through each point in the set
    for (int i = 0; i < k; ++i) {
        double term = y[i];  // Start with the y value of the current point

        // Inner loop to calculate the Lagrange basis polynomial for point i
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                // Multiply by (0 - x[j]) / (x[i] - x[j]) to calculate the product
                term *= (0.0 - x[j]) / (x[i] - x[j]);
            }
        }

        result += term;  // Add the term to the result
    }

    return result;  // Return the final interpolated result
}

// Function to parse the JSON file and process the points to calculate the constant term
void solveFromJson(const char* filename) {
    // Open the JSON file for reading
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open the file\n");
        return;  // Exit the function if file cannot be opened
    }

    // Find the file size and allocate a buffer to hold the contents
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = (char*)malloc(fileSize + 1);  // Allocate memory for the file content
    fread(buffer, 1, fileSize, file);  // Read the file content into the buffer
    buffer[fileSize] = '\0';  // Null-terminate the buffer
    fclose(file);  // Close the file

    // Parse the JSON from the buffer
    cJSON* root = cJSON_Parse(buffer);
    if (!root) {
        printf("Error: Failed to parse JSON\n");
        free(buffer);  // Free the buffer memory if parsing fails
        return;
    }

    // Extract the "n" and "k" values from the JSON under "keys"
    cJSON* keys = cJSON_GetObjectItem(root, "keys");
    int n = cJSON_GetObjectItem(keys, "n")->valueint;
    int k = cJSON_GetObjectItem(keys, "k")->valueint;

    // Allocate memory for the x and y arrays
    int* x = (int*)malloc(n * sizeof(int));
    long long* y = (long long*)malloc(n * sizeof(long long));

    // Loop through the points in the JSON and decode the y values
    for (int i = 1; i <= n; ++i) {
        char index[10];  // Create a buffer to hold the index as a string
        sprintf(index, "%d", i);  // Convert the index integer to a string

        // Get the JSON object for the current point
        cJSON* point = cJSON_GetObjectItem(root, index);
        if (point) {
            int base = atoi(cJSON_GetObjectItem(point, "base")->valuestring);  // Get the base
            const char* valueStr = cJSON_GetObjectItem(point, "value")->valuestring;  // Get the value string

            // Assign the x value and decode the y value using the base
            x[i - 1] = i;
            y[i - 1] = decodeBase(valueStr, base);
        }
    }

    // Calculate the constant term using Lagrange interpolation
    double constantTerm = lagrangeInterpolation(x, y, k);
    printf("Constant term: %.0f\n", constantTerm);  // Output the result

    // Free allocated memory
    free(x);
    free(y);
    cJSON_Delete(root);
    free(buffer);
}

int main() {
    // Call the function to solve the problem using the JSON file "testcase.json"
    solveFromJson("testcase.json");
    return 0;
}
