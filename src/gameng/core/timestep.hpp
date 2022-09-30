#pragma once

namespace gameng
{

class Timestep
{
public:
  Timestep(float time)
    :m_time(time)
  {
  }

  float GetSeconds(){return m_time;}
  float GetMilliSeconds(){return m_time * 1000.0f;}

  operator float() const {return m_time;}
private:
  float m_time;
};

} // namespace gameng
