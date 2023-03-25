#include <iostream>
#include <fstream>
#include <utility>
#include <string>

#include "count_artist.hpp"

int main(int argc, char* argv[]){
  if (argc == 1 || (argc == 2 && argv[1] == std::string("--help"))){
    std::cout << "Usage: main [artist path file] [artist type path file] [gender path file] [year]" << std::endl;
    return 0;
  }

  std::string artist_path = argv[1];
  std::string artist_type_path = argv[2];
  std::string gender_path = argv[3];
  std::string year = argv[4];

  std::ifstream file_artist(artist_path);
  std::ifstream file_artist_type(artist_type_path);
  std::ifstream file_gender(gender_path);

  try{
    if (!file_artist.is_open() || !file_artist_type.is_open() || !file_gender.is_open()){
      throw "Wrong path.";
    }
    CountedArtists count = CountMalesOrFemalesByYear(file_artist, file_artist_type, file_gender, year);
    std::cout << "Number of male artists - " << count.males << ", number of female artists - " << count.females << std::endl;
  }
  catch(const char* error_message)
  {
    std::cout << error_message << std::endl;
  }
  file_artist.close();
  file_artist_type.close();
  file_gender.close();
  return 0;
}