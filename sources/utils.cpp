// Copyright 2021 Your Name <your_email>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <utils.hpp>

void start(){
  std::vector<std::string> ids;
  std::vector<int> dates;
  std::vector<int> files;
  std::vector<std::string> folders;
  std::string path;
  std::cin >> path;
  const std::string target_path(path);
  const boost::regex my_filter("balance_(\\d{8})_(\\d{8}).txt");

  boost::filesystem::directory_iterator end_itr_dir;
  for (boost::filesystem::directory_iterator j( target_path );
       j != end_itr_dir; ++j)
  {
    boost::filesystem::directory_iterator end_itr;
    if (!boost::filesystem::is_regular_file(j->status()))
    {
      for (boost::filesystem::directory_iterator i(j->path());
           i != end_itr; ++i)
      {
        boost::smatch what;
        if (boost::regex_match(
                i->path().filename().string(), what, my_filter)){
          std::cout << j->path().filename().string() << " " <<
              i->path().filename().string() << std::endl;
          boost::filesystem::ifstream fileHandler(i->path().string());
          std::string line;
          getline(fileHandler, line);
          std::string id = line.substr(2, 8);
          int date = std::stoi(line.substr(11, 8));
          bool flag = true;
          int count = 0;
          for (auto l = ids.begin(); l != ids.end(); l++) {
            if (*l == id) {
              flag = false;
              if (date > dates[count]) dates[count] = date;
              files[count]++;
            }
            count++;
          }
          if (flag)
          {
            ids.push_back(id);
            dates.push_back(date);
            files.push_back(1);
            folders.push_back(j->path().filename().string());
          }
          std::cout << id << std::endl;
          std::cout << date << std::endl;
          std::cout << line << std::endl;
        }
      }
    }
  }
  for (size_t i = 0; i < ids.size(); i++){
    std::cout << "-> broker: " << folders[i] << " account: " << ids[i] <<
        " last update: " << dates[i] << " files: " << files[i] << std::endl;
  }
}
