#include "AssetPaths.h"

#include <algorithm>
#include <sstream>
#include <vector>

namespace ViewPoint
{
    std::string Trim(const std::string& text)
    {
        const size_t first =
            text.find_first_not_of(" \t\r\n");

        if (first == std::string::npos)
            return {};

        const size_t last =
            text.find_last_not_of(" \t\r\n");

        return text.substr(first, last - first + 1);
    }

    std::string NormalizeAssetPath(std::string path)
    {
        std::replace(
            path.begin(),
            path.end(),
            '\\',
            '/');

        while (path.rfind("./", 0) == 0)
            path.erase(0, 2);

        if (path.empty() ||
            path[0] == '/' ||
            (path.size() > 1 && path[1] == ':'))
        {
            return {};
        }

        std::stringstream stream(path);

        std::string part;
        std::vector<std::string> parts;

        while (std::getline(stream, part, '/'))
        {
            if (part.empty() || part == ".")
                continue;

            if (part == "..")
                return {};

            parts.push_back(part);
        }

        std::string result;

        for (const std::string& p : parts)
        {
            if (!result.empty())
                result += '/';

            result += p;
        }

        return result;
    }

    std::string ResolveRelativeAsset(
        const std::string& parent,
        const std::string& child)
    {
        std::string normalizedChild = child;

        std::replace(
            normalizedChild.begin(),
            normalizedChild.end(),
            '\\',
            '/');

        if (normalizedChild.empty() ||
            normalizedChild[0] == '/' ||
            (normalizedChild.size() > 1 &&
             normalizedChild[1] == ':'))
        {
            return {};
        }

        const size_t slash =
            parent.find_last_of('/');

        const std::string directory =
            slash == std::string::npos
                ? ""
                : parent.substr(0, slash + 1);

        return NormalizeAssetPath(
            directory + normalizedChild);
    }

    std::string ToUpperResourceName(const std::string& name)
    {
        std::string result = name;

        for (char& c : result)
        {
            if (c >= 'a' && c <= 'z')
            {
                c = static_cast<char>(c - 'a' + 'A');
            }
        }

        return result;
    }
}
