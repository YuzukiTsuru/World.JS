let test = "vaiueo2d.wav";

function runTest() {
    let WorldJS = Module.WorldJS;
    let wav2World = WorldJS.Wav2World(test);
    let x =  WorldJS.WavRead(test);
    WorldJS.DisplayInformationVal(x);
}