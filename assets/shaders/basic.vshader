attribute vec4 aPosition; 
attribute vec3 aTexture;                 
    
varying vec2 v_uv;   

void main()
{                               
  v_uv = vec2(aTexture.x, aTexture.y);
  gl_Position = aPosition;            	                   
}                                 