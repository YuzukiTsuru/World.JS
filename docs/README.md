<p align="center"><img width="300" src="https://raw.githubusercontent.com/YuzukiTsuru/World.JS/master/.github/ScreenShots/logo.v3.png" alt="World.JS logo"></p>
<h1 align="center">World.JS</h1>
<p align="center">A JavaScript Wrapper for World Vocoder Powered by Emscripten</p>
<p align="center"><img src="https://github.com/YuzukiTsuru/World.JS/workflows/CMake/badge.svg">    <img src="https://ci.appveyor.com/api/projects/status/6vbge2p0q0mdshtc?svg=true"></p>

## About World.JS

World.JS is A JavaScript Wrapper for World Vocoder Powered by emscripten.  
You can use World Vocoder in your Browser, NodeJS, Electron app and many more like normal JavaScript.

## About Emscripten

Emscripten is a toolchain for compiling to asm.js and WebAssembly, built using LLVM, that lets you run C and C++ on the
web at near-native speed without plugins.

- Fast as near-native speed.
- Easy to use.
- Powerful

## About World

Morise's World Vocoder is a fast and high-quality vocoder. World Vocoder parameterizes speech into three components:

1. Pitch (fundamental frequency, F0) contour
2. Harmonic spectral envelope
3. Aperiodic spectral envelope (relative to the harmonic spectral envelope)

