private ["_id", "_chars"];

_id = "";
_chars =
[
  "1","2","3","4","5","6","7","8","9","0",
  "A","B","C","D","E","F","G","H","I","J","K","L","M",
  "N","O","P","Q","R","S","T","U","V","W","X","Y","Z"
];

for "_n" from 1 to 32 do
{
  _id = _id + selectRandom _chars;
};

_id
