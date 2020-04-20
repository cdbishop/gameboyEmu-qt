#pragma once

namespace input {
namespace button {

enum {
  Up      = 1 << 0,
  Down    = 1 << 1,
  Left    = 1 << 2,
  Right   = 1 << 3,
  A       = 1 << 4,
  B       = 1 << 5,
  Start   = 1 << 6,
  Select  = 1 << 7
};
}

using State = unsigned int;

}