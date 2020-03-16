Texture2D  myTexture : register(t0);
SamplerState mySampler : register(s0);


cbuffer CBPerFrame : register(b0)
{
	row_major matrix  World;
	row_major matrix  View;
	row_major matrix  Proj;
	row_major matrix MVP;
};

struct VSInput
{
	float4 Position : POSITION;
	float2 TexCoord : TEXCOORD;
	float4 Color : COLOR;
};

struct PSInput
{
	float4 Position : SV_POSITION;
	float2 TexCoord : TEXCOORD;
	float4 Color : COLOR;
};


PSInput VSFunc(VSInput input)
{
	PSInput output = (PSInput)0;

	output.Position = mul(input.Position, MVP);
	output.TexCoord = input.TexCoord;
	output.Color = input.Color;

	return output;
}

float4 PSFunc(PSInput input) : SV_TARGET0
{
	float4 output = float4(0.0, 0.0, 0.0, 0.0);
	output = myTexture.Sample(mySampler, input.TexCoord);

	return input.Color * output;

}