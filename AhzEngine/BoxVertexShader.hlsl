cbuffer ViewProjectionConstantBuffer : register(b0)
{
    matrix View;
    matrix Projection;
};

cbuffer TransformConstantBuffer : register(b1)
{
    matrix Model;
}

struct VS_INPUT
{
    float3 vPos     : POSITION;
    float4 vColor   : COLOR0;
    float2 vUV      : UV;
    float3 vNormal  : NORMAL;
};

struct VS_OUTPUT
{
    float4 Position : SV_POSITION;  // interpolated vertex position (system value)
    float4 Color    : COLOR0;       // interpolated diffuse color
};

VS_OUTPUT main(VS_INPUT input) // main is the default function name
{
    VS_OUTPUT Output;

    float4 pos = float4(input.vPos, 1.0f);

    pos = mul(pos, Model);
    pos = mul(pos, View);
    pos = mul(pos, Projection);

    Output.Position = pos;

    // Just pass through the color data
    Output.Color = input.vColor;

    return Output;
}