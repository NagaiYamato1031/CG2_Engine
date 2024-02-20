#include "Sprite.hlsli"

VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;

    //output = input;
    output.position = mul(input.position, gMaterial.mat);
    output.texcoord = input.texcoord;

    return output;
}