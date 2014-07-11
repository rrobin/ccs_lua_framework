// Shader produced by robin

#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform sampler2D u_texture;

// fhue -1~1
uniform float brightness;


void main()
{
	vec4 color = texture2D(u_texture, v_texCoord);
	vec3 rgb = color.rgb;
	

		if( brightness > 0.0 )
		{
			rgb = rgb + ( 1.0 - rgb ) * brightness * color.a;
		}
		else
			rgb = rgb + rgb * brightness * color.a;

	
	gl_FragColor = vec4(rgb,color.a) * v_fragmentColor;
}