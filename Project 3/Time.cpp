#include "Time.hpp"

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
T Time::timeAndExecute(std::function<T(S, R)> func, const S& param1, const R& param2) {
  // Start timer
  auto start = std::chrono::steady_clock::now();

  // Execute function
  T execution_result = func(param1, param2);

  // Stop Timer
  auto end = std::chrono::steady_clock::now();
  auto diff = end - start;
  
  // Print execution time (ms)
  int duration = std::chrono::duration <double, std::milli> (diff).count();
  std::cout << "Finished executing in " << duration << " ms" << std::endl;
  return execution_result;
}