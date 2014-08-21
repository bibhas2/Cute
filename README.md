##Overview
Cute is a very simple C library to deal with common data structures like dynamic String and Array.

These data types are meant to be used in small C programs where use of C++
or STL will be too much of a burden. Consequently, the library is small
and focuses on high performance and low memory overhead.

There are no dependencies between the data types, such as String and Dictionary. This way,
you use just what you need.

###About String Class
The String class is able to store UTF-8 multi-byte characters. You can convert a String to a NULL
terminated C string by calling `stringAsCString(String* str)`.

###About Memory Management
One of the goals of this project is to be very careful about buffer overflow and 
memory allocation errors. In case of either, the program will abort. This way, we err
on the side of caution.

If you notice any potential problems with memory management, please open an issue.
