int strcmp(const char * s1, const char * s2)
{
    while (*s1 == *s2 && *s1++ | *s2++);
    int i = *s1 - *s2;
    return i < 0 ? -1 : i > 0 ? 1 : 0;
}
