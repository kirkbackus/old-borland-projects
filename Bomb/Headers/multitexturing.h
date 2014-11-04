#ifndef __H__MTEXURING_
#define __H__MTEXURING_

#include <string>

/**************************
 * Multitexturing Support
 *
 **************************/
#define GL_TEXTURE0_ARB                     0x84C0 // the first texture
#define GL_TEXTURE1_ARB                     0x84C1 // the second texture

#define GL_COMBINE_ARB						0x8570 // this gives us the ability to combine our textures (through r,g,b)
#define GL_RGB_SCALE_ARB					0x8573 // this lets us scale our texture colours

bool MTexEnabled = 1;

PFNGLMULTITEXCOORD1FARBPROC		glMultiTexCoord1fARB	 = NULL;
PFNGLMULTITEXCOORD2FARBPROC		glMultiTexCoord2fARB	 = NULL;
PFNGLMULTITEXCOORD3FARBPROC		glMultiTexCoord3fARB	 = NULL;
PFNGLMULTITEXCOORD4FARBPROC		glMultiTexCoord4fARB	 = NULL;
PFNGLACTIVETEXTUREARBPROC		glActiveTextureARB		 = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC	glClientActiveTextureARB = NULL;

bool isInString(char *string, const char *search) {
	int pos=0;
	int maxpos=strlen(search)-1;
	int len=strlen(string);
	char *other;
	for (int i=0; i<len; i++) {
		if ((i==0) || ((i>1) && string[i-1]=='\n')) {				// New Extension Begins Here!
			other=&string[i];
			pos=0;													// Begin New Search
			while (string[i]!='\n') {								// Search Whole Extension-String
				if (string[i]==search[pos]) pos++;					// Next Position
				if ((pos>maxpos) && string[i+1]=='\n') return true; // We Have A Winner!
				i++;
			}
		}
	}
	return false;													// Sorry, Not Found!
}

bool initMultitexturing() {
	string glExtensions;
	char* t;
	t = strdup((char*)glGetString(GL_EXTENSIONS)); glExtensions = t;
	if (glExtensions.find("GL_ARB_multitexture") && glExtensions.find("GL_EXT_texture_env_combine")) {
        glMultiTexCoord1fARB	= (PFNGLMULTITEXCOORD1FARBPROC)		wglGetProcAddress("glMultiTexCoord1fARB");
	    glMultiTexCoord2fARB	= (PFNGLMULTITEXCOORD2FARBPROC)		wglGetProcAddress("glMultiTexCoord2fARB");
     	glMultiTexCoord3fARB	= (PFNGLMULTITEXCOORD3FARBPROC)		wglGetProcAddress("glMultiTexCoord3fARB");
      	glMultiTexCoord4fARB	= (PFNGLMULTITEXCOORD4FARBPROC)		wglGetProcAddress("glMultiTexCoord4fARB");
       	glActiveTextureARB		= (PFNGLACTIVETEXTUREARBPROC)		wglGetProcAddress("glActiveTextureARB");
        glClientActiveTextureARB= (PFNGLCLIENTACTIVETEXTUREARBPROC)	wglGetProcAddress("glClientActiveTextureARB");
    } else return 0;
	return 1;
}

#endif
