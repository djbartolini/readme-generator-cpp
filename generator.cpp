#include <iostream>
#include <fstream>
#include <map>

std::map<std::string, std::string> promptUser() {
    std::map<std::string, std::string> responses;

    std::cout << "Title: What is your project's title? ";
    std::getline(std::cin, responses["title"]);

    std::cout << "Description: Write a brief description about your project: ";
    std::getline(std::cin, responses["description"]);

    std::cout << "Installation: How do you run your project? ";
    std::getline(std::cin, responses["installation"]);

    std::cout << "License: Which license are you using? (Apache 2.0, MIT, Creative Commons, Eclipse Public License, GNU GPL v3, None) ";
    std::getline(std::cin, responses["license"]);

    std::cout << "Usage: What are the instructions for usage? ";
    std::getline(std::cin, responses["usage"]);

    std::cout << "Contributing: Who would you like to give credit to? ";
    std::getline(std::cin, responses["contributing"]);

    std::cout << "Please enter your GitHub username: ";
    std::getline(std::cin, responses["username"]);

    std::cout << "Please enter your email address: ";
    std::getline(std::cin, responses["email"]);

    return responses;
}

std::string renderLicenseBadge(const std::string& license) {
    if (license == "Apache 2.0") {
        return "[![License: Apache](https://img.shields.io/badge/License-Apache_2.0-blue.svg)]";
    } else if (license == "MIT") {
        return "[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)]";
    } else if (license == "Creative Commons") {
        return "[![License: CC0-1.0](https://licensebuttons.net/l/zero/1.0/80x15.png)]";
    } else if (license == "Eclipse Public License") {
        return "[![License](https://img.shields.io/badge/License-EPL_1.0-red.svg)]";
    } else if (license == "GNU GPL v3") {
        return "[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)]";
    } else {
        return "";
    }
}

std::string renderLicenseLink(const std::string& license) {
    if (license == "Apache 2.0") {
        return "[Apache 2.0](https://opensource.org/licenses/Apache-2.0)";
    } else if (license == "MIT") {
        return "[MIT](https://opensource.org/licenses/MIT)";
    } else if (license == "Creative Commons") {
        return "[Creative Commons](http://creativecommons.org/publicdomain/zero/1.0/)";
    } else if (license == "Eclipse Public License") {
        return "[Eclipse Public License 1.0](https://opensource.org/licenses/EPL-1.0)";
    } else if (license == "GNU GPL v3") {
        return "[GNU GPL v3](https://www.gnu.org/licenses/gpl-3.0)";
    } else {
        return "";
    }
}

std::string renderLicenseSection(const std::string& license) {
    if (license != "None") {
        return "This app is covered under the " + license + " license:";
    } else {
        return "None";
    }
}

std::string renderSupportSection(const std::string& username, const std::string& email) {
    if (!username.empty() && !email.empty()) {
        return "If you encounter problems with this README generator, please reach out to me on GitHub at: https://github.com/" + username + ", or email me at " + email;
    } else {
        return "Unavailable at this time.";
    }
}

std::string generateMarkdown(const std::map<std::string, std::string>& data) {
    std::string result = "# " + data.at("title") + "\n\n";
    result += renderLicenseBadge(data.at("license")) + "\n\n";
    result += "## Description\n" + data.at("description") + "\n\n";
    result += "## Table of Contents\n";
    result += "* [Installation](#installation)\n";
    result += "* [Usage](#usage)\n";
    result += "* [Contributing](#contributing)\n";
    result += "* [License](#license)\n";
    result += "* [Support](#support)\n\n";
    result += "## Installation\n" + data.at("installation") + "\n\n";
    result += "## Usage\n" + data.at("usage") + "\n\n";
    result += "## Contributing\n" + data.at("contributing") + "\n\n";
    result += "## License\n" + renderLicenseSection(data.at("license")) + " " + renderLicenseLink(data.at("license")) + "\n\n";
    result += "## Support\n" + renderSupportSection(data.at("username"), data.at("email")) + "\n";
    return result;
}

void writeToFile(const std::map<std::string, std::string>& responses) {
    std::ofstream file("dist/README.md");
    if (file.is_open()) {
        file << generateMarkdown(responses);
        file.close();
        std::cout << "Data saved! Generating README!" << std::endl;
    } else {
        std::cerr << "Unable to open file." << std::endl;
    }
}

int main() {
    std::map<std::string, std::string> responses = promptUser();
    writeToFile(responses);
    return 0;
}
