// コンスタントバッファ
cbuffer constBuffer : register(b0)
{
    float4 color;
    float4x4 mat;
}

// バーテックスシェーダから出てくる値
struct VertexShaderOutput
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
};
// バーテックスシェーダに入れる値
struct VertexShaderInput
{
    float4 position : POSITION0;
    float2 texcoord : TEXCOORD0;
};

// マテリアル
struct Material
{
    // 色
    float4 color;
};
// ピクセルシェーダから出てくる値
struct PixelShaderOutput
{
    float4 color : SV_TARGET0;
};