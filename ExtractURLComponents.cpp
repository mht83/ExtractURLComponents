//////////////////////////////////////////////written by mht83/////////////////////////////////////////
#include <string>
#include <vector>
#include <iostream>


class URL {
public:

    URL(std::vector<std::string> tokens) {
        protocol = tokens[0];
        domain = tokens[4];
        if (tokens[5] == ":") {
            port = tokens[6];

        }
        int i = 5;
        if (!port.empty()) { i = 7; }
        

        for ( ; i < tokens.size(); ++i) {
            if (tokens[i] == "/") {
                path += tokens[i] + tokens[i + 1];
                i++; 
            }
            else if (tokens[i] == "?") {
                query = tokens[i + 1];
                i++; 
            }
            else if (tokens[i] == "#") {
                fragment = tokens[i + 1];
                break; 
            }
        }
    }

    void display() const {
        if (!protocol.empty()) std::cout << "URL protocol is " << protocol << std::endl;
        if (!domain.empty()) std::cout << "URL domain is " << domain << std::endl;
        if (!port.empty()) std::cout << "URL port is " << port << std::endl;
        if (!path.empty()) std::cout << "URL path is " << path << std::endl;
        if (!query.empty()) std::cout << "URL query is " << query << std::endl;
        if (!fragment.empty()) std::cout << "URL fragment is " << fragment << std::endl;
    }
private:
    std::string protocol="";
    std::string domain="";
    std::string port="";
    std::string path="";
    std::string query="";
    std::string fragment="";
};


std::vector<std::string> tokenizer(const std::string str, const std::string delimiters) {
    std::vector<std::string> tokens;
    std::string token;
    int start = 0, end = 0;

    while ((end = str.find_first_of(delimiters.data(), start)) != std::string::npos) {
        if (end != start) {
            token = str.substr(start, end - start);
            tokens.push_back(token);
        }
        tokens.push_back(str.substr(end, 1));
        start = end + 1;
    }

    if (start < str.size()) {
        tokens.push_back(str.substr(start));
    }

    return tokens;
}



int main() {
    std::string str = "https://www.example.co.uk:443/blog/article/search?docid=720&hl=en#dayone";
    std::string delimiters = ":#?/"; 
    std::vector<std::string> tokens = tokenizer(str, delimiters);

    std::cout << "input URL is: " << str<<std::endl;

    URL url(tokens);
    url.display();
    return 0;
}
