#pragma once
#include "../containers/string.h"

namespace BogoSort {
    String to_string(int number) {
        auto str = String("");

        // Check if the number is negative
		int isNegative = 0;
		if (number < 0) {
			isNegative = 1;
			number = -number;
		}

		// Convert each digit to character and store in reverse order
		do {
			str.push((number % 10) + '0');
			number /= 10;
		} while (number != 0);

		// Add negative sign if necessary
		if (isNegative) {
            str.push('-');
        }

        str.reverse();
        return str;
    }

    String to_string(float number) {
        auto str = String("");

        // Check for negative number
        bool is_negative = false;
        if (number < 0) {
            is_negative = true;
            number = -number;
        }

        // Extract the integer part
        int integerPart = (int)number;

        // Convert the integer part to a string
        int decimalCount = 0;
        do {
			str.push((integerPart % 10) + '0');
			integerPart /= 10;
            decimalCount++;
		} while (integerPart > 0);

        if (is_negative) {
            str.push('-');
        }

        str.reverse();

        // Add decimal point
        str.push('.');

        // Extract the decimal part
        float decimalPart = number - (int)number;
        // Convert the decimal part to a string
        do {
            decimalPart *= 10;
            int digit = (int)decimalPart;
            str.push('0' + digit);
            decimalPart -= digit;
            decimalCount++;
        } while (decimalCount < 10 && decimalPart != 0);

        return str;
    }
}
