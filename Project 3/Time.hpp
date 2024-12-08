#pragma once

#include <iostream>
#include <chrono>
#include <functional>

namespace Time {

  /**
   * Measures the execution time of a given function, prints the duration.
   * & returns the result of the executed function.
   * 
   * @param func The function to be executed. It takes two parameters of types S and R and returns a result of type T.
   * @param param1 The first parameter to pass to the function `func`.
   * @param param2 The second parameter to pass to the function `func`.
   * @return The result of executing the function `func` with parameters `param1` and `param2`.
   * 
   * @tparam T The return type of the function.
   * @tparam S The type of the first parameter.
   * @tparam R The type of the second parameter.
   */
  template <typename T, typename S, typename R>
  T timeAndExecute(std::function<T(S, R)> func, const S& param1, const R& param2);
};

#include "Time.cpp"