define(["exports"], function (exports) {
    "use strict";

    Object.defineProperty(exports, "__esModule", {
        value: true
    });

    function _classCallCheck(instance, Constructor) {
        if (!(instance instanceof Constructor)) {
            throw new TypeError("Cannot call a class as a function");
        }
    }

    var _createClass = function () {
        function defineProperties(target, props) {
            for (var i = 0; i < props.length; i++) {
                var descriptor = props[i];
                descriptor.enumerable = descriptor.enumerable || false;
                descriptor.configurable = true;
                if ("value" in descriptor) descriptor.writable = true;
                Object.defineProperty(target, descriptor.key, descriptor);
            }
        }

        return function (Constructor, protoProps, staticProps) {
            if (protoProps) defineProperties(Constructor.prototype, protoProps);
            if (staticProps) defineProperties(Constructor, staticProps);
            return Constructor;
        };
    }();

    var RawDecoder = function () {
        function RawDecoder() {
            _classCallCheck(this, RawDecoder);

            this._lines = 0;
        }

        _createClass(RawDecoder, [{
            key: "decodeRect",
            value: function decodeRect(x, y, width, height, sock, display, depth) {
                if (this._lines === 0) {
                    this._lines = height;
                }

                var pixelSize = depth == 8 ? 1 : 4;
                var bytesPerLine = width * pixelSize;

                if (sock.rQwait("RAW", bytesPerLine)) {
                    return false;
                }

                var cur_y = y + (height - this._lines);
                var curr_height = Math.min(this._lines, Math.floor(sock.rQlen / bytesPerLine));
                var data = sock.rQ;
                var index = sock.rQi;

                // Convert data if needed
                if (depth == 8) {
                    var pixels = width * curr_height;
                    var newdata = new Uint8Array(pixels * 4);
                    for (var i = 0; i < pixels; i++) {
                        newdata[i * 4 + 0] = (data[index + i] >> 0 & 0x3) * 255 / 3;
                        newdata[i * 4 + 1] = (data[index + i] >> 2 & 0x3) * 255 / 3;
                        newdata[i * 4 + 2] = (data[index + i] >> 4 & 0x3) * 255 / 3;
                        newdata[i * 4 + 4] = 0;
                    }
                    data = newdata;
                    index = 0;
                }

                display.blitImage(x, cur_y, width, curr_height, data, index);
                sock.rQskipBytes(curr_height * bytesPerLine);
                this._lines -= curr_height;
                if (this._lines > 0) {
                    return false;
                }

                return true;
            }
        }]);

        return RawDecoder;
    }();

    exports.default = RawDecoder;
});