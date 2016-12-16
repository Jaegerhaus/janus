private ["_frames", "_data", "_frame"];

_frames = _this;

_data = format [
  '["%1","%2","%3",[',
  janus_gameId,
  worldName,
  missionName
];

{
  _frame = _x;

  _data = _data + format [
    "[%1,[",
    _frame select 0
  ];

  {
    _data = _data + format ["%1,", _x];
  }
  forEach (_frame select 1);

  _data = ([_data, 0, -1] call BIS_fnc_trimString) + "]],";
}
forEach _frames;

_data = ([_data, 0, -1] call BIS_fnc_trimString) + "]]";

_data
