#pragma once

namespace Prova
{
  class Watch
  {
    public:
      bool isRunning = false;
      int startTime = 0;
      int lastStopTime = 0;
      int breakLength = 0;
      void Start();
      void Stop();
      void Reset();
      void Restart();
      int GetElapsedMilliseconds();
  };
}