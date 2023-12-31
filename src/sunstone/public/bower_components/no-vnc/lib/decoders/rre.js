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

    var RREDecoder = function () {
        function RREDecoder() {
            _classCallCheck(this, RREDecoder);

            this._subrects = 0;
        }

        _createClass(RREDecoder, [{
            key: "decodeRect",
            value: function decodeRect(x, y, width, height, sock, display, depth) {
                if (this._subrects === 0) {
                    if (sock.rQwait("RRE", 4 + 4)) {
                        return false;
                    }

                    this._subrects = sock.rQshift32();

                    var color = sock.rQshiftBytes(4); // Background
                    display.fillRect(x, y, width, height, color);
                }

                while (this._subrects > 0) {
                    if (sock.rQwait("RRE", 4 + 8)) {
                        return false;
                    }

                    var _color = sock.rQshiftBytes(4);
                    var sx = sock.rQshift16();
                    var sy = sock.rQshift16();
                    var swidth = sock.rQshift16();
                    var sheight = sock.rQshift16();
                    display.fillRect(x + sx, y + sy, swidth, sheight, _color);

                    this._subrects--;
                }

                return true;
            }
        }]);

        return RREDecoder;
    }();

    exports.default = RREDecoder;
});