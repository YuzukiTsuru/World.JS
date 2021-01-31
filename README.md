<p align="center"><img width="300" src=".github/ScreenShots/logo.v3.png" alt="World.JS logo"></p>
<h1 align="center">World.JS</h1>
<p align="center">A JavaScript Wrapper for World Vocoder Powered by Emscripten</p>
<p align="center"><img src="https://github.com/YuzukiTsuru/World.JS/workflows/CMake/badge.svg">    <img src="https://ci.appveyor.com/api/projects/status/6vbge2p0q0mdshtc?svg=true"></p>


### About World.JS

World.JS is A JavaScript Wrapper for World Vocoder Powered by Emscripten.

You can use World Vocoder in your Browser,Node or Electron app and many more.

### Build Status CI
| appveyor master | appveyor latest | GitHub Action latest |
|---|---|---|
|[![Build status](https://ci.appveyor.com/api/projects/status/6vbge2p0q0mdshtc/branch/master?svg=true)](https://ci.appveyor.com/project/GloomyGhost-MosquitoCoil/world-js/branch/master)|[![Build status](https://ci.appveyor.com/api/projects/status/6vbge2p0q0mdshtc?svg=true)](https://ci.appveyor.com/project/GloomyGhost-MosquitoCoil/world-js)|![CMake](https://github.com/YuzukiTsuru/World.JS/workflows/CMake/badge.svg)|

## Document
Read more info in: [document](http://YuzukiTsuru.github.io/World.JS)

### API
```
World Native:
- [x] WavRead_JS             # .wav input functions.
- [x] DIO_JS                 # F0 estimation based on DIO (Distributed Inline-filter Operation).
- [x] Harvest_JS             # F0 estimation based on Harvest.
- [x] DisplayInformation     # Display Information.
- [x] DisplayInformationVal  # Display Information by Audio object from WavRead_JS()
- [X] GetInformation         # Output information in HTML.
- [x] CheapTrick_JS          # Spectral envelope estimation on the basis of the idea of CheapTrick.
- [x] D4C_JS                 # Band-aperiodicity estimation on the basis of the idea of D4C.
- [X] Synthesis_JS           # Voice synthesis based on f0, spectrogram and aperiodicity.
- [x] WavWrite_JS            # Output Wav File.

Wrapper:
- [x] Wav2World              # Wav to world.
- [ ] WavInJS                # Load wav file as WavRead do in JavaScript.
```


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

## License

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
