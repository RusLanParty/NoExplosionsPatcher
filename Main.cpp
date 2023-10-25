#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

void clearConsole()
{
    std::cout << "\x1B[2J\x1B[H";
}

int main(int argc, char* argv[])
{    
    double newValue = 0.000000;

    // Get the directory where the program's executable is located
    std::filesystem::path programPath = std::filesystem::path(argv[0]).remove_filename();
    std::filesystem::path filePath = programPath / "handling.meta";

    // Open the input file    
    if (!std::filesystem::exists(filePath))
    {
        std::cerr << "Error: handling.meta not found" << std::endl;        
        std::cout << "Make sure your handling.meta is in: " << filePath << std::endl;
        std::cout << "Press enter to exit...";
        std::cin.get();
        return 1;
    }
    else 
    {
        std::cout << "Success: handling.meta found" << std::endl;
    }

    // Open file
    std::ifstream inputFile(filePath);

    // Create a temporary file for writing
    std::ofstream tempFile("Temp.txt");
    if (!tempFile)
    {
        std::cerr << "Error: Could not create a temporary file." << std::endl;
        std::cout << "Press enter to exit...";
        std::cin.get();
        return 1;
    }    

    // Replacing values
    std::string line;

    while (std::getline(inputFile, line)) {
        if (line.find("<fCollisionDamageMult value=") != std::string::npos) {
            size_t startPos = line.find("\"") + 1;
            size_t endPos = line.find("\"", startPos);
            std::string originalValue = line.substr(startPos, endPos - startPos);
            line.replace(startPos, endPos - startPos, std::to_string(newValue));            
        }
        else if (line.find("<fWeaponDamageMult value=") != std::string::npos) {
            size_t startPos = line.find("\"") + 1;
            size_t endPos = line.find("\"", startPos);
            std::string originalValue = line.substr(startPos, endPos - startPos);
            line.replace(startPos, endPos - startPos, std::to_string(newValue));                                    
        }

        tempFile << line << std::endl;
    }
        
    // Close both files
    inputFile.close();
    tempFile.close();

    // Remove the original file
    remove("handling.meta");

    // Rename the temporary file to the original file name
    rename("Temp.txt", "handling.meta");

    
    std::cout << "Success: Patching complete" << std::endl;
    std::cout << "Press enter to exit...";
    std::cin.get(); 
    return 0;
}
