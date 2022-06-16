<p align="center"><img width="300" src=".github/ScreenShots/logo.v3.png" alt="World.JS logo"></p>
<h1 align="center">World.JS</h1>
<p align="center">A JavaScript Wrapper for World Vocoder Powered by Emscripten</p>
<p align="center"><img src="https://github.com/YuzukiTsuru/World.JS/workflows/CMake/badge.svg">    <img src="https://ci.appveyor.com/api/projects/status/6vbge2p0q0mdshtc?svg=true"></p>

> The current version is not perfect, there may be a lot of obsolete methods and documents in the future, please pay more attention when using.

[![forthebadge](https://forthebadge.com/images/badges/compatibility-betamax.svg)](https://forthebadge.com)

### About World.JS

World.JS is A JavaScript Wrapper for World Vocoder Powered by Emscripten.  
You can use World Vocoder in your Browser, NodeJS, Electron app and many more like normal JavaScript.

[Examples](https://www.gloomyghost.com/World.JS/#/?id=example) &mdash;
[Documentation](https://www.gloomyghost.com/World.JS/) &mdash;
[Release](https://github.com/YuzukiTsuru/World.JS/releases/latest)

### Build Status CI
| appveyor master | appveyor latest | GitHub Action latest |
|---|---|---|
|[![Build status](https://ci.appveyor.com/api/projects/status/6vbge2p0q0mdshtc/branch/master?svg=true)](https://ci.appveyor.com/project/GloomyGhost-MosquitoCoil/world-js/branch/master)|[![Build status](https://ci.appveyor.com/api/projects/status/6vbge2p0q0mdshtc?svg=true)](https://ci.appveyor.com/project/GloomyGhost-MosquitoCoil/world-js)|![CMake](https://github.com/YuzukiTsuru/World.JS/workflows/CMake/badge.svg)|

## Documentation
Read more info in (Maybe Outdate, Need Update): [Documentation](http://YuzukiTsuru.github.io/World.JS)

### API
```
World Native:
- [x] WavRead_JS             # .wav input functions.
- [x] DIO_JS                 # F0 estimation based on DIO (Distributed Inline-filter Operation).
- [x] Harvest_JS             # F0 estimation based on Harvest.
- [x] DisplayInformation     # Display Information.
- [x] CheapTrick_JS          # Spectral envelope estimation on the basis of the idea of CheapTrick.
- [x] D4C_JS                 # Band-aperiodicity estimation on the basis of the idea of D4C.
- [X] Synthesis_JS           # Voice synthesis based on f0, spectrogram and aperiodicity.
- [x] WavWrite_JS            # Output Wav File.

Wrapper:
- [x] Wav2World              # Wav to world.
- [x] DisplayInformationVal  # Display Information by Audio object from WavRead_JS()
- [X] GetInformation         # Output information in HTML.
- [ ] WavInJS                # Load wav file as WavRead do in JavaScript.
```

## References
- [World](https://github.com/mmorise/World)
- [emscripten](https://emscripten.org/)

## License

```
MIT License

Copyright (c) 2019 Gloomy Ghost

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
