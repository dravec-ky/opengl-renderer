#version 430 core
layout (location=0) in vec3 inPos;
layout (location=1) in vec3 inN;
layout (location=2) in vec2 inUV;

layout (location=3) uniform mat4 inTransform;

out vec3 vertCol;
out vec2 TexCoords;
out vec3 WorldPos;
out vec3 Normal;


layout( std140) uniform TransformUBO
{
  mat4 MVP;
  mat4 normalMatrix;
  mat4 M;

}transforms;

void main()
{
    WorldPos = vec3(inTransform * vec4(inPos,1.0f));
    gl_Position = transforms.MVP*vec4(WorldPos,1.0);
    Normal = vec3(transforms.normalMatrix*vec4(inN,1.0f));
    vertCol = normalize(mat3(transforms.normalMatrix)*inN);
    TexCoords = inUV;
}