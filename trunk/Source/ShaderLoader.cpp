#include "ShaderLoader.h"
ShaderLoader::ShaderLoader(void)
{
}
ShaderLoader::~ShaderLoader(void)
{
}
GLuint ShaderLoader::loadShader ( GLenum type, const char *shaderFile )
{
   GLuint shader;
   GLint compiled;
   //const char *shaderSrc = readFile(shaderFile);
   // Create the shader object
   shader = glCreateShader ( type );

   if ( shader == 0 )
   	return 0;

   // Load the shader source
   glShaderSource ( shader, 1, &shaderFile, NULL );
   
   // Compile the shader
   glCompileShader ( shader );

   // Check the compile status
   glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );

   if ( !compiled ) 
   {
      GLint infoLen = 0;

      glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );
      
      if ( infoLen > 1 )
      {
        
      }

      glDeleteShader ( shader );
      return 0;
   }

   return shader;

}


//
///
/// \brief Load a vertex and fragment shader, create a program object, link program.
//         Errors output to log.
/// \param vertShaderSrc Vertex shader source code
/// \param fragShaderSrc Fragment shader source code
/// \return A new program object linked with the vertex/fragment shader pair, 0 on failure
//
GLuint ShaderLoader::loadProgram (const char *vertShaderSrc, const char *fragShaderSrc )
{
   GLuint vertexShader;
   GLuint fragmentShader;
   GLuint programObject;
   GLint linked;

   // Load the vertex/fragment shaders
   vertexShader = loadShader ( GL_VERTEX_SHADER, vertShaderSrc );
   if ( vertexShader == 0 )
      return 0;

   fragmentShader = loadShader ( GL_FRAGMENT_SHADER, fragShaderSrc );
   if ( fragmentShader == 0 )
   {
      glDeleteShader( vertexShader );
      return 0;
   }

   // Create the program object
   programObject = glCreateProgram ( );
   
   if ( programObject == 0 )
      return 0;

   glAttachShader ( programObject, vertexShader );
   glAttachShader ( programObject, fragmentShader );

   //glBindAttribLocation ( programObject, 0, "vPosition" );
   // Link the program
   glLinkProgram ( programObject );

   // Check the link status
   glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );

   if ( !linked ) 
   {
      GLint infoLen = 0;

      glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );
      
      if ( infoLen > 1 )
      {
         
      }

      glDeleteProgram ( programObject );
      return 0;
   }

   // Free up no longer needed shader resources
   glDeleteShader ( vertexShader );
   glDeleteShader ( fragmentShader );

   return programObject;
}

// read shader file
char* ShaderLoader::readFile(const char *file)
{
	size_t len;
    size_t bytesRead;
    char* contents;
    FILE* f;

    f = fopen(file, "rb");
    if (f == NULL) {
	return NULL;
    }

    // what's the size?
    fseek(f, 0, SEEK_END);
    len = ftell(f);
    rewind(f);

    // read contents
    contents = (char*) malloc(sizeof(char) * len + 1);
    contents[len] = '\0'; // this is needed only for printing to stdout with printf!
    if (contents == NULL) {
	
	return NULL;
    }

    bytesRead = fread(contents, sizeof(char), len, f);

    // close the file
    fclose(f);
   // printf("Contents:\n%s", contents);

   return contents;
	
}