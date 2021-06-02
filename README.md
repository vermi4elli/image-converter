# 1.2.0
## image-converter
An image converter for basic formats. Supports:
- PPM (from/to)
- BMP (from/to)
- PNG (from/to)
- GIF (from)

### Manual
To use the converter put the source image meant for convertion into the same folder as the executable. It can be used from command line with the next arguments:
- `--source` - the source file
- `--goal-format` - the goal image format (e.g. ppm or bmp)
- `--output` - the resulting file (by default the new file with the same path and name but different filename extension (e.g. `./example.ppm` > `./example.bmp`)

Example of the program executing:
```
> image-converter.x64.exe --source=example.bmp --goal-format=png
```
# 2.0.0
## renderer
An image converter for OBJ format. Supports rendering into:
- PPM
- BMP
- PNG

### Manual
To use the renderer put the source .obj model meant for rendering into the same folder as the executable. The raytracing is implemented using the KD-tree. It can be used from command line with the next arguments:
- `--source` - the source .obj file
- `--goal-format` - the goal image format (e.g. png or bmp)
- `--output` - the resulting file
- `--side` - the side of the model the camera should see (e.g. front, back, left or right)

Example of the program executing:
```
> renderer.x64.exe --source=dragon3.obj --output=render.png --side=front
```
Examples of render:

renderer.x64.exe --source=dragon3.obj --output=render1.png --side=front
![example 1](/images/render1.png)

Examples of render:
renderer.x64.exe --source=dragon3.obj --output=render2.png --side=back
![example 2](/images/render2.png)

Examples of render:
renderer.x64.exe --source=cow.obj --output=render3.png --side=front
![example 3](/images/render3.png)

Examples of render:
renderer.x64.exe --source=deer.obj --output=render4.png --side=back
![example 4](/images/render4.png)

Examples of render:
renderer.x64.exe --source=deer.obj --output=render5.png --side=right
![example 5](/images/render5.png)

## Whitted tracer and different materials

Examples of render:
Purple sphere in midle and glass sphere to the left, also red sphere far. Point light.
![example 6](/images/render6.png)

Examples of render:
Three diffuse sphere and point light.
![example 7](/images/render7.png)

Examples of render:
3 sphere in one line, first 2 from glass and last without material. Depth of traced incresed up to 10. Point light.
![example 8](/images/render8.png)

Examples of render:
3 sphere in one line. There is sphere in another shpere, both from glass and last without material. Depth of traced incresed up to 10. Point light.
![example 9](/images/render9.png)

Examples of render:
Sphere in middle has reflect material. Both anothere sphere with spirals. Directional light.

![example 10](/images/render10.png)

Examples of render:
Sphere in middle has diffuse material. Both anothere sphere with diffuse and glossy material. Directional light.
![example 11](/images/render11.png)

Examples of render:
Closest sphere from glass. Middle sphere also from glass but absorbs blue color. Spheres around from diffuse, and the last one default. Directional light.
![example 12](/images/render12.png)

Examples of render:
Middle sphere is mirror and absorbs some luminence. Spheres around from diffuse and with spirall(angle 0). Directional light.
![example 13](/images/render13.png)


Examples of render:
Middle sphere is from material which reflect and refract with ior 2.4(diamond). Spheres around from diffuse and with spirall(angle 0). Directional light.
![example 14](/images/render14.png)


Examples of render:
Example of interpolation. Every dot of this triangles has own normal which has it`s own direction. Directional light.
![example 15](/images/render15.png)

Examples of render:
Same triangles but without interpolation. Directional light.
![example 16](/images/render16.png)