//
// Created by regrif07 on 11/3/24.
//

#include <string.h>

void reverseStringInPlace(char* str)
{
    int first = 0;
    int last = (int)(strlen(str)) - 1;
    while (first < last)
    {
        const char temp = str[first];
        str[first++] = str[last];
        str[last--] = temp;
    }
}
