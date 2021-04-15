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
# 1.3.0
## renderer
