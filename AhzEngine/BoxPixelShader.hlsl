struct PS_INPUT
{
    float4 Position : SV_POSITION;  // interpolated vertex position (system value)
    float4 Color    : COLOR0;       // interpolated diffuse color
    float4 Normal   : NORMAL0;
};

struct PS_OUTPUT
{
    float4 RGBColor : SV_TARGET;
};


PS_OUTPUT main(PS_INPUT In)
{
    PS_OUTPUT Output;

    Output.RGBColor = In.Color * saturate(dot(In.Normal, float4(1, 0, 0, 1)));

    return Output;
}