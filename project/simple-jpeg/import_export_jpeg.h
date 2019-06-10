extern void export_JPEG_file (const char* filename, const unsigned char* image_chars,
                              int image_height, int image_width,
                              int num_components, int quality);

extern void import_JPEG_file (const char* filename, unsigned char** image_chars,
                              int* image_height, int* image_width,
                              int* num_components);
