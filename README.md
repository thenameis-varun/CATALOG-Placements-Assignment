# CATALOG-Placements-Assignment
This is solved problem provided by company Catalog :)

Polynomial Constant Term Solver - Solution Overview
This solution is designed to compute the constant term (c) of a polynomial using Lagrange Interpolation. The input is provided in JSON format, where each root of the polynomial is given in a base-encoded form.

How the Solution Works:
JSON Parsing:

The program reads and parses the input JSON file to extract the provided roots, which are encoded in different bases.
It uses the cJSON library to handle the parsing of the JSON data.
Base Conversion:

The encoded values (in bases like binary, decimal, hexadecimal, etc.) are converted to decimal format to make them usable for mathematical operations.
Lagrange Interpolation:

The decoded points are used to perform Lagrange interpolation. This method reconstructs the polynomial using the given points and helps in computing the polynomial's constant term.
Final Output:

The constant term (c) of the polynomial is computed and displayed as the final result.
The code dynamically handles various JSON inputs, and processes the roots to solve for the constant term efficiently using standard C language features combined with the cJSON library for JSON parsing.
