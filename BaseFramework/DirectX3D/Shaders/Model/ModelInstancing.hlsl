#include "../VertexHeader.hlsli"
#include "../PixelHeader.hlsli"

LightPixelInput VS(VertexInstancing input)
{
	LightPixelInput output;
	output.pos = mul(input.pos, input.transform);
	
	output.viewPos = invView._41_42_43;
	output.worldPos = output.pos;
	
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.uv = input.uv;
	
	output.normal = mul(input.normal, (float3x3) input.transform);
	output.tangent = mul(input.tangent, (float3x3) input.transform);
	output.binormal = cross(output.normal, output.tangent);
	
	return output;
}

float4 PS(LightPixelInput input) : SV_TARGET
{
	//return CalcLights(input);
	//return CalcLights(input) * 0.5f + diffuseMap.Sample(samp, input.uv) * 0.5f;
	//return CalcLights(input) * 0.3f + diffuseMap.Sample(samp, input.uv) * 0.7f;
	//return CalcLights(input) * 0.2f + diffuseMap.Sample(samp, input.uv) * 0.8f;
	//return CalcLights(input) * 0.1f + diffuseMap.Sample(samp, input.uv) * 0.9f;
	//return CalcLights(input) * 0.3f + diffuseMap.Sample(samp, input.uv) * 0.7f;

	return  float4(CalcLights(input).xyz,0) + diffuseMap.Sample(samp, input.uv);

	//return CalcLights(input) * 0.0f;
	//return {0,0,0,1.0f};
}