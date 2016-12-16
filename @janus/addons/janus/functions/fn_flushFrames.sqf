private ["_frames", "_data", "_result"];

_frames = _this;

_data = _frames call janus_fnc_framesData;
_result = _data call janus_fnc_sendChunked;

diag_log format ["Flushed frames: %1", _result];

true
