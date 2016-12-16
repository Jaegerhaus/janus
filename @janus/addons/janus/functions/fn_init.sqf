
janus_fps = 1;
janus_framesPerFlush = 10;
janus_extensionChunkSize = 4096;

janus_gameId = call janus_fnc_gameId;
[] spawn janus_fnc_runloop;
