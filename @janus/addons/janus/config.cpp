class CfgPatches
{
  class Janus
  {
    name = "Janus";
    author = "ARCOMM";
    requiredAddons[] = {"A3_Functions_F", "cba_main"};
    units[] = {};
    weapons[] = {};
  };
};

class CfgFunctions
{
  class JANUS
  {
    class fnc
    {
      file = "janus\functions";
      class init { postInit = 1; };
      class flushFrames;
      class framesData;
      class gameId;
      class runLoop;
      class sendChunked;
      class unitData;
    };
  };
};
