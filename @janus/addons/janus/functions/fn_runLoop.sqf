private ["_frames", "_units", "_frame"];

_frames = [];

while { true } do
{
  sleep 1 / janus_fps;

  _units = [];
  {
    _units pushBack (_x call janus_fnc_unitData);
  }
  forEach allUnits;

  _frame = _frames pushBack
  [
    time,
    _units
  ];

  if (_frame + 1 >= janus_framesPerFlush) then
  {
    _frames spawn janus_fnc_flushFrames;
    _frames = [];
  };
};
