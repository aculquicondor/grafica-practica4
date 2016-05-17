#include <GL/glew.h>
#include "texture.h"


Texture::Texture(const std::string &filename, GLenum image_format, GLint internal_format, GLint level, GLint border)
        : texture_id(0) {
    FREE_IMAGE_FORMAT fif;
    fif = FreeImage_GetFileType(filename.c_str());
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(filename.c_str());
    if (fif == FIF_UNKNOWN)
        return;
    if (not FreeImage_FIFSupportsReading(fif))
        return;
    FIBITMAP *dib = FreeImage_Load(fif, filename.c_str());
    if (not dib)
        return;
    BYTE *bits = FreeImage_GetBits(dib);
    unsigned int width = FreeImage_GetWidth(dib),
            height = FreeImage_GetHeight(dib);
    if (bits == 0 or width == 0  or height == 0)
        return;

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, bits);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    FreeImage_Unload(dib);
}


void Texture::load() const {
    if (texture_id != 0)
        glBindTexture(GL_TEXTURE_2D, texture_id);
}