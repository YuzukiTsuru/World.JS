//
// Created by YuzukiTsuru on 2021/1/28.
//

#ifndef WORLDJS_ERRORCODE_H
#define WORLDJS_ERRORCODE_H

void EM_TERM() {
    EM_ASM(
            function WorldJSException(message) {
                this.message = message;
                this.name = 'WorldJSException';
            }
            throw new WorldJSException("WorldJS Runtime Error. Terminated.");
    );
}

#define E00 "Audio File Error."
#define E01 "Audio Length Error, Audio Length Got 0"

#endif //WORLDJS_ERRORCODE_H
