private ["_data", "_chunk", "_result"];

_data = _this;

"janus" callExtension "chunk_begin";

while { count _data > janus_extensionChunkSize } do
{
  _chunk = _data select [0, janus_extensionChunkSize];
  _data = _data select [janus_extensionChunkSize];
  "janus" callExtension _chunk;
};

"janus" callExtension _data;
_result = "janus" callExtension "chunk_end";

_result
