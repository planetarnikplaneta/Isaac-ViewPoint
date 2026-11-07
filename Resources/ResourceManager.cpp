#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "ResourceManager.h"

#include <Windows.h>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "../Core/Logger.h"
#include "../Core/State.h"
#include "../Core/AssetPaths.h"
#include "../Core/Config.h"

namespace
{
    namespace fs = std::filesystem;

    HRSRC FindEmbeddedResource(
        HMODULE module,
        const std::string& assetPath)
    {
        const std::string resourceName =
            ViewPoint::ToUpperResourceName(assetPath);

        HRSRC resource = FindResourceA(
            module,
            resourceName.c_str(),
            RT_RCDATA);

        if (resource)
            return resource;

        // Also check resource names containing literal quotes.
        const std::string quotedName =
            "\"" + resourceName + "\"";

        resource = FindResourceA(
            module,
            quotedName.c_str(),
            RT_RCDATA);

        if (resource)
        {
            ViewPoint::LogMessage(
                ("Found quoted resource name: " +
                 quotedName).c_str());

            return resource;
        }

        char message[512];

        snprintf(
            message,
            sizeof(message),
            "Resource not found: %s",
            assetPath.c_str());

        ViewPoint::LogMessage(message);

        return nullptr;
    }

    BOOL CALLBACK EnumerateResourceNames(
        HMODULE module,
        LPCSTR type,
        LPSTR name,
        LONG_PTR)
    {
        char message[512];

        if (IS_INTRESOURCE(name))
        {
            snprintf(
                message,
                sizeof(message),
                "Embedded numeric resource ID: %u",
                static_cast<unsigned>(
                    reinterpret_cast<ULONG_PTR>(name)));

            ViewPoint::LogMessage(message);
            return TRUE;
        }

        snprintf(
            message,
            sizeof(message),
            "Enumerated resource: %s",
            name);

        ViewPoint::LogMessage(message);

        SetLastError(ERROR_SUCCESS);

        HRSRC resource = FindResourceA(
            module,
            name,
            type);

        if (resource)
        {
            ViewPoint::LogMessage(
                "Lookup using enumerated name: SUCCESS");
        }
        else
        {
            snprintf(
                message,
                sizeof(message),
                "Resource lookup failed: %lu",
                static_cast<unsigned long>(
                    GetLastError()));

            ViewPoint::LogMessage(message);
        }

        return TRUE;
    }
}

namespace ViewPoint
{
    bool ReadAsset(
        const std::string& requestedPath,
        std::vector<unsigned char>& output)
    {
        const std::string assetPath =
            NormalizeAssetPath(requestedPath);

        if (assetPath.empty())
            return false;

        output.clear();

        // External assets override embedded assets.
        try
        {
            const fs::path externalPath =
                GetConfigurationPath().parent_path() /
                "resources_ViewPoint" /
                fs::path(assetPath);

            if (fs::exists(externalPath) &&
                fs::is_regular_file(externalPath))
            {
                std::ifstream file(
                    externalPath,
                    std::ios::binary);

                if (file)
                {
                    file.seekg(0, std::ios::end);

                    const std::streamoff size =
                        file.tellg();

                    if (size <= 0)
                        return false;

                    file.seekg(0, std::ios::beg);

                    output.resize(
                        static_cast<size_t>(size));

                    file.read(
                        reinterpret_cast<char*>(output.data()),
                        size);

                    if (file)
                    {
                        LogMessage(
                            ("Loaded external asset: " +
                             assetPath).c_str());

                        return true;
                    }

                    output.clear();
                }
            }
        }
        catch (...)
        {
            LogMessage(
                "External asset access failed.");
        }

        // Fall back to an embedded Windows resource.
        HRSRC resource = FindEmbeddedResource(
            g_Module,
            assetPath);

        if (!resource)
        {
            LogMessage(
                ("Asset not found: " +
                 assetPath).c_str());

            return false;
        }

        HGLOBAL loaded = LoadResource(
            g_Module,
            resource);

        if (!loaded)
            return false;

        const DWORD size = SizeofResource(
            g_Module,
            resource);

        const void* data = LockResource(loaded);

        if (!data || size == 0)
            return false;

        const unsigned char* bytes =
            static_cast<const unsigned char*>(data);

        output.assign(
            bytes,
            bytes + size);

        return true;
    }

    void DiagnoseEmbeddedResources()
    {
        char message[256];

        snprintf(
            message,
            sizeof(message),
            "Resource enumeration module: %p",
            static_cast<void*>(g_Module));

        LogMessage(message);

        EnumResourceNamesA(
            g_Module,
            RT_RCDATA,
            EnumerateResourceNames,
            0);
    }
}
