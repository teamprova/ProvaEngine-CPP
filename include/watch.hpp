#pragma once

namespace Prova
{
  class Watch
  {
    public:
      void Start();
      void Pause();
      void Reset();
      void Restart();
      bool IsRunning();
      int GetElapsedMilliseconds();
    private:
      bool _isRunning = false;
      int _startTime = 0;
      int _lastStopTime = 0;
      int _breakLength = 0;
  };
}