!> For more information, please visit [Morise's World repository](https://github.com/mmorise/World) and
the [official website of World Vocoder](http://www.kisc.meiji.ac.jp/~mmorise/world/english/)

## Build Status CI

| appveyor master | appveyor latest | GitHub Action latest |
|---|---|---|
|[![Build status](https://ci.appveyor.com/api/projects/status/6vbge2p0q0mdshtc/branch/master?svg=true)](https://ci.appveyor.com/project/GloomyGhost-MosquitoCoil/world-js/branch/master)|[![Build status](https://ci.appveyor.com/api/projects/status/6vbge2p0q0mdshtc?svg=true)](https://ci.appveyor.com/project/GloomyGhost-MosquitoCoil/world-js)|![CMake](https://github.com/YuzukiTsuru/World.JS/workflows/CMake/badge.svg)|

## API

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

## How To Use

First, load the entire WorldJS Module.

```javascript
let WorldJS = Module.WorldJS
```

### Example

#### WavRead

- .wav input functions
    - Parameter
        - `filename: string`  Wav File Name
    - Retrun
        - `fs: int `
        - `nbit: int`
        - `x: Float64Array`
        - `x_length: int`

```javascript
let x = WorldJS.WavRead("vaiueo2d.wav")
console.log(x)
```

![WavRead](assets/img/WavRead.png)

#### DIO

- F0 estimation based on DIO (Distributed Inline-filter Operation).
    - Parameter
        - `x: Float64Array`
        - `x.fs: int`
        - `frame_period: double`

```javascript
let f0 = WorldJS.Dio(x.x, x.fs, 2.0);
console.log(x);
console.log(f0);
```

![Dio](assets/img/Dio.png)

#### Harvest

- F0 estimation based on Harvest.
    - Parameter
        - `x: Float64Array`
        - `x.fs: int`
        - `frame_period: double`

```javascript
let f0 = WorldJS.Harvest(x.x, x.fs, 2.0);
console.log(f0);
```

![Harvest](assets/img/Harvest.png)

#### DisplayInformation

- Display Information in native World
    - Parameter
        - `x.fs: int`
        - `x.nbit: int`
        - `x_length: int`

```javascript
WorldJS.DisplayInformation(x.fs, x.nbit, x.x_length);
```

![DisplayInformation](assets/img/DisplayInformation.png)

#### DisplayInformationVal

- Display Information in Wrapper
    - Parameter
        - `x: Wav Object`

```javascript
WorldJS.DisplayInformationVal(x);
```

![DisplayInformationVal](assets/img/DisplayInformationVal.png)

#### CheapTrick

- Spectral envelope estimation on the basis of the idea of CheapTrick.
    - Parameter
      - `x.x: Float64Array`
      - `f0.f0: Float64Array`
      - `f0.time_axis: int`
      - `x.fs: int`

```javascript
let f0 = WorldJS.Dio(x.x, x.fs, 2.0);  // estimation F0 first
WorldJS.CheapTrick(x.x, f0.f0, f0.time_axis, x.fs);
```

![CheapTrick](assets/img/CheapTrick.png)

#### TODO

#### D4C_JS

> Band-aperiodicity estimation on the basis of the idea of D4C.

```html

<script src="WorldJS.js"></script>

<script>
    let x = Module.WavRead_JS("vaiueo2d.wav");
    let f0 = Module.Dio_JS(x.x, x.fs, 2.0);
    let sp = Module.CheapTrick_JS(x.x, f0.f0, f0.time_axis, x.fs, 2.0);
    Module.D4C_JS(x.x, f0.f0, f0.time_axis, sp.fft_size, x.fs, 2.0);
</script>
```

![D4C](assets/img/D4C.png)

#### Synthesis_JS

> Voice synthesis based on f0, spectrogram and aperiodicity.

```html

<script src="WorldJS.js"></script>

<script>
    let x = Module.WavRead_JS("vaiueo2d.wav");
    let f0 = Module.Dio_JS(x.x, x.fs, 2.0);
    let sp = Module.CheapTrick_JS(x.x, f0.f0, f0.time_axis, x.fs, 2.0);
    let ap = Module.D4C_JS(x.x, f0.f0, f0.time_axis, sp.fft_size, x.fs, 2.0);
    Module.Synthesis_JS(f0.f0, sp.spectral, ap.aperiodicity, sp.fft_size, x.fs, 2.0)
</script>
```

#### WavWrite_JS

> Output Wav File

```html

<script src="WorldJS.js"></script>
<script>
    let x = Module.WavRead_JS("vaiueo2d.wav");
    Module.WavWrite_JS(x.x, x.fs, x.nbit, "out.wav")
</script>
```

![WavWrite](assets/img/WavWrite.png)

#### Wav2World

> Wav to world

```html

<script src="WorldJS.js"></script>
<script>
    Module.Wav2World("vaiueo2d.wav");
</script>
```

![WavWrite](assets/img/W2W.png)

### Build World.JS

#### Terminal Clip Guide

Here is a sort clip to show how to build the World.JS in Linux (Powered by asciinema)

<script id="asciicast-388188" src="https://asciinema.org/a/388188.js" async></script>

##### Before Build

You must install these software in advance:

- [CMake](https://cmake.org/)
- [Python3 environment](https://www.python.org/)
- [Emscripten SDK](https://emscripten.org/)
- [Node](https://nodejs.org/)
- [VSCode](https://code.visualstudio.com/)
    - [VSCode extension: CMake Tools](https://marketplace.visualstudio.com/items?itemName=vector-of-bool.cmake-tools)
- Software development tool chain like `make` `gcc` etc.

##### Clone Files

```bash
git clone https://github.com/YuzukiTsuru/World.JS.git
git submodule init
git submodule update
```

##### Set emsdk CMake Tool and Configure the compilation environment

!> The Debug version of World.JS will preload the test audio file `vaiueo2d.wav` into World.JS as a `*.data` file for
development and testing. This is because the file system of World.JS is currently incomplete.

###### VSCode

Edit it in `.vscode/settings.json` and change the path into your own.

```yaml
"cmake.configureArgs": [ "-DCMAKE_TOOLCHAIN_FILE=path/to/Emscripten.cmake" ]
```

###### Common CMake

Use the `CMAKE_TOOLCHAIN_FILE` parameter during `cmake` command.

example:

```bash
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=the/path/to/Emscripten.cmake ..
```

##### Run build script

###### For VSCode

After setting `cmake.configureArgs` in your VSCode settings file :`.vscode/settings.json`, click the compile button.

###### For CMake

After Configure the compilation environment, just `make`

```bash
cd build
make
```

### Troubleshooting

#### Uncaught could not load memory initializer

```
Access to XMLHttpRequest at 'file:///World.JS/test/WorldJS.data' from origin 'null' has been blocked by CORS policy: Cross origin requests are only supported for protocol schemes: http, data, chrome, chrome-extension, https.
WorldJS.js:15 Uncaught could not load memory initializer WorldJS.js.mem
```

Unfortunately several browsers (including *Chrome*, *Safari*, and *Internet Explorer*) do not support `file://`
XHRrequests, and can’t load extra files needed by the HTML (like a `.mem` file, or packaged file `data` as mentioned
lower down). For these browsers you’ll need to serve the files using a webserver. The easiest way to do this is to use
the Python **HTTPServer** (in the current directory do `python -m SimpleHTTPServer` (
Python2)  ` python -m http.server` (python3) and then open `http://localhost:8000`). And emscripten also provide `emrun`
to run such code. Document
here [Running HTML files with emrun](https://emscripten.org/docs/compiling/Running-html-files-with-emrun.html)

### File System Develop

The File System is based on Emscripten,visit Emscripten home for more detials:

[https://emscripten.org/docs/porting/files/index.html](https://emscripten.org/docs/porting/files/index.html)

## References

[1] M. Morise, F. Yokomori, and K. Ozawa: WORLD: a vocoder-based high-quality speech synthesis system for real-time
applications, IEICE transactions on information and systems, vol. E99-D, no. 7, pp. 1877-1884, 2016.
[2] M. Morise: D4C, a band-aperiodicity estimator for high-quality speech synthesis, Speech Communication, vol. 84, pp.
57-65, Nov. 2016. http://www.sciencedirect.com/science/article/pii/S0167639316300413

`In CheapTrick, you can refer the following references.`

[3] M. Morise: CheapTrick, a spectral envelope estimator for high-quality speech synthesis, Speech Communication, vol.
67, pp. 1-7, March 2015. http://www.sciencedirect.com/science/article/pii/S0167639314000697
[4] M. Morise: Error evaluation of an F0-adaptive spectral envelope estimator in robustness against the additive noise
and F0 error, IEICE transactions on information and systems, vol. E98-D, no. 7, pp. 1405-1408, July 2015.

`In DIO, you can refer the following reference.`

[5] M. Morise, H. Kawahara and H. Katayose: Fast and reliable F0 estimation method based on the period extraction of
vocal fold vibration of singing voice and speech, AES 35th International Conference, CD-ROM Proceeding, Feb. 2009.

`In Harvest, you can refer the following reference.`

[6] M. Morise: Harvest: A high-performance fundamental frequency estimator from speech signals, in Proc. INTERSPEECH
2017, pp. 2321–2325, 2017. http://www.isca-speech.org/archive/Interspeech_2017/abstracts/0068.html

`In the codec of spectral envelope, you can refer the following reference.`

[7] M. Morise, G. Miyashita and K. Ozawa: Low-dimensional representation of spectral envelope without deterioration for
full-band speech analysis/synthesis system, in Proc. INTERSPEECH 2017, pp. 409-413,

2017. http://www.isca-speech.org/archive/Interspeech_2017/abstracts/0067.html

`A paper was published to demonstrate that the current version of WORLD was superior to the similar vocoders in the sound quality of re-synthesized speech. This paper also includes the detailed information in the D4C LoveTrain used in the latest version.`

[8] M. Morise and Y. Watanabe: Sound quality comparison among high-quality vocoders by using re-synthesized speech,
Acoust. Sci. & Tech., vol. 39, no. 3, pp. 263-265, May

2018. https://www.jstage.jst.go.jp/article/ast/39/3/39_E1779/_article/-char/en
