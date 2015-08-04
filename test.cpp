#include <string.h>
#include "SparseBitmap.hpp"

int main(int argc, char **argv) {
  SparseBitmap bitmap("testfile",LOCK_EX, 1);
  std::cout <<"Expected: 0 " <<  bitmap.is_set(5) << "\n";
  std::cout << "Expected: 0 " <<  bitmap.is_set(250000) << "\n";
  std::cout << "Expected: 1 " <<  bitmap.set_bit(250000) << "\n";
  std::cout << "Expected: 1 " <<  bitmap.set_bit(5) << "\n";
  std::cout << "Expected: 1 " <<  bitmap.is_set(5) << "\n";
  std::cout << "Expected: 1 " <<  bitmap.is_set(250000) << "\n";
  std::cout << "Expected: 0 " <<  bitmap.is_set(250001) << "\n";

  /* should rollback */
  bitmap.close();
  /* should not roll back */
  bitmap.open("testfile", LOCK_EX);

  std::cout <<"Expected: 0 " <<  bitmap.is_set(5) << "\n";
  std::cout << "Expected: 0 " <<  bitmap.is_set(250000) << "\n";
  std::cout << "Expected: 1 " <<  bitmap.set_bit(250000) << "\n";
  std::cout << "Expected: 1 " <<  bitmap.set_bit(5) << "\n";
  std::cout << "Expected: 1 " <<  bitmap.is_set(5) << "\n";
  std::cout << "Expected: 1 " <<  bitmap.is_set(250000) << "\n";
  std::cout << "Expected: 0 " <<  bitmap.is_set(250001) << "\n";

  /* should not roll back */
  bitmap.commit();

  /* should not do replay*/
  bitmap.open("testfile", LOCK_SH);
  
}

