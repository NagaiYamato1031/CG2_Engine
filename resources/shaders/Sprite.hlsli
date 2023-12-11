// コンスタントバッファ
cbuffer constBuffer : register(b0)
{
    float32_t4 color;
    float32_t4x4 mat;
}

// バーテックスシェーダから出てくる値
struct VertexShaderOutput
{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD0;
};
// バーテックスシェーダに入れる値
struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
};

// マテリアル
struct Material
{
    // 色
    float32_t4 color;
};