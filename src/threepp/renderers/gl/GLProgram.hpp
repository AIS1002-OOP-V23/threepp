// https://github.com/mrdoob/three.js/blob/r129/src/renderers/webgl/WebGLProgram.js

#ifndef THREEPP_GLPROGRAM_HPP
#define THREEPP_GLPROGRAM_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <glad/glad.h>

#include "threepp/renderers/GLRenderer.hpp"

namespace threepp::gl {

    std::vector<std::string> split(const std::string &s, char delimiter) {

        std::string token;
        std::vector<std::string> tokens;
        std::istringstream tokenStream(s);

        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }

        return tokens;
    }

    void join(const std::vector<std::string> &v, char c, std::string &s) {

        s.clear();

        for (auto p = v.begin(); p != v.end(); ++p) {
            s += *p;
            if (p != v.end() - 1) {
                s += c;
            }
        }
    }

    std::string addLineNumbers(const std::string &str) {

        auto lines = split(str, '\n');

        for (int i = 0; i < lines.size(); i++) {

            lines[i] = std::to_string(i + 1) + ": " + lines[i];
        }

        std::string result;
        join(lines, '\n', result);
        return result;
    }

    std::pair<std::string, std::string> getEncodingComponents(int encoding) {

        switch (encoding) {

            case LinearEncoding:
                return {"Linear", "( value )"};
            case sRGBEncoding:
                return {"sRGB", "( value )"};
            case RGBEEncoding:
                return {"RGBE", "( value )"};
            case RGBM7Encoding:
                return {"RGBM", "( value, 7.0 )"};
            case RGBM16Encoding:
                return {"RGBM", "( value, 16.0 )"};
            case RGBDEncoding:
                return {"RGBD", "( value, 256.0 )"};
            case GammaEncoding:
                return {"Gamma", "( value, float( GAMMA_FACTOR ) )"};
            case LogLuvEncoding:
                return {"LogLuv", "( value )"};
            default:
                std::cerr << "THREE.WebGLProgram: Unsupported encoding:" << encoding << std::endl;
                return {"Linear", "( value )"};
        }
    }

    std::string getTexelDecodingFunction(const std::string &functionName, int encoding) {

        const auto components = getEncodingComponents(encoding);
        return "vec4 " + functionName + "( vec4 value ) { return " + components.first + "ToLinear" + components.second + "; }";
    }

    std::string getTexelEncodingFunction(const std::string &functionName, int encoding) {

        const auto components = getEncodingComponents(encoding);
        return "vec4 " + functionName + "( vec4 value ) { return LinearTo" + components.first + components.second + "; }";
    }

    std::string getToneMappingFunction(const std::string &functionName, int toneMapping) {

        std::string toneMappingName;

        switch (toneMapping) {

            case LinearToneMapping:
                toneMappingName = "Linear";
                break;

            case ReinhardToneMapping:
                toneMappingName = "Reinhard";
                break;

            case CineonToneMapping:
                toneMappingName = "OptimizedCineon";
                break;

            case ACESFilmicToneMapping:
                toneMappingName = "ACESFilmic";
                break;

            case CustomToneMapping:
                toneMappingName = "Custom";
                break;

            default:
                std::cerr << "THREE.WebGLProgram: Unsupported toneMapping:" << toneMapping << std::endl;
                toneMappingName = "Linear";
        }

        return "vec3 " + functionName + "( vec3 color ) { return " + toneMappingName + "ToneMapping( color ); }";
    }

    std::string generateDefines(const std::unordered_map<std::string, std::any> &defines) {

        //            std::vector<std::string> chunks;
        //
        //            for ( const auto& [name, value] : defines ) {
        //
        //                if ( value == false ) continue;
        //
        //                chunks.emplace_back( "#define " + name + " " + value );
        //
        //            }
        //
        //            std::string result;
        //            join(chunks, '\n',result);
        //
        //            return result;

        //TODO

        return "";
    }

//    void fetchAttributeLocations(program) {
//
//        const attributes = {};
//
//        const n = gl.getProgramParameter(program, gl.ACTIVE_ATTRIBUTES);
//
//        for (let i = 0; i < n; i++) {
//
//            const info = gl.getActiveAttrib(program, i);
//            const name = info.name;
//
//            // console.log( 'THREE.WebGLProgram: ACTIVE VERTEX ATTRIBUTE:', name, i );
//
//            attributes[name] = gl.getAttribLocation(program, name);
//        }
//
//        return attributes;
//    }

    class GLProgram {

    public:
        // GLProgram(std::shared_ptr<GLRenderer> renderer, std::string cacheKey) {}

    private:
        inline static int programIdCount = 0;
    };


}// namespace threepp::gl

#endif//THREEPP_GLPROGRAM_HPP