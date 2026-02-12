#include "fileio/SceneLoader.hpp"
#include "core/Logger.hpp"
#include "core/constants.hpp"
#include "core/types.hpp"
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <map>


std::vector<Particle> loadParticles(const std::string& filename) 
{    
    std::vector<Particle> particles;

    // Read JSON into string
    std::ifstream ifs(filename);
    if (!ifs.is_open()) 
    {
        Logger::error("Could not open file: " + filename);
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string content = buffer.str();

    // Parse JSON
    rapidjson::Document doc;
    doc.Parse(content.c_str());

    if (doc.HasParseError()) 
    {
        Logger::error("Could not parse JSON file: " + filename 
            + ", error: " + rapidjson::GetParseError_En(doc.GetParseError()));
        throw std::runtime_error("Could not parse JSON file: " + filename 
            + ", error: " + rapidjson::GetParseError_En(doc.GetParseError()));
    }

    // Extract Data
    if (doc.HasMember("particles") && doc["particles"].IsArray()) {
        const rapidjson::Value& pArray = doc["particles"];

        // Used for later conversion of normalized position coordinates
        float half_width_m  = (Constants::RENDER_RES.width  * 0.5f) / Constants::PIXELS_PER_METER;
        float half_height_m = (Constants::RENDER_RES.height * 0.5f) / Constants::PIXELS_PER_METER;
        
        for (rapidjson::SizeType i = 0; i < pArray.Size(); i++) {
            const rapidjson::Value& obj = pArray[i];

            auto xpos = obj["pos"][0].GetFloat();
            auto ypos = obj["pos"][1].GetFloat();
            auto xvel = obj["vel"][0].GetFloat();
            auto yvel = obj["vel"][1].GetFloat();
            auto mass        = obj["mass"].GetFloat();
            auto radius      = obj["radius"].GetFloat();
            auto restitution = obj["restitution"].GetFloat();
            auto mu          = obj["mu"].GetFloat();
            auto color       = obj["color"].GetString();

            // Validate fields
            if (!obj.HasMember("pos") || !obj["pos"].IsArray() || obj["pos"].Size() != 2)
            {
            Logger::error("Invalid or missing position within " + filename);
            throw std::runtime_error("Invalid or missing position within " + filename); 
            }
            if (!obj.HasMember("vel") || !obj["vel"].IsArray() || obj["vel"].Size() != 2)
            {
            Logger::error("Invalid or missing velocity within " + filename);
            throw std::runtime_error("Invalid or missing velocity within " + filename); 
            }
            if (!obj.HasMember("color") || !obj["color"].IsString())
            {
            Logger::error("Invalid or missing color within " + filename);
            throw std::runtime_error("Invalid or missing color within " + filename); 
            }

            std::string colorStr = obj["color"].GetString(); 
            if (!Constants::COLOR_MAP.contains(colorStr))
            {
            Logger::error("Unknown color: " + colorStr + " within: " + filename);
            throw std::runtime_error("Unknown color: " + colorStr + " within: " + filename);
            }

            // Input positions ranging from -1 to 1
            float nx = obj["pos"][0].GetFloat();
            float ny = obj["pos"][1].GetFloat();

            float x_m = nx * half_width_m;
            float y_m = ny * half_height_m;

            Particle p(
                Eigen::Vector2f(x_m, y_m),
                Eigen::Vector2f(obj["vel"][0].GetFloat(), obj["vel"][1].GetFloat()),
                obj["mass"].GetFloat(),
                obj["radius"].GetFloat(),
                obj["mu"].GetFloat(),
                obj["restitution"].GetFloat(),
                Constants::COLOR_MAP.at(colorStr)
            );

            particles.push_back(p);
        }
    }

    return particles;
}