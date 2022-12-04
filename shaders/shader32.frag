#version 450
layout(location = 0) out vec4 outColor;

layout(push_constant) uniform Push {vec3 general; vec4 edges; vec4 transform;} push;

float map(float value, float inputMin, float inputMax, float outputMin, float outputMax){
	 return outputMin + (outputMax - outputMin) * ((value - inputMin) / (inputMax - inputMin));
}

void main(){		
	float realZ = 0, imgZ = 0, realC = map(gl_FragCoord.x, 0, push.general.x, push.edges.x, push.edges.y), imgC = map(gl_FragCoord.y, 0, push.general.y, push.edges.z, push.edges.w);
	
	int i = 0;
	while(i < push.general.z && realZ * realZ + imgZ * imgZ <= 4){
		float img = realZ * imgZ * 2;
		realZ =  realZ * realZ -  imgZ * imgZ + realC;
		imgZ = img + imgC;
		i++;
	}
	outColor = vec4(vec3((i-1) / push.general.z), 1.0);
}