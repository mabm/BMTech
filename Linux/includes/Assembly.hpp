//
// Assembly.hpp for  in /home/Dieu/Desktop/Work/BMTech/Linux
// 
// Made by Dieu Dieu
// Login   <Dieu@epitech.net>
// 
// Started on  Mon Jan 18 15:20:30 2016 Dieu Dieu
// Last update Mon Jan 18 15:20:31 2016 Dieu Dieu
//

#ifndef		_ASSEMBLY_HPP_
# define	_ASSEMBLY_HPP_

# include	<Conf.hh>
# include	<rapidjson/document.h>
# include	<rapidjson/filereadstream.h>

# include	<string>

using namespace rapidjson;
class		Assembly
{
private:
  std::string	_version;
  std::string	_author;
  std::string	_name;
  std::string	_updateURL;
  
public:
  void		set(const std::string &version, const std::string &author, const std::string &name) {
    this->_version = version;
    this->_author = author;
    this->_name = name;
  };

  std::string	getVersion() const {
    return (_version);
  };

  std::string	getAuthor() const {
    return (_author);
  };

  std::string	getName() const {
    return (_name);
  };

  void		setUpdateURL(const std::string &url) {
    this->_updateURL = url;
  };

  void		checkForUpdate() {
    FILE	*fp;
    char	readBuffer[4096];
    Document	d;
    
    std::cout << "\u2746 Checking for update : ";
    try {
      Utils::httpRequest(this->_updateURL, TMP_FILE_UPDATE_REQUEST);
    } catch (const std::exception &e) {
      std::cout << "Error : " << e.what() << std::endl;
    };
    if (!(fp = fopen(TMP_FILE_UPDATE_REQUEST, "rb"))) {
      std::cout << "Error while fetching data" << std::endl;
    }
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    d.ParseStream(is);
    if (!d.IsObject()) {
      std::cout << "Bad API Result" << std::endl;
      fclose(fp);
      return;
    }
    if (atof(d["version"].GetString()) > atof(this->_version.c_str())) {
      std::cout << "\033[31mNew version (" << d["version"].GetString() << ") named \"" << d["name"].GetString() << "\" is available !\033[0m" << std::endl;
      std::cout << "/!\\ You MUST update your BMTech ! Please, go to http://jobertomeu.fr/bmtech" << std::endl;
      exit (-1);
    } else if (atof(d["version"].GetString()) == atof(this->_version.c_str()))
      std::cout << "\033[32mYou are up-to-date !\033[0m (" << d["version"].GetString() << " - " << d["name"].GetString() << ")" << std::endl;
    else {
      std::cout << "WTF ? Are you Marty Mcfly ?" << std::endl;
      std::cout << "Sorry, but you have to go away" << std::endl;
      exit (-1);
    }
    fclose(fp);
  };
};

#endif
