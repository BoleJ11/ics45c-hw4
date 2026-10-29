#include <iostream>

#include "string.hpp"

int String::strlen(const char *s) {
    int len = 0;
    while (s[len] != '\0') {
        ++len;
    }
    return len;
}

char *String::strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';
    return dest;
}

char *String::strdup(const char *s) {
    if (s == nullptr) s = "";
    int len = strlen(s);
    char *dest = new char[len + 1];
    strcpy(dest, s);
    return dest;
}

char *String::strncpy(char *dest, const char *src, int n) {
    int i = 0;
    for ( ; src[i] != '\0' && i < n; ++i) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

char *String::strcat(char *dest, const char *src) {
    int dest_len = strlen(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        ++i;
    }
    dest[dest_len + i] = '\0';
    return dest;
}

char *String::strncat(char *dest, const char *src, int n) {
    int dest_len = strlen(dest);
    int i = 0;
    while (src[i] != '\0' && i < n) {
        dest[dest_len + i] = src[i];
        ++i;
    }
    dest[dest_len + i] = '\0';
    return dest;
}

int String::strcmp(const char *left, const char *right) {
    int i = 0;
    while (left[i] != '\0' && right[i] != '\0') {
        if (left[i] != right[i]) {
            return left[i] - right[i];
        }
        ++i;
    }
    return left[i] - right[i];
}

int String::strncmp(const char *left, const char *right, int n) {
    if (n <= 0) return 0;
    int i = 0;
    while (i < n && left[i] != '\0' && right[i] != '\0') {
        if (left[i] != right[i]) {
            return left[i] - right[i];
        }
        ++i;
    }
    if (i == n) {
        return 0;
    }
    return left[i] - right[i];
}

void String::reverse_cpy(char *dest, const char *src) {
    int src_len = strlen(src);
    int src_index = src_len - 1;
    int dest_index = 0;
    for (; dest_index < src_len; ++dest_index, --src_index) {
        dest[dest_index] = src[src_index];
    }
    dest[dest_index] = '\0';
}

const char *String::strchr(const char *str, char c) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == c) {
            return &str[i];
        }
        ++i;
    }
    if (c == '\0') {
        return &str[i];
    }
    return nullptr;
}

const char *String::strstr(const char *haystack, const char *needle) {
    int len = strlen(needle);
    if (len == 0) return haystack;
    for (const char *p = haystack; (p = strchr(p, needle[0])) != nullptr; ++p) {
        if (strncmp(p, needle, len) == 0) {
            return p;
        }
    }
    return nullptr;
}

bool String::operator==(String s) const {
    return strcmp(buf, s.buf) == 0;
}

bool String::operator!=(String s) const {
    return strcmp(buf, s.buf) != 0;
}

bool String::operator<(String s) const {
    return strcmp(buf, s.buf) < 0;
}

bool String::operator>(String s) const {
    return strcmp(buf, s.buf) > 0;
}

bool String::operator<=(String s) const {
    return strcmp(buf, s.buf) <= 0;
}

bool String::operator>=(String s) const {
    return strcmp(buf, s.buf) >= 0;
}

String::String(const char *s) {
    buf = strdup(s);
}

String::String(int length) {
    buf = new char[length + 1];
}

String::String(const String &s) {
    buf = strdup(s.buf);
}

String::~String() {
    delete[] buf;
}

void String::swap(String &s) {
    char *temp = buf;
    buf = s.buf;
    s.buf = temp;
}

String &String::operator=(String s) {
    swap(s);
    return *this;
}

char &String::operator[](int index) {
    if (!in_bounds(index)) {
        std::cout << "ERROR: Index Out Of Bounds" << std::endl;
    }
    return buf[index];
}

const char &String::operator[](int index) const {
    if (!in_bounds(index)) {
        std::cout << "ERROR: Index Out Of Bounds" << std::endl;
    }
    return buf[index];
}

int String::size() const {
    return strlen(buf);
}

String String::reverse() const {
    int len = size();
    String result(len);
	reverse_cpy(result.buf, buf);
    return result;
}

int String::indexOf(char c) const {
    const char *p = strchr(buf, c);
    if (p != nullptr) {
        return p - buf;
    }
    return -1;
}

int String::indexOf(String s) const {
    const char *p = strstr(buf, s.buf);
    if (p != nullptr) {
        return p - buf;
    }
    return -1;
}

String String::operator+(String s) const {
    int len1 = size();
    int len2 = s.size();
    String result(len1 + len2);
	strcpy(result.buf, buf);
    strcat(result.buf, s.buf);
    return result;
}

String &String::operator+=(String s) {
    int len1 = size();
    int len2 = s.size();
    char *new_buf = new char[len1 + len2 + 1];
    strcpy(new_buf, buf);
    strcat(new_buf, s.buf);
    delete[] buf;
    buf = new_buf;
    return *this;
}

void String::print(std::ostream &out) const {
    out << buf;
}

void String::read(std::istream &in) {
    char temp[1024];
	in >> temp;
    delete[] buf;
    buf = strdup(temp);
}

std::ostream &operator<<(std::ostream &out, String s) {
    s.print(out);
    return out;
}

std::istream &operator>>(std::istream &in, String &s) {
    s.read(in);
    return in;
}
