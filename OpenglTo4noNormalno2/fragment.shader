	#version 330 core
layout(location = 0) out vec4 color;



in vec2 v_TexCoord;


uniform vec4 u_Color;
uniform sampler2D u_Texture; 

void main(){

		vec4 texColor = texture(u_Texture, v_TexCoord);
		if (u_Color == vec4(0.0, 0.0, 0.0, 0.0))
			color = texColor;
		else
			color = u_Color;

		//ccolor = vec4(0.0f,1.0f,0.0f,1.0f);
	//color = vec4(1.0f, 1.0f, 1.0f,1.0f);
}