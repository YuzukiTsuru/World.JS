<p align="center"><img width="300" src=".github/ScreenShots/logo.v3.png" alt="World.JS logo"></p>
<h1 align="center">World.JS</h1>
<p align="center">A JavaScript Wrapper for World Vocoder Powered by Emscripten</p>

### About World.JS

World.JS is A JavaScript Wrapper for World Vocoder Powered by Emscripten.

You can use World Vocoder in your Browser,Node or Electron app and many more.

####  About Emscripten
Emscripten is a toolchain for compiling to asm.js and WebAssembly, built using LLVM, that lets you run C and C++ on the web at near-native speed without plugins.
- Fast as near-native speed.
- Easy to use.
- Powerful

#### About World

Morise's World Vocoder is a fast and high-quality vocoder. World Vocoder parameterizes speech into three components:

1. Pitch (fundamental frequency, F0) contour
2. Harmonic spectral envelope
3. Aperiodic spectral envelope (relative to the harmonic spectral envelope)

For more information, please visit [Morise's World repository](https://github.com/mmorise/World) and the [official website of World Vocoder](http://www.kisc.meiji.ac.jp/~mmorise/world/english/)

### Build Status with AppVeyor CI
| master | develop |
|---|---|
|[![Build status](https://ci.appveyor.com/api/projects/status/6vbge2p0q0mdshtc/branch/master?svg=true)](https://ci.appveyor.com/project/GloomyGhost-MosquitoCoil/world-js/branch/master)|[![Build status](https://ci.appveyor.com/api/projects/status/6vbge2p0q0mdshtc?svg=true)](https://ci.appveyor.com/project/GloomyGhost-MosquitoCoil/world-js)|

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
- [ ] Wav2World              # Wav to world.
- [ ] WavInJS                # Load wav file as WavRead do.
```
### Example

##### WavRead_JS

> .wav input functions

```html
<script src="WorldJS.js"></script> 

<script>
    let x = Module.WavRead_JS("vaiueo2d.wav");
    console.log(x);
    console.log(x.x);
    console.log(x.fs);
    console.log(x.nbit);
    console.log(x.x_length);
</script>
```

![](.github/ScreenShots/WavRead.png)

##### DIO_JS

> F0 estimation based on DIO (Distributed Inline-filter Operation).

```html
<script src="WorldJS.js"></script> 

<script>
    let x = Module.WavRead_JS("vaiueo2d.wav");
    let f0 = Module.Dio_JS(x.x,x.fs,2.0);
    console.log(x);
    console.log(f0);
</script>
```
![Dio](.github/ScreenShots/Dio.png)

##### Harvest_JS

> F0 estimation based on Harvest.

```html
<script src="WorldJS.js"></script> 

<script>
    let x = Module.WavRead_JS("vaiueo2d.wav");
    let f0 = Module.Harvest_JS(x.x,x.fs,2.0);
    console.log(x);
    console.log(f0);
</script>
```

![Harvest](.github/ScreenShots/Harvest.png)

##### DisplayInformation

> Display Information

```html
<script src="WorldJS.js"></script> 

<script>
    let x = Module.WavRead_JS("vaiueo2d.wav");
    Module.DisplayInformation(x.fs, x.nbit, x.x_length);
</script>
```

##### CheapTrick_JS

> Spectral envelope estimation on the basis of the idea of CheapTrick.

```html
<script src="WorldJS.js"></script> 

<script>
    let x = Module.WavRead_JS("vaiueo2d.wav");
    let f0 = Module.Dio_JS(x.x, x.fs, 2.0);
    Module.CheapTrick_JS(x.x, f0.f0, f0.time_axis, x.fs, 2.0);
</script>
```

![CheapTrick](.github/ScreenShots/CheapTrick.png)

##### D4C_JS

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

![D4C](.github/ScreenShots/D4C.png)

##### Synthesis_JS

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

##### WavWrite_JS

> Output Wav File

```html
<script src="WorldJS.js"></script> 
<script>
    let x = Module.WavRead_JS("vaiueo2d.wav");
    Module.WavWrite_JS(x.x, x.fs, x.nbit, "out.wav")
</script>
```
![WavWrite](.github/ScreenShots/WavWrite.png)

### Build World.JS

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

##### Set emsdk CMake Tool

###### VSCode
Edit it in `.vscode/settings.json` and change the path into your own.

```json
"cmake.configureArgs": ["-DCMAKE_TOOLCHAIN_FILE=~/sdk/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake"]
```
###### Common CMake
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=~/sdk/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake ..
```

##### Run build script

Before run it, make sure `vaiueo2d.wav` is existence in the build folder. **OR** change the `CMakeLists.txt` and delete the `preload-file`, this file is only for test.

And make with vscode.

### Troubleshooting

##### Uncaught could not load memory initializer

```
Access to XMLHttpRequest at 'file:///World.JS/test/WorldJS.data' from origin 'null' has been blocked by CORS policy: Cross origin requests are only supported for protocol schemes: http, data, chrome, chrome-extension, https.
WorldJS.js:15 Uncaught could not load memory initializer WorldJS.js.mem
```

Unfortunately several browsers (including *Chrome*, *Safari*, and *Internet Explorer*) do not support `file://` XHRrequests, and can’t load extra files needed by the HTML (like a `.mem` file, or packaged file data as mentioned lower down). For these browsers you’ll need to serve the files using a webserver. The easiest way to do this is to use the python **HTTPServer** (in the current directory do `python -m SimpleHTTPServer` (Python2)  ` python -m http.server` (python3) and then open `http://localhost:8000`).

### File System Develop

The File System is based on Emscripten,visit Emscripten home for more detials:

[https://emscripten.org/docs/porting/files/index.html](https://emscripten.org/docs/porting/files/index.html)

## References

[1] M. Morise, F. Yokomori, and K. Ozawa: WORLD: a vocoder-based high-quality speech synthesis system for real-time applications, IEICE transactions on information and systems, vol. E99-D, no. 7, pp. 1877-1884, 2016.
[2] M. Morise: D4C, a band-aperiodicity estimator for high-quality speech synthesis, Speech Communication, vol. 84, pp. 57-65, Nov. 2016. http://www.sciencedirect.com/science/article/pii/S0167639316300413

`In CheapTrick, you can refer the following references.`

[3] M. Morise: CheapTrick, a spectral envelope estimator for high-quality speech synthesis, Speech Communication, vol. 67, pp. 1-7, March 2015. http://www.sciencedirect.com/science/article/pii/S0167639314000697
[4] M. Morise: Error evaluation of an F0-adaptive spectral envelope estimator in robustness against the additive noise and F0 error, IEICE transactions on information and systems, vol. E98-D, no. 7, pp. 1405-1408, July 2015.

`In DIO, you can refer the following reference.`

[5] M. Morise, H. Kawahara and H. Katayose: Fast and reliable F0 estimation method based on the period extraction of vocal fold vibration of singing voice and speech, AES 35th International Conference, CD-ROM Proceeding, Feb. 2009.

`In Harvest, you can refer the following reference.`

[6] M. Morise: Harvest: A high-performance fundamental frequency estimator from speech signals, in Proc. INTERSPEECH 2017, pp. 2321–2325, 2017. http://www.isca-speech.org/archive/Interspeech_2017/abstracts/0068.html

`In the codec of spectral envelope, you can refer the following reference.`

[7] M. Morise, G. Miyashita and K. Ozawa: Low-dimensional representation of spectral envelope without deterioration for full-band speech analysis/synthesis system, in Proc. INTERSPEECH 2017, pp. 409-413, 2017. http://www.isca-speech.org/archive/Interspeech_2017/abstracts/0067.html

`A paper was published to demonstrate that the current version of WORLD was superior to the similar vocoders in the sound quality of re-synthesized speech. This paper also includes the detailed information in the D4C LoveTrain used in the latest version.`

[8] M. Morise and Y. Watanabe: Sound quality comparison among high-quality vocoders by using re-synthesized speech, Acoust. Sci. & Tech., vol. 39, no. 3, pp. 263-265, May 2018. https://www.jstage.jst.go.jp/article/ast/39/3/39_E1779/_article/-char/en


### File Tree 

```Text
.
├─build
├─example
│  └─html
├─lib
│  └─WorldCmake
│      └─World
├─src
│  └─WorldJS
├─test
└─tools
    └─third_party
        └─emscripten
```



<details>
<summary>Expand View full directory trees</summary>
<pre><code>.
├─.vscode
├─build
├─example
│  └─html
├─lib
│  └─WorldCmake
│      └─World
│          ├─build
│          ├─doc
│          ├─examples
│          │  ├─analysis_synthesis
│          │  ├─codec_test
│          │  └─parameter_io
│          ├─src
│          │  └─world
│          ├─test
│          ├─tools
│          └─visualstudio
│              └─win
├─src
│  └─WorldJS
├─test
└─tools
    └─third_party
        └─emscripten
            ├─.circleci
            ├─cmake
            │  └─Modules
            │      └─Platform
            ├─docs
            ├─media
            ├─site
            │  ├─build
            │  │  └─text
            │  │      └─docs
            │  │          └─tools_reference
            │  └─source
            │      ├─docs
            │      │  ├─api_reference
            │      │  ├─building_from_source
            │      │  ├─compiling
            │      │  ├─contributing
            │      │  ├─debugging
            │      │  ├─getting_started
            │      │  ├─introducing_emscripten
            │      │  ├─optimizing
            │      │  ├─porting
            │      │  │  ├─connecting_cpp_and_javascript
            │      │  │  ├─files
            │      │  │  ├─guidelines
            │      │  │  └─multimedia_and_graphics
            │      │  ├─site
            │      │  └─tools_reference
            │      ├─_static
            │      └─_themes
            │          └─emscripten_sphinx_rtd_theme
            │              └─static
            │                  ├─css
            │                  ├─fonts
            │                  └─js
            ├─src
            │  └─embind
            ├─system
            │  ├─bin
            │  ├─include
            │  │  ├─AL
            │  │  ├─compat
            │  │  │  └─sys
            │  │  ├─EGL
            │  │  ├─emscripten
            │  │  ├─GL
            │  │  ├─GLES
            │  │  ├─GLES2
            │  │  ├─GLES3
            │  │  ├─GLFW
            │  │  ├─KHR
            │  │  ├─libc
            │  │  │  ├─arpa
            │  │  │  ├─net
            │  │  │  ├─netinet
            │  │  │  ├─netpacket
            │  │  │  ├─scsi
            │  │  │  └─sys
            │  │  ├─libcxx
            │  │  │  ├─experimental
            │  │  │  ├─ext
            │  │  │  └─support
            │  │  │      ├─android
            │  │  │      ├─fuchsia
            │  │  │      ├─ibm
            │  │  │      ├─musl
            │  │  │      ├─newlib
            │  │  │      ├─solaris
            │  │  │      ├─win32
            │  │  │      └─xlocale
            │  │  ├─SDL
            │  │  ├─SSE
            │  │  ├─uuid
            │  │  └─X11
            │  │      └─extensions
            │  ├─lib
            │  │  ├─compiler-rt
            │  │  │  └─lib
            │  │  │      └─builtins
            │  │  ├─embind
            │  │  ├─fetch
            │  │  ├─html5
            │  │  ├─libc
            │  │  │  └─musl
            │  │  │      ├─arch
            │  │  │      │  └─emscripten
            │  │  │      │      └─bits
            │  │  │      ├─dist
            │  │  │      ├─ldso
            │  │  │      └─src
            │  │  │          ├─aio
            │  │  │          ├─compat-emscripten
            │  │  │          ├─complex
            │  │  │          ├─conf
            │  │  │          ├─crypt
            │  │  │          ├─ctype
            │  │  │          ├─dirent
            │  │  │          ├─env
            │  │  │          ├─errno
            │  │  │          ├─exit
            │  │  │          ├─fcntl
            │  │  │          ├─fenv
            │  │  │          │  ├─armebhf
            │  │  │          │  ├─armhf
            │  │  │          │  ├─mips-sf
            │  │  │          │  ├─mipsel-sf
            │  │  │          │  ├─sh-nofpu
            │  │  │          │  └─sheb-nofpu
            │  │  │          ├─internal
            │  │  │          ├─ipc
            │  │  │          ├─ldso
            │  │  │          ├─legacy
            │  │  │          ├─linux
            │  │  │          ├─locale
            │  │  │          ├─math
            │  │  │          │  ├─armebhf
            │  │  │          │  └─armhf
            │  │  │          ├─misc
            │  │  │          ├─mman
            │  │  │          ├─mq
            │  │  │          ├─multibyte
            │  │  │          ├─network
            │  │  │          ├─passwd
            │  │  │          ├─prng
            │  │  │          ├─process
            │  │  │          ├─regex
            │  │  │          ├─sched
            │  │  │          ├─search
            │  │  │          ├─select
            │  │  │          ├─setjmp
            │  │  │          │  ├─mips-sf
            │  │  │          │  ├─mipsel-sf
            │  │  │          │  ├─sh-nofpu
            │  │  │          │  └─sheb-nofpu
            │  │  │          ├─signal
            │  │  │          ├─stat
            │  │  │          ├─stdio
            │  │  │          ├─stdlib
            │  │  │          ├─string
            │  │  │          │  ├─armel
            │  │  │          │  └─armhf
            │  │  │          ├─temp
            │  │  │          ├─termios
            │  │  │          ├─thread
            │  │  │          ├─time
            │  │  │          └─unistd
            │  │  ├─libcxx
            │  │  │  ├─experimental
            │  │  │  │  └─filesystem
            │  │  │  ├─include
            │  │  │  └─support
            │  │  │      ├─runtime
            │  │  │      ├─solaris
            │  │  │      └─win32
            │  │  ├─libcxxabi
            │  │  │  ├─include
            │  │  │  │  └─mach-o
            │  │  │  ├─lib
            │  │  │  └─src
            │  │  │      └─Unwind
            │  │  ├─pkgconfig
            │  │  └─pthread
            │  └─local
            │      └─include
            ├─tests
            │  ├─asmfs
            │  ├─box2d
            │  │  ├─Box2D
            │  │  │  ├─Collision
            │  │  │  │  └─Shapes
            │  │  │  ├─Common
            │  │  │  ├─Dynamics
            │  │  │  │  ├─Contacts
            │  │  │  │  └─Joints
            │  │  │  └─Rope
            │  │  ├─Build
            │  │  │  ├─vs2010
            │  │  │  └─xcode4
            │  │  │      └─Box2D.xcodeproj
            │  │  │          └─project.xcworkspace
            │  │  ├─freeglut
            │  │  ├─glui
            │  │  ├─HelloWorld
            │  │  └─Testbed
            │  │      ├─Framework
            │  │      └─Tests
            │  ├─browser
            │  ├─bullet
            │  │  ├─Demos
            │  │  │  ├─Benchmarks
            │  │  │  └─HelloWorld
            │  │  ├─Extras
            │  │  │  ├─ConvexDecomposition
            │  │  │  └─glui
            │  │  │      └─GL
            │  │  ├─lib
            │  │  └─src
            │  │      ├─BulletCollision
            │  │      │  ├─BroadphaseCollision
            │  │      │  ├─CollisionDispatch
            │  │      │  ├─CollisionShapes
            │  │      │  ├─Gimpact
            │  │      │  ├─ibmsdk
            │  │      │  └─NarrowPhaseCollision
            │  │      ├─BulletDynamics
            │  │      │  ├─Character
            │  │      │  ├─ConstraintSolver
            │  │      │  ├─Dynamics
            │  │      │  ├─ibmsdk
            │  │      │  └─Vehicle
            │  │      ├─BulletMultiThreaded
            │  │      │  ├─GpuSoftBodySolvers
            │  │      │  │  ├─CPU
            │  │      │  │  ├─DX11
            │  │      │  │  │  └─HLSL
            │  │      │  │  └─OpenCL
            │  │      │  │      ├─AMD
            │  │      │  │      ├─Apple
            │  │      │  │      ├─MiniCL
            │  │      │  │      ├─NVidia
            │  │      │  │      ├─OpenCLC
            │  │      │  │      └─OpenCLC10
            │  │      │  ├─SpuNarrowPhaseCollisionTask
            │  │      │  └─SpuSampleTask
            │  │      ├─BulletSoftBody
            │  │      ├─ibmsdk
            │  │      ├─LinearMath
            │  │      │  └─ibmsdk
            │  │      ├─MiniCL
            │  │      │  └─MiniCLTask
            │  │      └─vectormath
            │  │          ├─scalar
            │  │          └─sse
            │  ├─cases
            │  ├─cmake
            │  │  ├─cmake_with_emval
            │  │  ├─cpp_lib
            │  │  ├─emscripten_version
            │  │  ├─static_lib
            │  │  ├─stdproperty
            │  │  ├─target_html
            │  │  ├─target_js
            │  │  └─target_library
            │  ├─core
            │  ├─cstdio
            │  ├─ctype
            │  ├─cube2hash
            │  ├─cubescript
            │  ├─debugger
            │  ├─dirent
            │  ├─embind
            │  ├─emmake
            │  ├─emscripten_log
            │  ├─enet
            │  │  ├─docs
            │  │  ├─include
            │  │  │  └─enet
            │  │  └─m4
            │  ├─env
            │  ├─fcntl
            │  ├─fcntl-misc
            │  ├─fcntl-open
            │  ├─fetch
            │  ├─filesystem
            │  ├─freealut
            │  │  ├─admin
            │  │  │  ├─autotools
            │  │  │  │  └─m4
            │  │  │  ├─CMakeModules
            │  │  │  ├─pkgconfig
            │  │  │  ├─RPM
            │  │  │  ├─VisualStudio6
            │  │  │  │  ├─alut
            │  │  │  │  ├─hello_world
            │  │  │  │  └─playfile
            │  │  │  └─VisualStudioDotNET
            │  │  │      ├─alut
            │  │  │      ├─hello_world
            │  │  │      └─playfile
            │  │  ├─doc
            │  │  ├─examples
            │  │  ├─include
            │  │  │  └─AL
            │  │  ├─src
            │  │  └─test_suite
            │  ├─freetype
            │  │  ├─builds
            │  │  │  └─unix
            │  │  ├─docs
            │  │  ├─include
            │  │  │  └─freetype
            │  │  │      ├─config
            │  │  │      └─internal
            │  │  │          └─services
            │  │  ├─objs
            │  │  └─src
            │  │      ├─autofit
            │  │      ├─base
            │  │      ├─bdf
            │  │      ├─cache
            │  │      ├─cff
            │  │      ├─cid
            │  │      ├─gxvalid
            │  │      ├─gzip
            │  │      ├─lzw
            │  │      ├─otvalid
            │  │      ├─pcf
            │  │      ├─pfr
            │  │      ├─psaux
            │  │      ├─pshinter
            │  │      ├─psnames
            │  │      ├─raster
            │  │      ├─sfnt
            │  │      ├─smooth
            │  │      ├─tools
            │  │      │  ├─docmaker
            │  │      │  └─ftrandom
            │  │      ├─truetype
            │  │      ├─type1
            │  │      ├─type42
            │  │      └─winfonts
            │  ├─fs
            │  ├─fuzz
            │  │  └─include
            │  ├─glbook
            │  │  ├─Chapter_10
            │  │  │  └─MultiTexture
            │  │  ├─Chapter_11
            │  │  │  ├─Multisample
            │  │  │  └─Stencil_Test
            │  │  ├─Chapter_13
            │  │  │  └─ParticleSystem
            │  │  ├─Chapter_15
            │  │  │  └─Hello_Triangle_KD
            │  │  ├─Chapter_2
            │  │  │  └─Hello_Triangle
            │  │  ├─Chapter_8
            │  │  │  └─Simple_VertexShader
            │  │  ├─Chapter_9
            │  │  │  ├─MipMap2D
            │  │  │  ├─Simple_Texture2D
            │  │  │  ├─Simple_TextureCubemap
            │  │  │  └─TextureWrap
            │  │  └─Common
            │  ├─hyperbolic
            │  ├─include_test
            │  ├─interop
            │  ├─langinfo
            │  ├─lua
            │  │  ├─doc
            │  │  └─src
            │  ├─lzma
            │  │  └─lzma
            │  ├─math
            │  ├─module
            │  ├─Module-exports
            │  ├─msvc10
            │  ├─nbody-java
            │  ├─netinet
            │  ├─openjpeg
            │  │  ├─CMake
            │  │  ├─codec
            │  │  ├─common
            │  │  ├─doc
            │  │  │  └─man
            │  │  │      ├─man1
            │  │  │      └─man3
            │  │  └─libopenjpeg
            │  ├─optimizer
            │  ├─other
            │  │  ├─fd_closed
            │  │  ├─ioctl
            │  │  │  └─window_size
            │  │  ├─malloc_implicit
            │  │  ├─unlink
            │  │  ├─wasm_sourcemap
            │  │  └─wasm_sourcemap_dead
            │  ├─parseInt
            │  ├─poppler
            │  │  ├─cmake
            │  │  │  └─modules
            │  │  ├─cpp
            │  │  │  └─tests
            │  │  ├─fofi
            │  │  ├─fontconfig
            │  │  ├─glib
            │  │  │  ├─demo
            │  │  │  └─reference
            │  │  │      └─html
            │  │  ├─goo
            │  │  ├─m4
            │  │  ├─poppler
            │  │  ├─qt
            │  │  ├─qt4
            │  │  │  ├─demos
            │  │  │  ├─src
            │  │  │  └─tests
            │  │  ├─splash
            │  │  ├─test
            │  │  └─utils
            │  ├─printf
            │  ├─pthread
            │  ├─python
            │  ├─qsort
            │  ├─return64bit
            │  ├─scons
            │  ├─sockets
            │  │  ├─p2p
            │  │  │  ├─broker
            │  │  │  └─client
            │  │  └─ws
            │  │      └─lib
            │  ├─sounds
            │  ├─sqlite
            │  ├─stat
            │  ├─stdio
            │  ├─systypes
            │  ├─termios
            │  ├─test_whole_archive
            │  ├─time
            │  ├─unistd
            │  ├─utime
            │  ├─uuid
            │  ├─va_arg
            │  ├─wasm
            │  ├─webidl
            │  └─zlib
            ├─third_party
            │  ├─closure-compiler
            │  │  ├─browser-externs
            │  │  └─node-externs
            │  ├─jni
            │  ├─lzma.js
            │  │  └─lzip
            │  ├─ply
            │  │  ├─doc
            │  │  ├─example
            │  │  │  ├─ansic
            │  │  │  ├─BASIC
            │  │  │  ├─calc
            │  │  │  ├─calcdebug
            │  │  │  ├─classcalc
            │  │  │  ├─closurecalc
            │  │  │  ├─GardenSnake
            │  │  │  ├─hedit
            │  │  │  ├─newclasscalc
            │  │  │  ├─optcalc
            │  │  │  ├─unicalc
            │  │  │  └─yply
            │  │  ├─ply
            │  │  └─test
            │  └─websockify
            │      ├─docs
            │      ├─include
            │      │  └─web-socket-js
            │      ├─other
            │      │  └─js
            │      ├─tests
            │      ├─websockify
            │      └─Windows
            │          └─noVNC Websocket Service Project
            │              └─Properties
            └─tools
                ├─debug
                ├─eliminator
                │  └─node_modules
                │      ├─.bin
                │      └─uglify-js
                │          ├─bin
                │          ├─lib
                │          ├─test
                │          │  └─unit
                │          │      └─compress
                │          │          ├─expected
                │          │          └─test
                │          └─tmp
                ├─experimental
                ├─node_modules
                │  └─source-map
                │      └─lib
                ├─optimizer
                ├─ports
                ├─scons
                │  └─site_scons
                │      └─site_tools
                │          └─emscripten
                └─source-maps
</pre></code></details>
