uniform mat4 proj;
attribute vec4 aPosition;

void main() 
{
    // the matrix must be included as a modifier of gl_Position
    gl_Position = proj * aPosition;
	//gl_Position = aPosition;
}