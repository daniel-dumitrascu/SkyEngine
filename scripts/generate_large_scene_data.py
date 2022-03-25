file = open("world_1.level", "w")
file.write("<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>\n")
file.write("<Level>\n")
file.write("	<Cameras>\n")
file.write("		<Camera id=\"1\">\n")
file.write("			<Position x=\"500\" y=\"500\" />\n")
file.write("			<Rotation x=\"0\" y=\"0\" />\n")
file.write("		</Camera>\n")
file.write("	</Cameras>\n")
file.write("	<SelectedActiveCamera CameraID=\"1\" AttachedObject=\"1\"/>\n")

index = 2

for i in range(16):
	xValue = 200
	yValue = 200 + (400 * i)
	for j in range(16):
		file.write("	<GameObject id=\"{0}\">\n".format(index))
		file.write("		<Composition Type=\"2\" ResourceMeshPath=\"assets/meshes/grass.mesh\"\n")
		file.write("								ResourceTexturePath=\"assets/textures/PNG_files/grass.png\"\n")
		file.write("								ResourceShaderPath=\"assets/shaders/rend_tex\" />\n")
		file.write("		<Properties Renderable=\"true\" Collidable=\"true\" />\n")
		xValue = 200 + (400 * j)
		file.write("		<Position x=\"{0}\" y=\"{1}\" />\n".format(xValue, yValue))
		file.write("		<Rotation x=\"0\" y=\"0\" />\n")
		file.write("		<Scale size=\"200\" />\n")
		file.write("		<ZBuffer value=\"1\" />\n")
		file.write("	</GameObject>\n")
		index = index + 1

file.write("</Level>")
file.close