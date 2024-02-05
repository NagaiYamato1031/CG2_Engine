// バーテックスシェーダに入れる値
struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
};
// バーテックスシェーダから出てくる値
struct VertexShaderOutput
{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD0;
};
// マテリアル
struct Material
{
    // 色
    float32_t4 color;
    // 移動行列
    float32_t4x4 mat;
};

ConstantBuffer<Material> gMaterial : register(b0);