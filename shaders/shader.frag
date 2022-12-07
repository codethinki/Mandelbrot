#version 450
layout(location = 0) out vec4 outColor;
layout(location = 0) in vec3 color;

layout(push_constant) uniform Push {vec3 general; vec4 edges; vec4 transform;} push;

double map(double value, double inputMin, double inputMax, double outputMin, double outputMax){
	 return outputMin + (outputMax - outputMin) * ((value - inputMin) / (inputMax - inputMin));
}

void main(){
	double realZ = 0, imgZ = 0, realC = map(gl_FragCoord.x, 0, push.general.x, push.edges[0], push.edges[1]), imgC = map(gl_FragCoord.y, 0, push.general.y, push.edges[2], push.edges[3]);
	int i = -1;
	while(i < push.general[2]  && realZ * realZ + imgZ * imgZ < 4){
		double img = realZ * imgZ * 2 + imgC;
		realZ = realZ * realZ - imgZ * imgZ + realC;
		imgZ = img;
		i++;
	}
	double quotient = i / push.general[2];
	//if (quotient > 0.5) outColor = vec4(0, (1 - quotient) * 1.8, 0, 1);
	//else outColor  = vec4(0, quotient * 1.8, 0, 1);
	outColor = vec4(color.x * quotient, color.y * quotient, color.z * quotient, 1);
}
